/********************************
*								*
*	Bloom.h						*
*								*
*	Created : 2022/07/25		*
*	Updated : 2022/07/27		*
*********************************/

#pragma once

#include "PostProcess/Blur/Blur.h"
#include "PostProcess/Combine/Combine.h"
#include "PostProcess/DownSampling/DownSampling.h"

namespace DX11
{
	class Bloom
	{
		ID3D11DeviceContext* deviceContext;

		DownSampling* downSampler;

		Blur* blur;
		Combine* combine;

		float threshold;

	public:
		Bloom(ID3D11DeviceContext* deviceContext);
		~Bloom();

		void Init(Factory* factory, ID3D11Device* device, DXGI_FORMAT format, DirectX::SpriteBatch* spriteBatch);
	
		void operator ()(RenderTexture* texture, ID3D11DepthStencilView* depthView = nullptr, ID3D11DepthStencilState* depthState = nullptr);
	};
}