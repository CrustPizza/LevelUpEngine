/********************************
*								*
*	Progress Bar.cpp			*
*								*
*	Created : 2022/08/10		*
*	Updated : 2022/08/10		*
*********************************/

#include "ProgressBar.h"

namespace GraphicsEngineSpace
{
	ProgressBar::ProgressBar()
		: frontBarTexture(nullptr)
		, backBarTexture(nullptr)
		, front{}
		, back{}
		, dir(Direction::LEFT)
		, percent(1.0f)
	{

	}

	ProgressBar::~ProgressBar()
	{

	}

	void ProgressBar::SetFrontTexture(TextureBase* texture)
	{
		this->frontBarTexture = texture;
	}

	void ProgressBar::SetBackTexture(TextureBase* texture)
	{
		this->backBarTexture = texture;
	}

	void ProgressBar::SetPercent(float percent)
	{
		if (percent > 1.0f)
			this->percent = 1.0f;
		else if (percent < 0.0f)
			this->percent = 0.0f;
		else
			this->percent = percent;
	}

	void ProgressBar::SetDirection(Direction direction)
	{
		dir = direction;
	}

	void ProgressBar::SetFrontBarTexCoord(float x, float y, float width, float height)
	{
		front.left = x;
		front.top = y;
		front.right = x + width;
		front.bottom = y + height;
	}

	void ProgressBar::SetBackBarTexCoord(float x, float y, float width, float height)
	{
		back.left = x;
		back.top = y;
		back.right = x + width;
		back.bottom = y + height;
	}

	void ProgressBar::Render(GraphicsEngineBase* engine, float tick)
	{
		if (isEnable != true || engine == nullptr)
			return;

		engine->GraphicsDebugBeginEvent(name);

		auto screenPosition = GetScreenPosition();
		auto screenScale = GetScreenScale();

		Rect dest =
		{
			screenPosition.x,
			screenPosition.y,
			screenPosition.x + width * screenScale.x,
			screenPosition.y + height * screenScale.y
		};

		engine->DrawSprite(backBarTexture->GetTexture(), dest, back, screenPosition.z);

		Rect frontSrc = front;

		switch (dir)
		{

		case Direction::LEFT:
		{
			dest.right = dest.left + width * screenScale.x * percent;
			frontSrc.right = frontSrc.left + front.GetWidth() * percent;

			break;
		}

		case Direction::RIGHT:
		{
			dest.left = dest.right - width * screenScale.x * percent;
			frontSrc.left = frontSrc.right - front.GetWidth() * percent;

			break;
		}

		case Direction::UP:
		{
			dest.bottom = dest.top + height * screenScale.y * percent;
			frontSrc.bottom = frontSrc.top + front.GetHeight() * percent;

			break;
		}

		case Direction::DOWN:
		{
			dest.top = dest.bottom - height * screenScale.y * percent;
			frontSrc.top = frontSrc.bottom - front.GetHeight() * percent;

			break;
		}

		}

		engine->DrawSprite(frontBarTexture->GetTexture(), dest, frontSrc, screenPosition.z);

		for (auto* iter : child)
		{
			if (iter != nullptr)
				iter->Render(engine);
		}

		engine->GraphicsDebugEndEvent();
	}
}