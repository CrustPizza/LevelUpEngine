/********************************
*								*
*	Texture Builder.cpp			*
*								*
*	Created : 2022/06/21		*
*	Updated : 2022/06/24		*
*********************************/

#include "TextureBuilder.h"
#include "Inc/DDSTextureLoader.h"
#include "Inc/WICTextureLoader.h"

namespace DX11
{
	TextureBuilder::TextureBuilder(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
		: device(device)
		, deviceContext(deviceContext)
	{

	}

	TextureBuilder::~TextureBuilder()
	{

	}

	D3DTexture* TextureBuilder::CreateTexture(const std::string& path)
	{
		ID3D11ShaderResourceView* texture = CreateTextureFromFile(path);

		if (texture == nullptr)
			return nullptr;

		D3DTexture* newTexture = new D3DTexture(deviceContext);

		if (newTexture == nullptr)
			return nullptr;

		newTexture->SetTexture(texture);

		return newTexture;
	}

	ID3D11ShaderResourceView* TextureBuilder::CreateTextureFromFile(const std::string& path)
	{
		HRESULT hr = S_OK;
		ID3D11ShaderResourceView* texture = nullptr;
		
		std::string fileFormat = path.substr(path.length() - 3);

		for (char& chr : fileFormat)
			chr = std::toupper(chr);

		if (fileFormat.compare("DDS") == 0)
		{
			std::wstring convertPath;

			convertPath.assign(path.begin(), path.end());

			hr = DirectX::CreateDDSTextureFromFile(device, convertPath.c_str(), nullptr, &texture);
			
			if (FAILED(hr))
				return nullptr;
		}
		else
		{
			std::wstring convertPath;

			convertPath.assign(path.begin(), path.end());

			// 지원되는 파일 형식에 대한 필터를 마소의 함수에 의존해서 찝찝한 점이 있다..
			hr = DirectX::CreateWICTextureFromFile(device, convertPath.c_str(), nullptr, &texture);

			if (FAILED(hr))
				return nullptr;
		}

		return texture;
	}
}