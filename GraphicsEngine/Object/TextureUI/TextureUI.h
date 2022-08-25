/********************************
*								*
*	Texture UI.h				*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/20		*
*********************************/

#pragma once

#include "Bases/UIBase.h"
#include "Bases/TextureBase.h"
#include "Bases/GraphicsEngineBase.h"

namespace GraphicsEngineSpace
{
	class Canvas;

	class TextureUI : public UIBase
	{
		TextureBase* texture;

	protected:
		TextureUI();
		~TextureUI() override;

	public:
		virtual void SetTexture(TextureBase* texture);
		virtual TextureBase* GetTexture();

	protected:
		void Render(GraphicsEngineBase* engine, float tick) override;

		friend Canvas;
	};
}