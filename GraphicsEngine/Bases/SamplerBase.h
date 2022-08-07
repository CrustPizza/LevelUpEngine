/********************************
*								*
*	Sampler Base.h				*
*								*
*	Created : 2022/07/28		*
*	Updated : 2022/07/28		*
*********************************/

#pragma once

#include "Bases/ResourceBase.h"
#include "Bases/ShaderBase.h"

namespace GraphicsEngineSpace
{
	class SamplerBase : public ResourceBase<SamplerBase>
	{

	public:
		SamplerBase() = default;
		virtual ~SamplerBase() = default;

		virtual bool SetUpSampler(unsigned int slot, ShaderType targetType) abstract;
	};
}