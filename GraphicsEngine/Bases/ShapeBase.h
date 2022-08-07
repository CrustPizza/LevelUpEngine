/********************************
*								*
*	Shape Base.h				*
*								*
*	Created : 2022/07/15		*
*	Updated : 2022/07/19		*
*********************************/

#pragma once

#include <vector>
#include <string>
#include "Bases/ObjectBase.h"
#include "Bases/AnimationBase.h"
#include "Transform/Transform.h"

namespace GraphicsEngineSpace
{
	class ASEBuilder;

	class ShapeBase : public ObjectBase
	{
		std::map<std::string, AnimationBase*> animations;

	public:
		ShapeBase() = default;
		virtual ~ShapeBase()
		{
			for (auto iter : animations)
			{
				if (iter.second != nullptr)
					delete iter.second;
			}
		}

	protected:

		friend ASEBuilder;
	};
}