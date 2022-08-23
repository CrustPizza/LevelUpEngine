/********************************
*								*
*	Model Base.h				*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/08/02		*
*********************************/

#pragma once

#include "Bases/MeshBase.h"
#include "Bases/BoneBase.h"
#include "Bases/ShapeBase.h"
#include "Bases/HelperBase.h"
#include "Bases/MaterialBase.h"

namespace GraphicsEngineSpace
{
#pragma region Release_Macro_Implementation
#define RELEASE_VECTOR(v) \
for (auto* iter : (v))\
{\
	if (iter != nullptr)\
		delete iter;\
}

#define RELEASE_MAP(m) \
for (auto& iter : (m))\
{\
	if (iter.second != nullptr)\
		delete iter.second;\
}
#pragma endregion

	class ASEBuilder;

	class ModelBase : public ResourceBase<ModelBase>
	{
#pragma region Parent_Macro_Implementation
#define CHECK_PARENT(element) \
if (##element->GetParentName().length() == 0)\
{\
	element->SetupAttachment(&emptyObject);\
	continue;\
}

#define FIND_PARENT(element) \
ObjectBase* parent = FindParent(##element->GetParentName());\
if (parent == nullptr) continue;\
element->SetupAttachment(parent);
#pragma endregion

		std::string modelName;

		std::vector<MeshBase*> meshes;
		std::vector<BoneBase*> bones;
		std::vector<ShapeBase*> shapes;
		std::vector<HelperBase*> helpers;
		std::map<int, MaterialBase*> materials;

		ObjectBase emptyObject;
		std::vector<std::string> animationKeys;
		std::string animationKey;

		Matrix* boneMatrix;
		Matrix rotationMatrix;

		Vector boundingBoxMin;
		Vector boundingBoxMax;

	public:
		ModelBase()
			: boneMatrix(nullptr)
			, rotationMatrix(Matrix::Identity)
			, boundingBoxMin{ 0.0f, 0.0f, 0.0f, 1.0f }
			, boundingBoxMax{ 0.0f, 0.0f, 0.0f, 1.0f }
			, animationKey{} {}
		virtual ~ModelBase()
		{
			RELEASE_VECTOR(meshes);
			RELEASE_VECTOR(bones);
			RELEASE_VECTOR(shapes);
			RELEASE_VECTOR(helpers);
			RELEASE_MAP(materials);

			if (boneMatrix != nullptr)
				delete boneMatrix;
		}

		Vector GetBoundingBoxCenter()
		{
			return (boundingBoxMin + boundingBoxMax) / 2.0f;
		}

		Vector GetBoundingBoxScale()
		{
			return boundingBoxMax - boundingBoxMin;
		}

		void SetMetallicMap(TextureBase* metallicMap)
		{
			for (auto& material : materials)
			{
				auto& maps = material.second->GetMaterialData().maps;

				for (auto& map : maps)
				{
					if (map.type == MapType::METALLIC)
					{
						map.map = metallicMap;
						return;
					}
				}

				MapData temp;

				temp.map = metallicMap;
				temp.type = MapType::METALLIC;

				maps.push_back(temp);

				break;
			}
		}

		void SetRoughnessMap(TextureBase* roughnessMap)
		{
			for (auto& material : materials)
			{
				auto& maps = material.second->GetMaterialData().maps;

				for (auto& map : maps)
				{
					if (map.type == MapType::ROUGHNESS)
					{
						map.map = roughnessMap;
						return;
					}
				}

				MapData temp;

				temp.map = roughnessMap;
				temp.type = MapType::ROUGHNESS;

				maps.push_back(temp);

				break;
			}
		}

		void SetAmbientOcclusionMap(TextureBase* ambientOcclusionMap)
		{
			for (auto& material : materials)
			{
				auto& maps = material.second->GetMaterialData().maps;

				for (auto& map : maps)
				{
					if (map.type == MapType::AMBIENTOCCLUSION)
					{
						map.map = ambientOcclusionMap;
						return;
					}
				}

				MapData temp;

				temp.map = ambientOcclusionMap;
				temp.type = MapType::AMBIENTOCCLUSION;

				maps.push_back(temp);

				break;
			}
		}

		void AddAnimation(const std::string& animationKey)
		{
			if (IsAlreadyHaveAnimation(animationKey) == true)
				return;

			animationKeys.push_back(animationKey);
		}

		bool SetAnimationKey(const std::string& animationKey)
		{
			if (this->animationKey.compare(animationKey) == 0)
				return false;

			this->animationKey = animationKey;

			return true;
		}

		bool PrepareRender(const Matrix& worldTransform, float animTime = 0.0f)
		{
			bool timeReset = true;

			for (auto* iter : helpers)
			{
				if (iter->UpdateAnimation(animationKey, animTime) == true)
					timeReset = false;
			}

			for (auto* iter : meshes)
			{
				if (iter->UpdateAnimation(animationKey, animTime) == true)
					timeReset = false;
			}
			
			for (auto* iter : bones)
			{
				if (iter->UpdateAnimation(animationKey, animTime) == true)
					timeReset = false;
			}

			if (timeReset == true)
			{
				for (auto* iter : helpers)
					iter->UpdateAnimation(animationKey, -1.0f);

				for (auto* iter : meshes)
					iter->UpdateAnimation(animationKey, -1.0f);

				for (auto* iter : bones)
					iter->UpdateAnimation(animationKey, -1.0f);
			}

			Transform* transform = &emptyObject.GetTransform();

			transform->SetWorldTransform(rotationMatrix * worldTransform);

			for (auto* iter : emptyObject.GetChild())
				iter->PrepareRender();

			if (boneMatrix != nullptr)
			{
				for (int i = 0; i < bones.size() && i < 64; i++)
					boneMatrix[i] = MatrixTranspose(bones[i]->GetBoneMatrix());
			}

			return timeReset;
		}
		void SetName(const std::string& name) { this->modelName = name; }

		const std::string& GetName() { return modelName; }
		const std::vector<MeshBase*>& GetMeshes() { return meshes; }
		const std::vector<BoneBase*>& GetBones() { return bones; }
		const std::map<int, MaterialBase*>& GetMaterials() { return materials; }
		Matrix* GetBoneMatrix() { return boneMatrix; }

		bool IsAlreadyHaveAnimation(const std::string& animationKey)
		{
			for (int i = 0; i < animationKeys.size(); i++)
			{
				if (animationKeys[i].compare(animationKey) == 0)
					return true;
			}

			return false;
		}

		void SetRotation(const Vector& rotation) { this->rotationMatrix = MatrixRotationFromVector(rotation); }

	private:
		void SetHierarchy()
		{
			// Helper
			for (int i = 0; i < helpers.size(); i++)
			{
				CHECK_PARENT(helpers[i]);
				FIND_PARENT(helpers[i]);
			}

			// Shape
			for (int i = 0; i < shapes.size(); i++)
			{
				CHECK_PARENT(shapes[i]);
				FIND_PARENT(shapes[i]);
			}

			// Mesh
			for (int i = 0; i < meshes.size(); i++)
			{
				CHECK_PARENT(meshes[i]);
				FIND_PARENT(meshes[i]);
			}

			// Bones
			for (int i = 0; i < bones.size(); i++)
			{
				CHECK_PARENT(bones[i]);
				FIND_PARENT(bones[i]);
			}
		}

		ObjectBase* FindParent(const std::string& parentName)
		{
			for (int i = 0; i < helpers.size(); i++)
			{
				if (parentName.compare(helpers[i]->GetName()) == 0)
					return helpers[i];
			}

			for (int i = 0; i < shapes.size(); i++)
			{
				if (parentName.compare(shapes[i]->GetName()) == 0)
					return shapes[i];
			}

			for (int i = 0; i < meshes.size(); i++)
			{
				if (parentName.compare(meshes[i]->GetName()) == 0)
					return meshes[i];
			}

			for (int i = 0; i < bones.size(); i++)
			{
				if (parentName.compare(bones[i]->GetName()) == 0)
					return bones[i];
			}

			return nullptr;
		}

		friend ASEBuilder;
	};
}