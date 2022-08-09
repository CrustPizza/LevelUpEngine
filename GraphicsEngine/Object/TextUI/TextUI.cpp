/********************************
*								*
*	Text UI.cpp					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/09		*
*********************************/

#include "TextUI.h"

namespace GraphicsEngineSpace
{
	TextUI::TextUI()
		: text("Temp Text")
		, color{ 0.0f, 0.0f, 0.0f }
		, fontSize(14.0f)
	{

	}

	TextUI::~TextUI()
	{

	}

	void TextUI::SetText(const std::string& text)
	{
		this->text = text;
	}

	void TextUI::SetColor(const Vector& color)
	{
		this->color = color;
	}

	void TextUI::Render(GraphicsEngineBase* engine)
	{
		engine->DrawTextColor(text, color, GetScreenPosition(), 0.0f, Vector{ fontSize / 14.0f, fontSize / 14.0f } * scale);
	}
}