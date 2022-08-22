/********************************
*								*
*	Point Light.h				*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#pragma once

#include "Bases/LightBase.h"

namespace GraphicsEngineSpace
{
	using namespace HeraclesMath;

	class PointLight : public LightBase
	{
		struct cbPointLight
		{
			Vector position;
			Vector diffuse;
			Vector color;
			float specularPower;
			float intensity;
		};

	public:
		float intensity;

	public:
		PointLight();
		~PointLight() override;

		void SetBuffer(BufferBase* buffer) override;
		void SetUpBuffer(unsigned int slot, ShaderType type) override;
		virtual cbPointLight GetPointLightParameter();
		virtual BufferBase* GetBuffer();
	};
}