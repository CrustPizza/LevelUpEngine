/********************************
*								*
*	Directional Light Base.h	*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#pragma once

#include "Bases/BufferBase.h"
#include "../HeraclesMath/HeraclesMath.h"

namespace GraphicsEngineSpace
{
	class DirectionalLightBase
	{
		struct cbDirectionalLight
		{
			HeraclesMath::Vector	direction;
			HeraclesMath::Vector	diffuse;
			HeraclesMath::Vector	ambient;
			float			specularPower;
		};

		BufferBase* directionalLightBuffer;

	public:
		HeraclesMath::Vector color;
		HeraclesMath::Vector rotation;
		HeraclesMath::Vector diffuse;
		HeraclesMath::Vector ambient;
		float specularPower;

	public:
		DirectionalLightBase()
			: directionalLightBuffer(nullptr)
			, color{ 1.0f, 1.0f, 1.0f, 0.0f }
			, rotation{}
			, diffuse{ 1.0f, 1.0f, 1.0f, 0.0f }
			, ambient{ 0.3f, 0.3f, 0.3f, 0.3f }
			, specularPower(16.0f) {}
		virtual ~DirectionalLightBase() = default;

		void SetBuffer(BufferBase* constantBuffer) { directionalLightBuffer = constantBuffer; }

		void SetUpBuffer(unsigned int slot)
		{
			cbDirectionalLight cb;
			cb.direction = Vector::UnitZ * HeraclesMath::MatrixRotationFromVector(rotation);
			cb.diffuse = diffuse * color;
			cb.ambient = ambient * color;
			cb.specularPower = specularPower;

			directionalLightBuffer->SetUpBuffer(slot, &cb, ShaderType::PIXEL);
		}
	};
}