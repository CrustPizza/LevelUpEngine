/********************************
*								*
*	Sampler.cpp					*
*								*
*	Created : 2022/07/28		*
*	Updated : 2022/07/28		*
*********************************/

#include "Sampler.h"

namespace DX11
{
	Sampler::Sampler(ID3D11DeviceContext* deviceContext)
		: deviceContext(deviceContext)
		, samplerState(nullptr)
	{

	}

	Sampler::~Sampler()
	{
		if (samplerState != nullptr)
			samplerState->Release();
	}

	void Sampler::SetSampler(ID3D11SamplerState* sampler)
	{
		if (samplerState != nullptr)
			samplerState->Release();

		samplerState = sampler;
	}

	bool Sampler::SetUpSampler(unsigned int slot, ShaderType targetType)
	{
		if (samplerState == nullptr)
			return false;

		switch (targetType)
		{
			
		case ShaderType::VERTEX:
		{
			deviceContext->VSSetSamplers(slot, 1, &samplerState);

			return true;
		}
			
		case ShaderType::PIXEL:
		{
			deviceContext->PSSetSamplers(slot, 1, &samplerState);

			return true;
		}

		}

		return false;
	}
}