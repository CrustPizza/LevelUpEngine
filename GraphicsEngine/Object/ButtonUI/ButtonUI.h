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
		virtual void SetDefaultTexture(TextureBase* texture);
		virtual void SetHoverTexture(TextureBase* texture);
		virtual void SetPressTexture(TextureBase* texture);
		virtual void SetButtonState(ButtonState state);
		virtual void SetClickEvent(std::function<void(void)> clickEvent);

		virtual ButtonState GetButtonState();

		void Render(GraphicsEngineBase* engine);

		friend Canvas;
	};
}