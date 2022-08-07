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
		, sampler(nullptr)
	{

	}

	Sampler::~Sampler()
	{
		if (this->sampler != nullptr)
			this->sampler->Release();
	}

	void Sampler::SetSampler(ID3D11SamplerState* sampler)
	{
		if (this->sampler != nullptr)
			this->sampler->Release();

		this->sampler = sampler;
	}

	bool Sampler::SetUpSampler(unsigned int slot, ShaderType targetType)
	{
		if (sampler == nullptr)
			return false;

		switch (targetType)
		{
			
		case ShaderType::VERTEX:
		{
			deviceContext->VSSetSamplers(slot, 1, &sampler);

			return true;
		}
			
		case ShaderType::PIXEL:
		{
			deviceContext->PSSetSamplers(slot, 1, &sampler);

			return true;
		}

		}

		return false;
	}
}