/********************************
*								*
*	Sprite Animation UI.cpp		*
*								*
*	Created : 2022/08/25		*
*	Updated : 2022/08/25		*
*********************************/

#include "SpriteAnimationUI.h"

namespace GraphicsEngineSpace
{
	SpriteAnimationUI::SpriteAnimationUI()
		: texture(nullptr)
	{

	}

	SpriteAnimationUI::~SpriteAnimationUI()
	{

	}

	void SpriteAnimationUI::SetSpriteTexture(SpriteAnimation* texture)
	{
		this->texture = texture;
	}

	void SpriteAnimationUI::Render(GraphicsEngineBase* engine, float tick)
	{
		if (isEnable != true || engine == nullptr)
			return;

		engine->GraphicsDebugBeginEvent(name);

		if (texture != nullptr)
		{
			auto screenPosition = GetScreenPosition();
			auto screenScale = GetScreenScale();

			texture->SetPosition(screenPosition);
			texture->SetScale(screenScale);

			texture->Render(engine, tick);
		}

		for (auto* iter : child)
		{
			if (iter != nullptr)
				iter->Render(engine);
		}

		engine->GraphicsDebugEndEvent();
	}
}