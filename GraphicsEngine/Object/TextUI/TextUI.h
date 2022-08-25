/********************************
*								*
*	Text UI.h					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/20		*
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
		std::wstring text;
		std::string font;
		Vector color;
		float fontSize;

	protected:
		TextUI();
		~TextUI() override;

	public:
		virtual void SetText(const std::string& text);
		virtual void SetText(const std::wstring& text);
		virtual void SetColor(const Vector& color);
		virtual void SetFont(const std::string& fontName);
		virtual void SetFontSize(float fontSize);

		virtual std::string GetText();

	protected:
		void Render(GraphicsEngineBase* engine, float tick) override;

		friend Canvas;
	};
}