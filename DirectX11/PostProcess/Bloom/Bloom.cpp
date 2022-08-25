/********************************
*								*
*	Bloom.cpp					*
*								*
*	Created : 2022/07/25		*
*	Updated : 2022/07/27		*
*********************************/

#include "Bloom.h"

namespace DX11
{
	Bloom::Bloom(ID3D11DeviceContext* deviceContext)
		: deviceContext(deviceContext)
		, downSampler(nullptr)
		, blur(nullptr)
		, combine(nullptr)
		, threshold(0.50f)
	{

	}

	Bloom::~Bloom()
	{
		delete downSampler;
		delete blur;
		delete combine;
	}

	void Bloom::Init(Factory* factory, ID3D11Device* device, DXGI_FORMAT format, DirectX::SpriteBatch* spriteBatch)
	{
		downSampler = new DownSampling(deviceContext);
		downSampler->Init(factory, device, format, spriteBatch, threshold);

		blur = new Blur(deviceContext);
		blur->Init(factory, device, format, spriteBatch);
		blur->downSampler->SetThreshold(threshold);

		combine = new Combine(deviceContext);
		combine->Init(factory, device, format, spriteBatch);
		combine->param.sourceIntensity = 1.0f;
	}

	void Bloom::operator()(RenderTexture* texture, ID3D11DepthStencilView* depthView, ID3D11DepthStencilState* depthState)
	{
		long width = texture->GetWidth();
		long height = texture->GetHeight();

		downSampler->OnResize(width / 2, height / 2);

		auto downSRV1 = (*downSampler)(texture->GetShaderResourceView(), depthView, depthState);

		(*blur)(downSampler->GetRenderTexture(), 4.0f, depthView, depthState);
		(*combine)(texture, downSRV1, depthView, depthState);
	}
}