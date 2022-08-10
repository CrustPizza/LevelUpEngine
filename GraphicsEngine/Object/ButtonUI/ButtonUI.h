/********************************
*								*
*	Button UI.h					*
*								*
*	Created : 2022/08/10		*
*	Updated : 2022/08/10		*
*********************************/

#pragma once

#include <functional>
#include "Bases/UIBase.h"
#include "Bases/TextureBase.h"
#include "Bases/GraphicsEngineBase.h"

namespace GraphicsEngineSpace
{
	class Canvas;

	enum class ButtonState
	{
		DEFAULT,
		DOWN,
		UP,
		PRESS,
		HOVER
	};

	class ButtonUI : public UIBase
	{
		TextureBase* defaultTexture;
		TextureBase* hoverTexture;
		TextureBase* pressTexture;
		ButtonState buttonState;

		std::function<void(void)> clickEvent;

	protected:
		ButtonUI();
		~ButtonUI() override;

	public:
		void SetDefaultTexture(TextureBase* texture);
		void SetHoverTexture(TextureBase* texture);
		void SetPressTexture(TextureBase* texture);
		void SetButtonState(ButtonState state);
		void SetClickEvent(std::function<void(void)> clickEvent);

		ButtonState GetButtonState();

		void Render(GraphicsEngineBase* engine);

		friend Canvas;
	};
}