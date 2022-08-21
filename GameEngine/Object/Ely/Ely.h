/********************************
*								*
*	Ely.h						*
*								*
*	Created : 2022/08/12		*
*	Updated : 2022/08/12		*
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

	class Ely : public ObjectBase
	{
		PBRModel* pbrModel;

		PrefabBase* prefab;
		ModelBase* model;

		Vector velocity;
		float animationTime;

	public:
		Ely();
		~Ely();

		void Init(GraphicsEngineSpace::Factory* factory, ModelBase* model);
		void Update(float tick) override;
		void Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick = 0.0f) override;

		void AddForce(const Vector& v);
		bool Move();

		void SetMetallic(float metallic);
		void SetRoughness(float roughness);
	};
}