/********************************
*								*
*	Object Base.h				*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#pragma once

#include <vector>
#include "Component/Transform/Transform.h"
#include "../GraphicsEngine/GraphicsEngineFramework.h"

namespace GameEngineSpace
{
	class ObjectBase
	{
	protected:
		Transform transform;

		ObjectBase* parent;
		std::vector<ObjectBase*> child;

	public:

		virtual void Update(float tick) abstract;
		virtual void Render(GraphicsEngineSpace::GraphicsEngineBase* engine) abstract;

		Transform& GetTransform();
		ObjectBase* GetParent();
		std::vector<ObjectBase*>& GetChild();

		void SetupAttachment(ObjectBase* parent);
		void UnsetAttachment(ObjectBase* child);
		void Detachment();
	};
}