/********************************
*								*
*	Sprite Animation.CPP		*
*								*
*	Created : 2022/08/09		*
*	Updated : 2022/08/25		*
*********************************/

#include "SpriteAnimation.h"

namespace GraphicsEngineSpace
{
	SpriteAnimation::SpriteAnimation()
		: texture(nullptr)
		, textureWidth(0.0f)
		, textureHeight(0.0f)
		, isLoop(false)
		, position(Vector::UnitW)
		, scale({ 1.0f, 1.0f, 1.0f })
		, width(0.0f)
		, height(0.0f)
		, totalAnimTime(0.0f)
	{

	}

	SpriteAnimation::~SpriteAnimation()
	{

	}

	bool SpriteAnimation::GetLoop()
	{
		return isLoop;
	}

	const Vector& SpriteAnimation::GetPosition()
	{
		return position;
	}

	void SpriteAnimation::SetLoop(bool loop)
	{
		isLoop = loop;
	}

	void SpriteAnimation::SetWidth(float width)
	{
		this->width = width;
	}

	void SpriteAnimation::SetHeight(float height)
	{
		this->height = height;
	}

	void SpriteAnimation::SetPosition(const Vector& position)
	{
		this->position = position;
	}

	void SpriteAnimation::SetScale(const Vector& scale)
	{
		this->scale = scale;
	}

	void SpriteAnimation::SetTexture(TextureBase* texture, float width, float height, int frameX, int frameY, float framePerSec)
	{
		this->texture = texture;
		textureWidth = width;
		textureHeight = height;

		float totalTick = 0.0f;

		for (int y = 0; y < frameY; y++)
		{
			for (int x = 0; x < frameX; x++)
			{
				AnimationFrame temp;

				temp.left = static_cast<float>(x) / frameX;
				temp.top = static_cast<float>(y) / frameY;
				temp.right = static_cast<float>(x + 1) / frameX;
				temp.bottom = static_cast<float>(y + 1) / frameY;
				temp.tick = totalTick;

				frames.push_back(temp);

				totalTick += framePerSec;
			}
		}

		// End Frame
		frames.push_back({});
	}

	void SpriteAnimation::Render(GraphicsEngineBase* engine, float tick)
	{
		Rect dest =
		{
			position.x,
			position.y,
			position.x + width * scale.x,
			position.y + height * scale.y
		};

		Rect src;

		totalAnimTime += tick;

		for (int i = 1; i < frames.size(); i++)
		{
			if (totalAnimTime > frames[i].tick)
			{
				if (i + 1 != frames.size())
					continue;

				if (isLoop == true)
				{
					totalAnimTime = 0.0f;

					src.left = textureWidth * frames[0].left;
					src.top = textureHeight * frames[0].top;
					src.right = textureWidth * frames[0].right;
					src.bottom = textureHeight * frames[0].bottom;
				}

				break;
			}

			src.left = textureWidth * frames[i].left;
			src.top = textureHeight * frames[i].top;
			src.right = textureWidth * frames[i].right;
			src.bottom = textureHeight * frames[i].bottom;

			break;
		}

		engine->DrawSprite(texture->GetTexture(), dest, src, position.z);
	}

	void SpriteAnimation::Render(GraphicsEngineBase* engine, const Matrix& viewProjection, float tick)
	{
		Matrix worldViewProj = (MatrixScalingFromVector(scale) * MatrixTranslationFromVector(position)) * viewProjection;
		Vector texCoord[3] = {};

		totalAnimTime += tick;

		for (int i = 1; i < frames.size(); i++)
		{
			if (totalAnimTime > frames[i].tick)
			{
				if (i + 1 != frames.size())
					continue;

				if (isLoop == true)
				{
					totalAnimTime = 0.0f;

					texCoord[0].x = frames[0].left;
					texCoord[0].y = frames[0].top;

					texCoord[1].x = frames[0].right;
					texCoord[1].y = frames[0].top;

					texCoord[2].x = frames[0].left;
					texCoord[2].y = frames[0].bottom;
				}

				break;
			}

			texCoord[0].x = frames[i].left;
			texCoord[0].y = frames[i].top;

			texCoord[1].x = frames[i].right;
			texCoord[1].y = frames[i].top;

			texCoord[2].x = frames[i].left;
			texCoord[2].y = frames[i].bottom;

			break;
		}

		engine->DrawSpriteOn3D(texture->GetTexture(), width, height, MatrixTranspose(worldViewProj), texCoord);
	}

	void SpriteAnimation::Render(GraphicsEngineBase* engine, const Matrix& viewProjection, const Vector& viewPosition, float tick)
	{
		Matrix worldMatrix = MatrixLookAtLH(position, viewPosition, Vector::UnitY);

		Matrix worldViewProj = MatrixInverse(worldMatrix) * viewProjection;
		Vector texCoord[3] = {};

		totalAnimTime += tick;

		for (int i = 1; i < frames.size(); i++)
		{
			if (totalAnimTime > frames[i].tick)
			{
				if (i + 1 != frames.size())
					continue;

				if (isLoop == true)
				{
					totalAnimTime = 0.0f;

					texCoord[0].x = frames[0].left;
					texCoord[0].y = frames[0].top;

					texCoord[1].x = frames[0].right;
					texCoord[1].y = frames[0].top;

					texCoord[2].x = frames[0].left;
					texCoord[2].y = frames[0].bottom;
				}

				break;
			}

			texCoord[0].x = frames[i].left;
			texCoord[0].y = frames[i].top;

			texCoord[1].x = frames[i].right;
			texCoord[1].y = frames[i].top;

			texCoord[2].x = frames[i].left;
			texCoord[2].y = frames[i].bottom;

			break;
		}

		engine->DrawSpriteOn3D(texture->GetTexture(), width, height, MatrixTranspose(worldViewProj), texCoord);
	}
}