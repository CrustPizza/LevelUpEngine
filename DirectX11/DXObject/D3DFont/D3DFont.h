/********************************
*								*
*	D3D Font.h					*
*								*
*	Created : 2022/08/17		*
*	Updated : 2022/08/17		*
*********************************/

#pragma once

#include "Inc/SpriteBatch.h"
#include "Inc/SpriteFont.h"
#include "../GraphicsEngine/Bases/FontBase.h"

namespace DX11
{
	using GraphicsEngineSpace::FontBase;
	using namespace HeraclesMath;

	class D3DFont : public FontBase
	{
		DirectX::SpriteBatch* spriteBatch;
		DirectX::SpriteFont* spriteFont;
		ID3D11DepthStencilState** depthState;

	public:
		D3DFont(DirectX::SpriteBatch* spriteBatch, DirectX::SpriteFont* spriteFont, ID3D11DepthStencilState** depthState);
		~D3DFont() override;

		bool DrawTextColor(const std::string& text, Vector color, Vector position, float rotation, Vector scale) override;
		bool DrawTextColor(const std::wstring& text, Vector color, Vector position, float rotation, Vector scale) override;
		void SetLineSpacing(float size) override;
	};
}