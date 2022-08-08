/********************************
*								*
*	Directional Light.h			*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#pragma once

#include "Bases/LightBase.h"

namespace GraphicsEngineSpace
{
	class DirectionalLight : public LightBase
	{
		struct cbDirectionalLight
		{
			Vector	direction;
			Vector	diffuse;
			Vector	ambient;
			float	specularPower;
		};

	public:
		Vector rotation;

	public:
		DirectionalLight();
		~DirectionalLight() override;

		void SetBuffer(BufferBase* buffer) override;
		void SetUpBuffer(unsigned int slot, ShaderType type) override;
	};
}