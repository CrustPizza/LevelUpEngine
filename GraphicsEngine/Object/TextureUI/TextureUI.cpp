/********************************
*								*
*	Texture UI.cpp				*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/09		*
*********************************/

#include "TextureUI.h"

namespace GraphicsEngineSpace
{
	TextureUI::TextureUI()
		: texture(nullptr)
	{

	}

	TextureUI::~TextureUI()
	{

	}

	void TextureUI::SetTexture(TextureBase* texture)
	{
		this->texture = texture;
	}

	TextureBase* TextureUI::GetTexture()
	{
		return texture;
	}

	void TextureUI::Render(GraphicsEngineBase* engine, float tick)
	{
		if (isEnable != true || engine == nullptr)
			return;

		engine->GraphicsDebugBeginEvent(name);

		if (texture != nullptr)
		{
			auto screenPosition = GetScreenPosition();
			auto screenScale = GetScreenScale();

			engine->DrawSprite(texture->GetTexture(), screenPosition.x, screenPosition.y, width * screenScale.x, height * screenScale.y, screenPosition.z);
		}

		for (auto* iter : child)
		{
			if (iter != nullptr)
				iter->Render(engine);
		}

		engine->GraphicsDebugEndEvent();
	}
}