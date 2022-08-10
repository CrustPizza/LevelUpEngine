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

	void TextureUI::Render(GraphicsEngineBase* engine)
	{
		if (isEnable != true || engine == nullptr)
			return;

		auto screenPosition = GetScreenPosition();

		engine->DrawSprite(texture->GetTexture(), screenPosition.x, screenPosition.y, width, height, screenPosition.z);

		for (auto* iter : child)
		{
			if (iter != nullptr)
				iter->Render(engine);
		}
	}
}