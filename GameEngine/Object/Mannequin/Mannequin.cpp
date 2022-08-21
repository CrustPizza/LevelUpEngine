/********************************
*								*
*	Mannequin.cpp				*
*								*
*	Created : 2022/08/11		*
*	Updated : 2022/08/11		*
*********************************/

#include "Mannequin.h"

namespace GameEngineSpace
{
	Mannequin::Mannequin()
		: pbrModel(nullptr)
		, prefab(nullptr)
		, model(nullptr)
		, velocity{}
		, animationTime(0.0f)
	{
		transform.position = { 0.0f, 0.0f, -5.0f };
		transform.scale = { 0.1f, 0.1f, 0.1f };
	}

	Mannequin::~Mannequin()
	{

	}

	void Mannequin::Init(GraphicsEngineSpace::Factory* factory, ModelBase* model)
	{
		static int ID = 0;

		pbrModel = factory->CreateSkinningModel("MannequinPBR_" + std::to_string(ID++), model);
		pbrModel->SetAlpha(1.0f);
		pbrModel->SetMetallic(0.5f);
		pbrModel->SetRoughness(0.2f);

		prefab = pbrModel->GetPrefab();
		prefab->SetAnimationKey("Idle");
		this->model = model;
	}

	void Mannequin::Update(float tick)
	{
		transform.rotation.y += 15.0f;

		transform.UpdateWorldTransform();

		if (Move() == true)
			;
	}

	void Mannequin::Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick)
	{
		using namespace GraphicsEngineSpace;

		animationTime += tick;

		if (prefab->PrepareRender(transform.GetWorldTransform(), animationTime) == true)
		{
			static bool test1 = true;
			static bool test2 = false;

			if (test1 == true)
			{
				prefab->SetAnimationKey("Run");

				test2 = true;
				test1 = false;
			}
			else if (test2 == true)
			{
				prefab->SetAnimationKey("Slash");

				test2 = false;
			}
			else
			{
				prefab->SetAnimationKey("Idle");

				test1 = true;
			}

			animationTime = 0.0f;
		}

		prefab->Render(engine);
	}

	void Mannequin::AddForce(const Vector& v)
	{
		velocity += v;
	}

	bool Mannequin::Move()
	{
		bool ret = false;

		for (int i = 0; i < 3; i++)
		{
			if (velocity[i] != 0.0f)
			{
				if (velocity[i] > 0.01f)
				{
					transform.position[i] += 0.01f;
					velocity[i] -= 0.01f;

					ret = true;
				}
				else if (velocity[i] < -0.01f)
				{
					transform.position[i] -= 0.01f;
					velocity[i] += 0.01f;

					ret = true;
				}
				else
				{
					transform.position[i] += velocity[i];
					velocity[i] = 0.0f;

					ret = true;
				}
			}
		}

		return ret;
	}

	void Mannequin::SetMetallic(float metallic)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetMetallic(metallic);
	}

	void Mannequin::SetRoughness(float roughness)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetRoughness(roughness);
	}
}