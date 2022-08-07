/********************************
*								*
*	Genji.h						*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/08/05		*
*********************************/

#pragma once

#include "Object/ObjectBase/ObjectBase.h"

namespace GameEngineSpace
{
	using GraphicsEngineSpace::PrefabBase;
	using GraphicsEngineSpace::ModelBase;
	using GraphicsEngineSpace::ShaderBase;
	using GraphicsEngineSpace::BufferBase;
	using GraphicsEngineSpace::PBRModel;

	class Genji : public ObjectBase
	{
		struct MaterialCB
		{
			HeraclesMath::Vector ambient;
			HeraclesMath::Vector diffuse;
			HeraclesMath::Vector specular;
		} material;

		PBRModel* pbrModel;

		PrefabBase* prefab;

	public:
		Genji();
		~Genji();

		void Init(GraphicsEngineSpace::Factory* factory, ModelBase* model);
		void Init(GraphicsEngineSpace::Factory* factory, ModelBase* model, ShaderBase* vertexShader, ShaderBase* pixelShader, BufferBase* matrixBuffer, BufferBase* materialBuffer);
		void Update(float tick) override;
		void Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick = 0.0f) override;

		void SetMetallic(float metallic);
		void SetRoughness(float roughness);
		void SetLight(const Vector& dir, const Vector& color, int index);
	};
}