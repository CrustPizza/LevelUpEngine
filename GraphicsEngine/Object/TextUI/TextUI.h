/********************************
*								*
*	Text UI.h					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/09		*
*********************************/

#pragma once

#include <string>
#include "Bases/UIBase.h"
#include "Bases/GraphicsEngineBase.h"

namespace GraphicsEngineSpace
{
	class Canvas;

	class TextUI : public UIBase
	{
		std::string text;
		Vector color;
		float fontSize;

	protected:
		TextUI();
		~TextUI() override;

	public:
		virtual void SetText(const std::string& text);
		virtual void SetColor(const Vector& color);
		void Render(GraphicsEngineBase* engine);

		friend Canvas;
	};
}