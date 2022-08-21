/********************************
*								*
*	Sampler Builder.cpp			*
*								*
*	Created : 2022/07/28		*
*	Updated : 2022/07/28		*
*********************************/

#include "SamplerBuilder.h"

namespace DX11
{
	SamplerBuilder::SamplerBuilder(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
		: device(device)
		, deviceContext(deviceContext)
	{

	}

	SamplerBuilder::~SamplerBuilder()
	{

	}

	SamplerBase* SamplerBuilder::CreateSampler(D3D11_FILTER filter)
	{
		D3D11_SAMPLER_DESC sampDesc = {};
		sampDesc.Filter = filter;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		ID3D11SamplerState* sampler;

		HRESULT hr = device->CreateSamplerState(&sampDesc, &sampler);

		if (FAILED(hr) == true)
			return nullptr;

		Sampler* newSampler = new Sampler(deviceContext);

		if (newSampler == nullptr)
		{
			sampler->Release();

			return nullptr;
		}

		newSampler->SetSampler(sampler);

		return newSampler;
	}
}