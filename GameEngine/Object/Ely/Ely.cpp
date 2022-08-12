/********************************
*								*
*	Ely.cpp						*
*								*
*	Created : 2022/08/12		*
*	Updated : 2022/08/12		*
*********************************/

#include "Ely.h"

namespace GameEngineSpace
{
	Ely::Ely()
		: pbrModel(nullptr)
		, prefab(nullptr)
		, model(nullptr)
		, velocity{}
		, animationTime(0.0f)
	{
		transform.position = { -10.0f, 0.0f, -5.0f };
		transform.scale = { 0.1f, 0.1f, 0.1f };
	}

	Ely::~Ely()
	{

	}

	void Ely::Init(GraphicsEngineSpace::Factory* factory, ModelBase* model)
	{
		static int ID = 0;

		pbrModel = factory->CreateSkinningModel("ElyPBR_" + std::to_string(ID++), model);
		pbrModel->SetAlpha(1.0f);
		pbrModel->SetMetallic(0.5f);
		pbrModel->SetRoughness(0.2f);

		prefab = pbrModel->GetPrefab();
		prefab->SetRotation({ 0.0f, 180.0f, 0.0f });
		this->model = model;
		this->model->SetAnimationKey("Idle");
	}

	void Ely::Update(float tick)
	{
		transform.rotation.y += 0.1f;

		transform.UpdateWorldTransform();

		if (Move() == true)
			;
	}

	void Ely::Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick)
	{
		using namespace GraphicsEngineSpace;

		auto& materials = prefab->GetMaterials();
		//auto materials = pbrModel->GetPrefab()->GetMaterials();

		for (auto iter : materials)
		{
			auto materialData = iter.second->GetMaterialData();
			auto maps = materialData.maps;

			for (int i = 0; i < maps.size(); i++)
			{
				if (maps[i].type == MapType::DIFFUSE)
				{
					if (maps[i].map != nullptr)
						maps[i].map->SetUpTexture(0, ShaderType::PIXEL);
				}
				else if (maps[i].type == MapType::NORMAL)
				{
					if (maps[i].map != nullptr)
						maps[i].map->SetUpTexture(1, ShaderType::PIXEL);
				}
			}

			break;
		}

		animationTime += tick;

		if (prefab->PrepareRender(transform.GetWorldTransform(), animationTime) == true)
		{
			static bool test1 = true;
			static bool test2 = false;

			if (test1 == true)
			{
				model->SetAnimationKey("Run");

				test2 = true;
				test1 = false;
			}
			else if (test2 == true)
			{
				model->SetAnimationKey("Attack");

				test2 = false;
			}
			else
			{
				model->SetAnimationKey("Idle");

				test1 = true;
			}

			animationTime = 0.0f;
		}

		prefab->Render(engine);
	}

	void Ely::AddForce(const Vector& v)
	{
		velocity += v;
	}

	bool Ely::Move()
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

	void Ely::SetMetallic(float metallic)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetMetallic(metallic);
	}

	void Ely::SetRoughness(float roughness)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetRoughness(roughness);
	}

	void Ely::SetLight(const Vector& dir, const Vector& color, int index)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetLightDirection(dir, index);
		pbrModel->SetLightColor(color, index);
	}
}