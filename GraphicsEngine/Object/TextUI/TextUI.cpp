/********************************
*								*
*	Text UI.cpp					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/20		*
*********************************/

#include "TextUI.h"

namespace GraphicsEngineSpace
{
	TextUI::TextUI()
		: text(L"Temp Text")
		, font{"±¼¸²"}
		, color{ 1.0f, 1.0f, 1.0f, 1.0f }
		, fontSize(16.0f)
	{

	}

	TextUI::~TextUI()
	{

	}

	void TextUI::SetText(const std::string& text)
	{
		this->text.assign(text.begin(), text.end());

		width = text.size() * (fontSize - 1.0f);
		height = fontSize;
	}

	void TextUI::SetText(const std::wstring& text)
	{
		this->text = text;

		width = text.size() * (fontSize - 1.0f);
		height = fontSize;
	}

	void TextUI::SetColor(const Vector& color)
	{
		this->color = color;
	}

	void TextUI::SetFont(const std::string& fontName)
	{
		font = fontName;
	}

	void TextUI::SetFontSize(float fontSize)
	{
		if (fontSize < 0.0f)
			this->fontSize = 0.0f;
		else
			this->fontSize = fontSize;

		width = text.size() * (this->fontSize - 1.0f);
		height = this->fontSize;
	}

	std::string TextUI::GetText()
	{
		std::string ret;
		ret.assign(text.begin(), text.end());

		return ret;
	}

	void TextUI::Render(GraphicsEngineBase* engine, float tick)
	{
		if (isEnable != true || engine == nullptr)
			return;

		engine->GraphicsDebugBeginEvent(name);

		engine->DrawTextColor(font, text, color, GetScreenPosition(), 0.0f, Vector{ fontSize / 32.0f, fontSize / 32.0f } * GetScreenScale());

		for (auto* iter : child)
		{
			if (iter != nullptr)
				iter->Render(engine);
		}

		engine->GraphicsDebugEndEvent();
	}
}