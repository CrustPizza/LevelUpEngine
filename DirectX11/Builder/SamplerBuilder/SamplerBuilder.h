/********************************
*								*
*	Sampler Builder.h			*
*								*
*	Created : 2022/07/28		*
*	Updated : 2022/07/28		*
*********************************/

#pragma once

#include "DXObject/Sampler/Sampler.h"

namespace DX11
{
	class SamplerBuilder
	{
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;

	public:
		SamplerBuilder(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~SamplerBuilder();

		SamplerBase* CreateSampler(D3D11_FILTER filter);
	};
}