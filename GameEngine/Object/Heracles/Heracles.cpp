/********************************
*								*
*	Heracles.cpp				*
*								*
*	Created : 2022/08/23		*
*	Updated : 2022/08/23		*
*********************************/

#include "Heracles.h"

namespace GameEngineSpace
{
	Heracles::Heracles()
		: pbrModel(nullptr)
		, prefab(nullptr)
		, model(nullptr)
		, animationTime(0.0f)
	{

	}

	Heracles::~Heracles()
	{

	}

	void Heracles::Init(GraphicsEngineSpace::Factory* factory, ModelBase* model)
	{
		static int ID = 0;

		pbrModel = factory->CreateAllTextureModel("HeraclesPBR_" + std::to_string(ID++), model);
		pbrModel->SetAlpha(1.0f);

		prefab = pbrModel->GetPrefab();
		prefab->SetAnimationKey("Idle");
		this->model = model;

		transform.position.z -= 30.0f * ID;
		transform.scale = { 0.1f, 0.1f, 0.1f };
	}

	void Heracles::SetWeapon(GraphicsEngineSpace::Factory* factory, ModelBase* model)
	{
		static int ID = 0;

		weaponPbrModel = factory->CreateSkinningAlbedoModel("HeraclesWeaponPBR_" + std::to_string(ID++), model);
		weaponPbrModel->SetAlpha(1.0f);

		weaponPrefab = weaponPbrModel->GetPrefab();
		weaponPrefab->SetAnimationKey("Idle");
	}

	void Heracles::Update(float tick)
	{
		transform.rotation.y += 15.0f;

		transform.UpdateWorldTransform();
	}

	void Heracles::Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick)
	{
		animationTime += tick;

		weaponPrefab->PrepareRender(transform.GetWorldTransform(), animationTime);

		if (prefab->PrepareRender(transform.GetWorldTransform(), animationTime) == true)
			animationTime = 0.0f;

		prefab->Render(engine);
		weaponPrefab->Render(engine);
	}

	void Heracles::SetAnimKey(const std::string& animationName)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->GetPrefab()->SetAnimationKey(animationName);
		weaponPbrModel->GetPrefab()->SetAnimationKey(animationName);
	}
}