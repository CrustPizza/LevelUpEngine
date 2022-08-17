/********************************
*								*
*	Point Light.cpp				*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#include "PointLight.h"

namespace GraphicsEngineSpace
{
	PointLight::PointLight()
		: intensity(10.0f)
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
		cb.diffuse = diffuse * color;
		cb.specularPower = specularPower;
		cb.intensity = intensity;

		lightParamBuffer->SetUpBuffer(slot, &cb, type);
	}
}