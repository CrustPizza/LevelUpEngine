/********************************
*								*
*	Button UI.cpp				*
*								*
*	Created : 2022/08/10		*
*	Updated : 2022/08/10		*
*********************************/

#include "ButtonUI.h"

namespace GraphicsEngineSpace
{
	ButtonUI::ButtonUI()
		: defaultTexture(nullptr)
		, hoverTexture(nullptr)
		, pressTexture(nullptr)
		, buttonState(ButtonState::DEFAULT)
		, clickEvent(nullptr)
	{

	}

	ButtonUI::~ButtonUI()
	{

	}

	void ButtonUI::SetDefaultTexture(TextureBase* texture)
	{
		this->defaultTexture = texture;
	}

	void ButtonUI::SetHoverTexture(TextureBase* texture)
	{
		this->hoverTexture = texture;
	}

	void ButtonUI::SetPressTexture(TextureBase* texture)
	{
		this->pressTexture = texture;
	}

	void ButtonUI::SetButtonState(ButtonState state)
	{
		buttonState = state;

		switch (state)
		{
		case ButtonState::UP: if (clickEvent != nullptr) clickEvent(); break;
		}
	}

	void ButtonUI::SetClickEvent(std::function<void(void)> clickEvent)
	{
		this->clickEvent = clickEvent;
	}

	ButtonState ButtonUI::GetButtonState()
	{
		return buttonState;
	}

	void ButtonUI::Render(GraphicsEngineBase* engine)
	{
		if (isEnable != true || engine == nullptr)
			return;

		Texture* texture = defaultTexture->GetTexture();

		switch (buttonState)
		{

		case ButtonState::DOWN:
		case ButtonState::PRESS:
		{
			if (pressTexture != nullptr)
				texture = pressTexture->GetTexture();

			break;
		}
		
		case ButtonState::UP:
		case ButtonState::HOVER:
		{
			if (hoverTexture != nullptr)
				texture = hoverTexture->GetTexture();

			break;
		}

		}

		auto screenPosition = GetScreenPosition();

		engine->DrawSprite(texture, screenPosition.x, screenPosition.y, width, height, screenPosition.z);

		for (auto* iter : child)
		{
			if (iter != nullptr)
				iter->Render(engine);
		}
	}
}