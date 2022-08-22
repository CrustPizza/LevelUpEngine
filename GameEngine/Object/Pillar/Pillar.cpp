/********************************
*								*
*	Pillar.cpp					*
*								*
*	Created : 2022/08/11		*
*	Updated : 2022/08/11		*
*********************************/

#include "Pillar.h"

namespace GameEngineSpace
{
	Pillar::Pillar()
		: pbrModel(nullptr)
		, prefab(nullptr)
		, model(nullptr)
	{

	}

	Pillar::~Pillar()
	{

	}

	void Pillar::Init(GraphicsEngineSpace::Factory* factory, ModelBase* model)
	{
		static int ID = 0;

		pbrModel = factory->CreateWithoutAOStaticModel("PillarPBR_" + std::to_string(ID++), model);
		pbrModel->SetAlpha(1.0f);

		prefab = pbrModel->GetPrefab();
		this->model = model;
		this->model->SetAnimationKey("Idle");

		transform.position.x += 10.0f;
		transform.position.z -= 20.0f;
	}

	void Pillar::Update(float tick)
	{
		transform.rotation.y += 0.1f;

		transform.UpdateWorldTransform();
	}

	void Pillar::Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick)
	{
		using namespace GraphicsEngineSpace;

		prefab->PrepareRender(transform.GetWorldTransform(), tick);
		prefab->Render(engine);
	}

	void Pillar::SetMetallic(float metallic)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetMetallic(metallic);
	}

	void Pillar::SetRoughness(float roughness)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetRoughness(roughness);
	}
}