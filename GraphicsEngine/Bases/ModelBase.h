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
for (auto iter : (m))\
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

		std::vector<MeshBase*> meshes;
		std::vector<BoneBase*> bones;
		std::vector<ShapeBase*> shapes;
		std::vector<HelperBase*> helpers;
		std::map<int, MaterialBase*> materials;

		ObjectBase emptyObject;
		std::string animationKey;
		float totalAnimTime;

	public:
		ModelBase()
			: totalAnimTime(0.0f) {}
		virtual ~ModelBase()
		{
			RELEASE_VECTOR(meshes);
			RELEASE_VECTOR(bones);
			RELEASE_VECTOR(shapes);
			RELEASE_VECTOR(helpers);
			RELEASE_MAP(materials);
		}

		void SetAnimationKey(const std::string& animationKey)
		{
			if (this->animationKey.compare(animationKey) == 0)
				return;

			this->animationKey = animationKey;
			totalAnimTime = 0.0f;
		}

		void SetupData(const Matrix& worldTransform, float animTime = 0.0f)
		{
			bool timeReset = true;

			totalAnimTime += animTime;

			for (auto iter : helpers)
			{
				if (iter->UpdateAnimation(animationKey, totalAnimTime) == true)
					timeReset = false;
			}

			for (auto iter : meshes)
			{
				if (iter->UpdateAnimation(animationKey, totalAnimTime) == true)
					timeReset = false;
			}
			
			for (auto iter : bones)
			{
				if (iter->UpdateAnimation(animationKey, totalAnimTime) == true)
					timeReset = false;
			}

			if (timeReset == true)
				totalAnimTime = 0.0f;

			Transform* transform = &emptyObject.GetTransform();

			transform->SetWorldTransform(worldTransform);

			for (auto* iter : emptyObject.GetChild())
				iter->PrepareRender();
		}

		const std::vector<MeshBase*>& GetMeshes() { return meshes; }
		const std::vector<BoneBase*>& GetBones() { return bones; }
		const std::map<int, MaterialBase*>& GetMaterials() { return materials; }

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