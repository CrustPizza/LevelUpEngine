/********************************
*								*
*	Button UI.cpp				*
*								*
*	Created : 2022/08/10		*
*	Updated : 2022/08/20		*
*********************************/

#include "ButtonUI.h"
#include <Windows.h>

namespace GraphicsEngineSpace
{
	ButtonUI::ButtonUI()
		: defaultTexture(nullptr)
		, hoverTexture(nullptr)
		, pressTexture(nullptr)
		, buttonState(ButtonState::DEFAULT)
		, clickEvent(nullptr)
		, hoverEvent(nullptr)
		, hoverOutEvent(nullptr)
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
		if (buttonState == ButtonState::HOVER && state != ButtonState::HOVER)
		{
			if (hoverOutEvent != nullptr)
				hoverOutEvent();
		}

		switch (state)
		{
		case ButtonState::UP: if (clickEvent != nullptr) clickEvent(); break;
		case ButtonState::HOVER: if (hoverEvent != nullptr) hoverEvent(); break;
		}

		buttonState = state;
	}

	void ButtonUI::SetClickEvent(std::function<void(void)> clickEvent)
	{
		this->clickEvent = clickEvent;
	}

	void ButtonUI::SetHoverEvent(std::function<void(void)> hoverEvent)
	{
		this->hoverEvent = hoverEvent;
	}

	void ButtonUI::SetHoverOutEvent(std::function<void(void)> hoverOutEvent)
	{
		this->hoverOutEvent = hoverOutEvent;
	}

	ButtonState ButtonUI::GetButtonState()
	{
		return buttonState;
	}

	void ButtonUI::Render(GraphicsEngineBase* engine, float tick)
	{
		if (isEnable != true || engine == nullptr)
			return;

		engine->GraphicsDebugBeginEvent(name);

		Texture* texture = nullptr;

		if (defaultTexture != nullptr)
			texture = defaultTexture->GetTexture();

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

		if (texture != nullptr)
		{
			auto screenPosition = GetScreenPosition();
			auto screenScale = GetScreenScale();

			engine->DrawSprite(texture, screenPosition.x, screenPosition.y, width * screenScale.x, height * screenScale.y, screenPosition.z);
		}

		for (auto* iter : child)
		{
			if (iter != nullptr)
				iter->Render(engine);
		}

		engine->GraphicsDebugEndEvent();
	}
}