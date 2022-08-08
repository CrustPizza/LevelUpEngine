/********************************
*								*
*	Directional Light.cpp		*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#include "DirectionalLight.h"

namespace GraphicsEngineSpace
{
	DirectionalLight::DirectionalLight()
		: rotation{}
	{

	}

	DirectionalLight::~DirectionalLight()
	{

	}

	void DirectionalLight::SetBuffer(BufferBase* buffer)
	{
		lightParamBuffer = buffer;
	}

	void DirectionalLight::SetUpBuffer(unsigned int slot, ShaderType type)
	{
		cbDirectionalLight cb;
		cb.direction = Vector::UnitZ * HeraclesMath::MatrixRotationFromVector(rotation);
		cb.diffuse = diffuse * color;
		cb.ambient = ambient * color;
		cb.specularPower = specularPower;

		lightParamBuffer->SetUpBuffer(slot, &cb, type);
	}
}