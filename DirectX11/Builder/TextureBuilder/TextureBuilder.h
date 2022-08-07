/********************************
*								*
*	Texture Builder.h			*
*								*
*	Created : 2022/06/21		*
*	Updated : 2022/07/27		*
*********************************/

#pragma once

#include <string>
#include "DXObject/D3DTexture/D3DTexture.h"

namespace DX11
{
	class TextureBuilder
	{
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;

	public:
		TextureBuilder(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~TextureBuilder();

		D3DTexture* CreateTexture(const std::string& path);

	private:
		ID3D11ShaderResourceView* CreateTextureFromFile(const std::string& path);
	};
}