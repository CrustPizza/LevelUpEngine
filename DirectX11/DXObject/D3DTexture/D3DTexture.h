/********************************
*								*
*	D3D Texture.h				*
*								*
*	Created : 2022/07/27		*
*	Updated : 2022/07/27		*
*********************************/

#pragma once

#include <d3d11_1.h>
#include "../GraphicsEngine/Bases/TextureBase.h"

namespace DX11
{
	using GraphicsEngineSpace::Texture;
	using GraphicsEngineSpace::TextureBase;
	using GraphicsEngineSpace::ShaderType;

	class D3DTexture : public TextureBase
	{
		ID3D11DeviceContext* deviceContext;
		ID3D11ShaderResourceView* texture;

	public:
		D3DTexture(ID3D11DeviceContext* deviceContext);
		~D3DTexture() override;

		unsigned int GetMipLevels() override;
		Texture* GetTexture() override;

		void SetTexture(ID3D11ShaderResourceView* texture);
		bool SetUpTexture(unsigned int slot, ShaderType targetType) override;
	};
}