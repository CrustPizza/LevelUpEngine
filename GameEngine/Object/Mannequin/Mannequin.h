/********************************
*								*
*	Mannequin.h					*
*								*
*	Created : 2022/08/11		*
*	Updated : 2022/08/11		*
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

	class Mannequin : public ObjectBase
	{
		PBRModel* pbrModel;

		PrefabBase* prefab;
		ModelBase* model;

		Vector velocity;
		float animationTime;

	public:
		Mannequin();
		~Mannequin();

		void Init(GraphicsEngineSpace::Factory* factory, ModelBase* model);
		void Update(float tick) override;
		void Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick = 0.0f) override;

		void AddForce(const Vector& v);
		bool Move();

		void SetMetallic(float metallic);
		void SetRoughness(float roughness);
	};
}