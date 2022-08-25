/********************************
*								*
*	Point Light.h				*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/22		*
*********************************/

#pragma once

#include "Bases/LightBase.h"

namespace GraphicsEngineSpace
{
	class GraphicsEngine;
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
			float range;
			float padding;
		};

		static PointLight* instance;
		static cbPointLight parameters[20];

	public:
		float intensity;
		float range;

	public:
		PointLight();
		~PointLight() override;

		void SetBuffer(BufferBase* buffer) override;
		void SetUpBuffer(unsigned int slot, ShaderType type) override;
		virtual void SetUpPointLightsBuffer(unsigned int slot, ShaderType type);
		virtual void SetUpPointLight();

		friend GraphicsEngine;
	};
}