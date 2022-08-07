/********************************
*								*
*	Pig.h						*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/08/02		*
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

	class Pig : public ObjectBase
	{
		struct MaterialCB
		{
			HeraclesMath::Vector ambient;
			HeraclesMath::Vector diffuse;
			HeraclesMath::Vector specular;
		} material;

		PBRModel* pbrModel;

		PrefabBase* prefab;
		ModelBase* model;

		Matrix boneMatrix[64];

		Vector velocity;

	public:
		Pig();
		~Pig();
		
		void Init(GraphicsEngineSpace::Factory* factory, ModelBase* model);
		void Init(GraphicsEngineSpace::Factory* factory, ModelBase* model, ShaderBase* vertexShader, ShaderBase* pixelShader, BufferBase* matrixBuffer, BufferBase* boneBuffer, BufferBase* materialBuffer);
		void Update(float tick) override;
		void Render(GraphicsEngineSpace::GraphicsEngineBase* engine) override;

		void AddForce(const Vector& v);
		bool Move();

		void LookAt(const Vector& targetPos);

		void SetMetallic(float metallic);
		void SetRoughness(float roughness);
		void SetLight(const Vector& dir, const Vector& color, int index);
	};
}