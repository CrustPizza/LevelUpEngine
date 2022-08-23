/********************************
*								*
*	Helper Base.h				*
*								*
*	Created : 2022/07/15		*
*	Updated : 2022/08/03		*
*********************************/

#pragma once

#include <vector>
#include <string>
#include "Bases/ObjectBase.h"
#include "Bases/AnimationBase.h"
#include "Bases/MeshBase.h"
#include "Transform/Transform.h"

namespace GraphicsEngineSpace
{
	class ASEBuilder;

	class HelperBase : public ObjectBase
	{
		std::map<std::string, AnimationBase*> animations;

	public:
		HelperBase() = default;
		virtual ~HelperBase()
		{
			for (auto iter : animations)
			{
				if (iter.second != nullptr)
					delete iter.second;
			}
		}

		bool UpdateAnimation(const std::string& animationKey, float tick)
		{
			GetTransform().ResetLocation();

			auto result = animations.find(animationKey);

			if (result == animations.end())
				return false;

			bool temp = result->second->UpdateAnimation(&GetTransform(), tick);

			return temp;
		}

		void ConvertMeshToHelper(MeshBase* const mesh)
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

	protected:

		friend ASEBuilder;
	};
}