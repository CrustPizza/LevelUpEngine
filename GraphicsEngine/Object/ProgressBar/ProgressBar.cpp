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
		: texture(nullptr)
		, front{}
		, back{}
		, dir(Direction::LEFT)
		, percent(1.0f)
	{

	}

	ProgressBar::~ProgressBar()
	{

	}

	void ProgressBar::SetTexture(TextureBase* texture)
	{
		this->texture = texture;
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

	void ProgressBar::Render(GraphicsEngineBase* engine)
	{
		if (isEnable != true || engine == nullptr)
			return;

		auto screenPosition = GetScreenPosition();

		Rect dest =
		{
			screenPosition.x,
			screenPosition.y,
			screenPosition.x + width * GetScale().x,
			screenPosition.y + height * GetScale().y
		};

		engine->DrawSprite(texture->GetTexture(), dest, back, screenPosition.z);

		Rect frontSrc = front;

		switch (dir)
		{

		case Direction::LEFT:
		{
			dest.right = dest.left + width * GetScale().x * percent;
			frontSrc.right = frontSrc.left + front.GetWidth() * percent;

			break;
		}

		case Direction::RIGHT:
		{
			dest.left = dest.right - width * GetScale().x * percent;
			frontSrc.left = frontSrc.right - front.GetWidth() * percent;

			break;
		}

		case Direction::UP:
		{
			dest.bottom = dest.top + height * GetScale().y * percent;
			frontSrc.bottom = frontSrc.top + front.GetHeight() * percent;

			break;
		}

		case Direction::DOWN:
		{
			dest.top = dest.bottom - height * GetScale().y * percent;
			frontSrc.top = frontSrc.bottom - front.GetHeight() * percent;

			break;
		}

		}

		engine->DrawSprite(texture->GetTexture(), dest, frontSrc, screenPosition.z);

		for (auto* iter : child)
		{
			if (iter != nullptr)
				iter->Render(engine);
		}
	}
}