/********************************
*								*
*	Bone Base.h					*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/08/03		*
*********************************/

#pragma once

#include <map>
#include <string>
#include "Bases/ObjectBase.h"
#include "Bases/MeshBase.h"
#include "Bases/AnimationBase.h"

namespace GraphicsEngineSpace
{
	class BoneBase : public ObjectBase
	{
		std::map<std::string, AnimationBase*> animations;
		Matrix offset;

	public:
		BoneBase() = default;
		virtual ~BoneBase()
		{
			for (auto iter : animations)
			{
				if (iter.second != nullptr)
					delete iter.second;
			}
		}

		bool UpdateAnimation(const std::string& animationKey, float tick)
		{
			auto result = animations.find(animationKey);

			if (result == animations.end())
				return false;

			GetTransform().ResetLocation();

			return result->second->UpdateAnimation(&GetTransform(), tick);
		}

		void SetOffSet(const Matrix& offset)
		{
			this->offset = offset;
		}

		Matrix GetBoneMatrix()
		{
			return offset * GetTransform().GetWorldTransform();
		}

		Matrix GetBoneMatrix(const Matrix& worldTransform)
		{
			return offset * worldTransform;
		}

		void ConvertMeshToBone(MeshBase* const mesh)
		{
			auto& meshAnimations = mesh->GetAnimation();

			for (auto& iter : meshAnimations)
			{
				AnimationBase* animation = iter.second;

				auto isAlready = animations.find(iter.first);

				if (isAlready != animations.end())
				{
					delete animation;

					continue;
				}

				animations[iter.first] = animation;
			}

			meshAnimations.clear();

			this->SetName(mesh->GetName());
			this->SetParentName(mesh->GetParentName());
			this->GetTransform().DecomposeWorldTransform(mesh->GetTransform().GetWorldTransform());

			if (mesh->GetIndexBuffer() != nullptr)
				mesh->GetIndexBuffer()->Release();
		}

		friend ASEBuilder;
	};
}