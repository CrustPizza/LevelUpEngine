/********************************
*								*
*	D3D Font.cpp				*
*								*
*	Created : 2022/08/17		*
*	Updated : 2022/08/17		*
*********************************/

#include "D3DFont.h"

namespace DX11
{
	D3DFont::D3DFont(DirectX::SpriteBatch* spriteBatch, DirectX::SpriteFont* spriteFont, ID3D11DepthStencilState** depthState)
		: spriteBatch(spriteBatch)
		, spriteFont(spriteFont)
		, depthState(depthState)
	{

	}

	D3DFont::~D3DFont()
	{
		delete spriteFont;
	}

	bool D3DFont::DrawTextColor(const std::string& text, Vector color, Vector position, float rotation, Vector scale)
	{
		if (spriteBatch == nullptr || spriteFont == nullptr)
			return false;

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, *depthState);
		spriteFont->DrawString(spriteBatch, text.c_str(), DirectX::XMVECTOR{ position.x, position.y }, DirectX::XMVECTOR{ color.x, color.y, color.z }, HeraclesMath::ConvertDegreeToRadian(rotation), DirectX::g_XMZero, DirectX::XMVECTOR{ scale.x, scale.y }, DirectX::SpriteEffects_None, position.z);
		spriteBatch->End();

		return true;
	}

	bool D3DFont::DrawTextColor(const std::wstring& text, Vector color, Vector position, float rotation, Vector scale)
	{
		if (spriteBatch == nullptr || spriteFont == nullptr)
			return false;

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, *depthState);
		spriteFont->DrawString(spriteBatch, text.c_str(), DirectX::XMVECTOR{ position.x, position.y }, DirectX::XMVECTOR{ color.x, color.y, color.z }, HeraclesMath::ConvertDegreeToRadian(rotation), DirectX::g_XMZero, DirectX::XMVECTOR{ scale.x, scale.y }, DirectX::SpriteEffects_None, position.z);
		spriteBatch->End();

		return true;
	}

	void D3DFont::SetLineSpacing(float size)
	{
		if (spriteBatch == nullptr || spriteFont == nullptr)
			return;
		
		spriteFont->SetLineSpacing(size);
	}
}