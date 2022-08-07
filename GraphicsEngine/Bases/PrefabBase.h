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
		float totalAnimationTime;

		ShaderBase* vertexShader;
		ShaderBase* pixelShader;

		std::vector<BufferBase*> vertexBuffers;
		std::vector<ConstantBufferSetting> onceBuffer;
		const ConstantBufferSetting matrixBuffer;
		ConstantBufferSetting materialBuffer;

	public:
		PrefabBase(ModelBase* model, const ConstantBufferSetting& matrixBuffer)
			: model(model)
			, totalAnimationTime(0.0f)
			, vertexShader(nullptr)
			, pixelShader(nullptr)
			, matrixBuffer(matrixBuffer)
			, materialBuffer{} {}
		virtual ~PrefabBase() = default;

		const std::map<int, MaterialBase*>& GetMaterials() { return model->GetMaterials(); }

		void SetVertexShader(ShaderBase* shader) { this->vertexShader = shader; }
		void SetPixelShader(ShaderBase* shader) { this->pixelShader = shader; }
		void AddOnceBuffer(const ConstantBufferSetting& buffer) { onceBuffer.push_back(buffer); }
		void SetMaterialBuffer(const ConstantBufferSetting& materialBuffer) { this->materialBuffer = materialBuffer; }

		template <typename T>
		void CreateVertexBuffer(FactoryBase* factory, std::function<T(const VertexData&)> vertexConstructor);

		void Render(GraphicsEngineBase* engine, const Matrix& worldTransform, float tick = 0.0f)
		{
			if (model == nullptr)
				assert(0);

			totalAnimationTime += tick;

			if (model->PrepareRender(worldTransform, totalAnimationTime) == true)
				totalAnimationTime = 0.0f;

			if (vertexShader != nullptr)
				vertexShader->SetUpShader();

			if (pixelShader != nullptr)
				pixelShader->SetUpShader();

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
	};

	template<typename T>
	inline void PrefabBase::CreateVertexBuffer(FactoryBase* factory, std::function<T(const VertexData&)> vertexConstructor)
	{
		if (model == nullptr)
			return;

		const std::vector<MeshBase*>& meshes = model->GetMeshes();

		for (int i = 0; i < meshes.size(); i++)
		{
			std::vector<T> vertices;
			const std::vector<VertexData>& vertexData = meshes[i]->GetVertexData();

			for (int j = 0; j < vertexData.size(); j++)
				vertices.push_back(vertexConstructor(vertexData[j]));

			BufferBase* vertexBuffer = factory->CreateVertexBuffer(
				meshes[i]->GetName() + "VB", USAGE::DEFAULT, 0, sizeof(T), vertices.data(), vertices.size());

			vertexBuffers.push_back(vertexBuffer);
		}
	}
}