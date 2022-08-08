/********************************
*								*
*	Sampler.h					*
*								*
*	Created : 2022/07/28		*
*	Updated : 2022/07/28		*
*********************************/

#pragma once

#include <d3d11_1.h>
#include "../GraphicsEngine/Bases/SamplerBase.h"

namespace DX11
{
	using GraphicsEngineSpace::SamplerBase;
	using GraphicsEngineSpace::ShaderType;

	class Sampler : public SamplerBase
	{
		ID3D11DeviceContext* deviceContext;
		ID3D11SamplerState* samplerState;

	public:
		Sampler(ID3D11DeviceContext* deviceContext);
		~Sampler() override;

		void SetSampler(ID3D11SamplerState* sampler);
		bool SetUpSampler(unsigned int slot, ShaderType targetType) override;
	};
}