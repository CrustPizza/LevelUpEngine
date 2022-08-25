/********************************
*								*
*	Sprite Animation.h			*
*								*
*	Created : 2022/08/09		*
*	Updated : 2022/08/25		*
*********************************/

#pragma once

#include <vector>
#include "Bases/TextureBase.h"
#include "Bases/GraphicsEngineBase.h"

namespace GraphicsEngineSpace
{
	class SpriteAnimation : public ResourceBase<SpriteAnimation>
	{
		struct AnimationFrame
		{
			float left;
			float top;
			float right;
			float bottom;

			float tick;
		};

		std::vector<AnimationFrame> frames;
		TextureBase* texture;
		float textureWidth;
		float textureHeight;

		bool isLoop;
		Vector position;
		Vector scale;

		float width;
		float height;
		float totalAnimTime;

	public:
		SpriteAnimation();
		~SpriteAnimation() override;

		bool GetLoop();
		const Vector& GetPosition();

		virtual void SetLoop(bool loop);
		virtual void SetWidth(float width);
		virtual void SetHeight(float height);
		virtual void SetPosition(const Vector& position);
		virtual void SetScale(const Vector& scale);
		virtual void SetTexture(TextureBase* texture, float width, float height, int frameX, int frameY, float framePerSec);

		virtual void Render(GraphicsEngineBase* engine, float tick = 0.0f);
		virtual void Render(GraphicsEngineBase* engine, const Matrix& viewProjection, float tick = 0.0f);
		virtual void Render(GraphicsEngineBase* engine, const Matrix& viewProjection, const Vector& viewPosition, float tick = 0.0f);
	};
}