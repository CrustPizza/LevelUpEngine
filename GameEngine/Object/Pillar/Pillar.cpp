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

		pbrModel = factory->CreateAlbedoModel("PillarPBR_" + std::to_string(ID++), model);
		pbrModel->SetAlpha(1.0f);
		pbrModel->SetMetallic(0.5f);
		pbrModel->SetRoughness(0.2f);

		prefab = pbrModel->GetPrefab();
		this->model = model;
		this->model->SetAnimationKey("Idle");
	}

	void Pillar::Update(float tick)
	{
		transform.UpdateWorldTransform();
	}

	void Pillar::Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick)
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

	void Pillar::SetLight(const Vector& dir, const Vector& color, int index)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetLightDirection(dir, index);
		pbrModel->SetLightColor(color, index);
	}
}