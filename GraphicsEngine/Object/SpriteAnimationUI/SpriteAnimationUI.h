/********************************
*								*
*	Sprite Animation UI.h		*
*								*
*	Created : 2022/08/25		*
*	Updated : 2022/08/25		*
*********************************/

#pragma once

#include "Bases/UIBase.h"
#include "Bases/GraphicsEngineBase.h"
#include "Object/SpriteAnimation/SpriteAnimation.h"

namespace GraphicsEngineSpace
{
	class Canvas;

	class SpriteAnimationUI : public UIBase
	{
		SpriteAnimation* texture;

	protected:
		SpriteAnimationUI();
		~SpriteAnimationUI() override;

	public:
		virtual void SetSpriteTexture(SpriteAnimation* texture);

	protected:
		void Render(GraphicsEngineBase* engine, float tick);

		friend Canvas;
	};
}