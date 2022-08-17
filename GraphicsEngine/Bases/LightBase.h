/********************************
*								*
*	Light Base.h				*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#pragma once

#include "Bases/ResourceBase.h"
#include "Bases/BufferBase.h"
#include "../HeraclesMath/HeraclesMath.h"

namespace GraphicsEngineSpace
{
	using HeraclesMath::Vector;
	using HeraclesMath::Matrix;

	class LightBase : public ResourceBase<LightBase>
	{
	protected:
		BufferBase* lightParamBuffer;

	public:
		Vector color;
		Vector diffuse;
		Vector ambient;
		float specularPower;
		Vector position;

	public:
		LightBase()
			: lightParamBuffer(nullptr)
			, color{ 1.0f, 1.0f, 1.0f, 0.0f }
			, diffuse{ 1.0f, 1.0f, 1.0f, 0.0f }
			, ambient{ 0.3f, 0.3f, 0.3f, 1.0f }
			, specularPower(16.0f)
			, position{ 0.0f, 0.0f, 0.0f, 1.0f } {}
		virtual ~LightBase() = default;

		virtual void SetBuffer(BufferBase* buffer) abstract;
		virtual void SetUpBuffer(unsigned int slot, ShaderType type = ShaderType::PIXEL) abstract;
	};
}