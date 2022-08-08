/********************************
*								*
*	UI Base.h					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#pragma once

#include "Bases/ResourceBase.h"

namespace GraphicsEngineSpace
{
	enum class VerticalPivot
	{
		TOP,
		MIDDLE,
		BOTTOM,
		STRETCH
	};

	enum class HorizontalPivot
	{
		LEFT,
		CENTER,
		RIGHT,
		STRETCH
	};

	class UIBase : public ResourceBase<UIBase>
	{
		VerticalPivot vPivot;
		HorizontalPivot hPivot;

		float width;
		float height;

	public:
		UIBase(VerticalPivot vPivot = VerticalPivot::MIDDLE, HorizontalPivot hPivot = HorizontalPivot::CENTER)
			: vPivot(vPivot)
			, hPivot(hPivot)
			, width(0.0f)
			, height(0.0f) {}
		virtual ~UIBase() = default;
	};
}