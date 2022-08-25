/********************************
*								*
*	Font Base.h					*
*								*
*	Created : 2022/08/17		*
*	Updated : 2022/08/17		*
*********************************/

#pragma once

#include <string>
#include "Bases/ResourceBase.h"
#include "../HeraclesMath/HeraclesMath.h"

namespace GraphicsEngineSpace
{
	using namespace HeraclesMath;

	class FontBase : public ResourceBase<FontBase>
	{
	public:
		FontBase() = default;
		virtual ~FontBase() = default;

		virtual bool DrawTextColor(const std::string& text, Vector color, Vector position, float rotation = 0.0f, Vector scale = { 1.0f, 1.0f }) abstract;
		virtual bool DrawTextColor(const std::wstring& text, Vector color, Vector position, float rotation = 0.0f, Vector scale = { 1.0f, 1.0f }) abstract;
		virtual void SetLineSpacing(float size) abstract;
	};
}