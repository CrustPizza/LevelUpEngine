/********************************
*								*
*	D3D Texture.cpp				*
*								*
*	Created : 2022/07/27		*
*	Updated : 2022/07/27		*
*********************************/

#include "D3DTexture.h"

namespace DX11
{
	D3DTexture::D3DTexture(ID3D11DeviceContext* deviceContext)
		: deviceContext(deviceContext)
		, texture(nullptr)
	{

	}

	D3DTexture::~D3DTexture()
	{
		if (texture != nullptr)
			texture->Release();
	}

	unsigned int D3DTexture::GetMipLevels()
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};

		texture->GetDesc(&desc);

		return desc.TextureCube.MipLevels;
	}

	Texture* D3DTexture::GetTexture()
	{
		return reinterpret_cast<Texture*>(texture);
	}

	void D3DTexture::SetTexture(ID3D11ShaderResourceView* texture)
	{
		if (this->texture != nullptr)
			this->texture->Release();

		this->texture = texture;
	}

	bool D3DTexture::SetUpTexture(unsigned int slot, ShaderType targetType)
	{
		if (texture == nullptr)
			return false;

		switch (targetType)
		{

		case ShaderType::VERTEX:
		{
			deviceContext->VSSetShaderResources(slot, 1, &texture);

			return true;
		}

		case ShaderType::PIXEL:
		{
			deviceContext->PSSetShaderResources(slot, 1, &texture);

			return true;
		}

		}

		return false;
	}
}