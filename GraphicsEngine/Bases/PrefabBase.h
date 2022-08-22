/********************************
*								*
*	Prefab Base.h				*
*								*
*	Created : 2022/07/25		*
*	Updated : 2022/07/26		*
*********************************/

#pragma once

#include <vector>
#include <functional>
#include <assert.h>
#include "Bases/ModelBase.h"
#include "Bases/ShaderBase.h"
#include "Bases/BufferBase.h"
#include "Bases/ResourceBase.h"

#include "Bases/FactoryBase.h"
#include "Bases/GraphicsEngineBase.h"

namespace GraphicsEngineSpace
{
	class GraphicsEngine;

	struct ConstantBufferSetting
	{
		BufferBase* buffer;
		UINT slot;
		void* data;
		ShaderType type;
	};

	class PrefabBase : public ResourceBase<PrefabBase>
	{
		struct cbMatrix
		{
			Matrix worldTransform;
			Matrix worldInvTransform;
		};

		ModelBase* const model;

		ShaderBase* vertexShader;
		ShaderBase* pixelShader;

		std::vector<BufferBase*> shadowVertexBuffers;
		std::vector<BufferBase*> vertexBuffers;
		std::vector<ConstantBufferSetting> onceBuffer;
		const ConstantBufferSetting matrixBuffer;
		ConstantBufferSetting materialBuffer;

		std::string animationKey;
		Matrix worldTransform;
		float animationTime;

		bool isSkinning;

	public:
		PrefabBase(ModelBase* model, const ConstantBufferSetting& matrixBuffer)
			: model(model)
			, vertexShader(nullptr)
			, pixelShader(nullptr)
			, matrixBuffer(matrixBuffer)
			, materialBuffer{}
			, worldTransform(Matrix::Identity)
			, animationTime(0.0f)
			, isSkinning(false) {}
		virtual ~PrefabBase() = default;

		const std::map<int, MaterialBase*>& GetMaterials() { return model->GetMaterials(); }

		void SetVertexShader(ShaderBase* shader) { this->vertexShader = shader; }
		void SetPixelShader(ShaderBase* shader) { this->pixelShader = shader; }
		void AddOnceBuffer(const ConstantBufferSetting& buffer) { onceBuffer.push_back(buffer); }
		void SetMaterialBuffer(const ConstantBufferSetting& materialBuffer) { this->materialBuffer = materialBuffer; }
		void SetRotation(const Vector& rotation) { model->SetRotation(rotation); }
		void SetSkinning(bool isSkinning) { this->isSkinning = isSkinning; }

		bool SetAnimationKey(const std::string& animationKey)
		{
			if (model == nullptr)
				return false;

			this->animationKey = animationKey;

			return true;
		}

		template <typename T>
		void CreateVertexBuffer(FactoryBase* factory, std::function<T(const VertexData&)> vertexConstructor);

		bool PrepareRender(const Matrix& worldTransform, float animationTime)
		{
			if (model == nullptr)
				assert(0);

			this->worldTransform = worldTransform;
			this->animationTime = animationTime;

			model->SetAnimationKey(animationKey);
			return model->PrepareRender(worldTransform, animationTime);
		}

		void Render(GraphicsEngineBase* engine)
		{
			GraphicsEngineBase::RenderData temp;

			temp.worldTransform = worldTransform;
			temp.animationTime = animationTime;
			temp.prefab = this;

			engine->AddRenderQueue(temp);
		}

		void ShadowRender(GraphicsEngineBase* engine)
		{
			const std::vector<MeshBase*>& meshes = model->GetMeshes();

			for (int i = 0; i < meshes.size(); i++)
			{
				cbMatrix cb;
				cb.worldTransform = MatrixTranspose(meshes[i]->GetTransform().GetWorldTransform());

				matrixBuffer.buffer->SetUpBuffer(matrixBuffer.slot, &cb, ShaderType::VERTEX);

				engine->DrawMesh(shadowVertexBuffers[i], meshes[i]->GetIndexBuffer());
			}
		}

		void RenderImpl(GraphicsEngineBase* engine)
		{
			if (model == nullptr)
				assert(0);

			if (vertexShader != nullptr)
				vertexShader->SetUpShader();

			if (pixelShader != nullptr)
				pixelShader->SetUpShader();

			auto& materials = model->GetMaterials();
			//auto materials = pbrModel->GetPrefab()->GetMaterials();

			struct MaterialCB
			{
				HeraclesMath::Vector ambient;
				HeraclesMath::Vector diffuse;
				HeraclesMath::Vector specular;
			} material;

			for (auto iter : materials)
			{
				auto materialData = iter.second->GetMaterialData();
				auto maps = materialData.maps;

				material.ambient = materialData.ambient;
				material.diffuse = materialData.diffuse;
				material.specular = materialData.specular;

				for (int i = 0; i < maps.size(); i++)
				{
					int slot = -1;

					switch (maps[i].type)
					{
					case MapType::DIFFUSE: slot = 0; break;
					case MapType::NORMAL: slot = 1; break;
					case MapType::METALLIC: slot = 2; break;
					case MapType::ROUGHNESS: slot = 3; break;
					case MapType::AMBIENTOCCLUSION: slot = 4; break;
					}

					if (slot >= 0)
						maps[i].map->SetUpTexture(slot, ShaderType::PIXEL);
				}

				break;
			}

			for (int i = 0; i < onceBuffer.size(); i++)
				onceBuffer[i].buffer->SetUpBuffer(onceBuffer[i].slot, onceBuffer[i].data, onceBuffer[i].type);

			if (materialBuffer.buffer != nullptr)
				materialBuffer.buffer->SetUpBuffer(materialBuffer.slot, materialBuffer.data, materialBuffer.type);

			const std::vector<MeshBase*>& meshes = model->GetMeshes();

			for (int i = 0; i < meshes.size(); i++)
			{
				cbMatrix cb;
				cb.worldTransform = MatrixTranspose(meshes[i]->GetTransform().GetWorldTransform());
				cb.worldInvTransform = MatrixInverse(meshes[i]->GetTransform().GetWorldTransform());

				matrixBuffer.buffer->SetUpBuffer(matrixBuffer.slot, &cb, ShaderType::VERTEX);

				engine->DrawMesh(vertexBuffers[i], meshes[i]->GetIndexBuffer());
			}
		}

		friend GraphicsEngine;
	};

	template<typename T>
	inline void PrefabBase::CreateVertexBuffer(FactoryBase* factory, std::function<T(const VertexData&)> vertexConstructor)
	{
		if (model == nullptr)
			return;

		const std::vector<MeshBase*>& meshes = model->GetMeshes();

		struct SkinningData
		{
			Vector position;
			Vector weights1;
			Vector weights2;
			Vector weights3;
			Vector weights4;
			unsigned int weightIndex1;
			unsigned int weightIndex2;
			unsigned int weightIndex3;
			unsigned int weightIndex4;
		};

		for (int i = 0; i < meshes.size(); i++)
		{
			std::vector<T> vertices;
			std::vector<Vector> shadowVertices;
			std::vector<SkinningData> shadowSkinningVertices;

			const std::vector<VertexData>& vertexData = meshes[i]->GetVertexData();

			for (int j = 0; j < vertexData.size(); j++)
			{
				vertices.push_back(vertexConstructor(vertexData[j]));

				if (isSkinning == true)
				{
					SkinningData temp;

					temp.position = vertexData[j].position;
					temp.weights1 = vertexData[j].weights1;
					temp.weights2 = vertexData[j].weights2;
					temp.weights3 = vertexData[j].weights3;
					temp.weights4 = vertexData[j].weights4;
					temp.weightIndex1 = vertexData[j].weightIndex1;
					temp.weightIndex2 = vertexData[j].weightIndex2;
					temp.weightIndex3 = vertexData[j].weightIndex3;
					temp.weightIndex4 = vertexData[j].weightIndex4;

					shadowSkinningVertices.push_back(temp);
				}
				else
				{
					shadowVertices.push_back(vertexData[j].position);
				}
			}

			BufferBase* vertexBuffer = factory->CreateVertexBuffer(
				meshes[i]->GetName() + "VB", USAGE::DEFAULT, 0, sizeof(T), vertices.data(), vertices.size());

			vertexBuffers.push_back(vertexBuffer);

			if (isSkinning == true)
			{
				BufferBase* shadowVertexBuffer = factory->CreateVertexBuffer(
					"Shadow" + meshes[i]->GetName() + "VB", USAGE::DEFAULT, 0, sizeof(SkinningData), shadowSkinningVertices.data(), shadowSkinningVertices.size());

				shadowVertexBuffers.push_back(shadowVertexBuffer);
			}
			else
			{
				BufferBase* shadowVertexBuffer = factory->CreateVertexBuffer(
					"Shadow" + meshes[i]->GetName() + "VB", USAGE::DEFAULT, 0, sizeof(Vector), shadowVertices.data(), shadowVertices.size());

				shadowVertexBuffers.push_back(shadowVertexBuffer);
			}
		}
	}
}