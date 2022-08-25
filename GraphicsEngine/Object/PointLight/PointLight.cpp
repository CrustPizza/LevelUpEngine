/********************************
*								*
*	Point Light.cpp				*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/22		*
*********************************/

#include "PointLight.h"

namespace GraphicsEngineSpace
{
	PointLight* PointLight::instance = nullptr;
	PointLight::cbPointLight PointLight::parameters[20] = {};
	int paramIndex = 0;

	PointLight::PointLight()
		: intensity(1.0f)
		, range(10.0f)
	{
		
	}

	PointLight::~PointLight()
	{

	}

	void PointLight::SetBuffer(BufferBase* buffer)
	{
		lightParamBuffer = buffer;
	}

	void PointLight::SetUpBuffer(unsigned int slot, ShaderType type)
	{
		cbPointLight cb;
		cb.position = position;
		cb.diffuse = diffuse;
		cb.color = color;
		cb.specularPower = specularPower;
		cb.intensity = intensity;
		cb.range = range;

		lightParamBuffer->SetUpBuffer(slot, &cb, type);
	}

	void PointLight::SetUpPointLightsBuffer(unsigned int slot, ShaderType type)
	{
		if (lightParamBuffer == nullptr)
			return;

		lightParamBuffer->SetUpBuffer(slot, parameters, type);

		paramIndex = 0;

		for (int i = 0; i < 20; i++)
			parameters[i] = {};
	}

	void PointLight::SetUpPointLight()
	{
		if (paramIndex >= 20)
			return;

		parameters[paramIndex].position = position;
		parameters[paramIndex].diffuse = diffuse;
		parameters[paramIndex].color = color;
		parameters[paramIndex].specularPower = specularPower;
		parameters[paramIndex].intensity = intensity;
		parameters[paramIndex].range = range;

		paramIndex++;
	}
}