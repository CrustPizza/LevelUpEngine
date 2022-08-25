/********************************
*								*
*	Progress Bar.h				*
*								*
*	Created : 2022/08/10		*
*	Updated : 2022/08/10		*
*********************************/

#pragma once

#include "Bases/UIBase.h"
#include "Bases/TextureBase.h"
#include "Bases/GraphicsEngineBase.h"

namespace GraphicsEngineSpace
{
	class Canvas;

	enum class Direction
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	class ProgressBar : public UIBase
	{
		TextureBase* frontBarTexture;
		TextureBase* backBarTexture;

		Rect front;
		Rect back;

		Direction dir;
		float percent;

	protected:
		ProgressBar();
		~ProgressBar() override;

	public:
		virtual void SetFrontTexture(TextureBase* texture);
		virtual void SetBackTexture(TextureBase* texture);
		virtual void SetPercent(float percent);
		virtual void SetDirection(Direction direction);

		virtual void SetFrontBarTexCoord(float x, float y, float width, float height);
		virtual void SetBackBarTexCoord(float x, float y, float width, float height);

	protected:
		void Render(GraphicsEngineBase* engine, float tick) override;

		friend Canvas;
	};
}