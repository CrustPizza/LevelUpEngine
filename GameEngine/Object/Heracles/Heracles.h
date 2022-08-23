/********************************
*								*
*	Heracles.h					*
*								*
*	Created : 2022/08/23		*
*	Updated : 2022/08/23		*
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

	class Heracles : public ObjectBase
	{
		PBRModel* pbrModel;
		PBRModel* weaponPbrModel;

		PrefabBase* prefab;
		PrefabBase* weaponPrefab;
		ModelBase* model;

		Vector velocity;
		bool animSwitch;

		float animationTime;

	public:
		Heracles();
		~Heracles();

		void Init(GraphicsEngineSpace::Factory* factory, ModelBase* model);
		void SetWeapon(GraphicsEngineSpace::Factory* factory, ModelBase* model);
		void Update(float tick) override;
		void Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick = 0.0f) override;

		void SetAnimKey(const std::string& animationName);
	};
}