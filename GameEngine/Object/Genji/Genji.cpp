/********************************
*								*
*	Genji.cpp					*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/08/05		*
*********************************/

#include "Genji.h"

namespace GameEngineSpace
{
	Genji::Genji()
		: prefab(nullptr)
		, material
	{
		{ 1.0f, 1.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, 0.0f },
	}
	{
		transform.position.x -= 10.0f;
		transform.scale *= 2.0f;
	}

	Genji::~Genji()
	{

	}

	void Genji::Init(GraphicsEngineSpace::Factory* factory, ModelBase* model)
	{
		pbrModel = factory->CreateAlbedoNormalModel("GenjiPBR", model);
		pbrModel->SetAlpha(1.0f);
		pbrModel->SetMetallic(0.5f);
		pbrModel->SetRoughness(0.5f);
		prefab = pbrModel->GetPrefab();

		transform.position.x += 5.0f;
	}

	void Genji::Init(GraphicsEngineSpace::Factory* factory, ModelBase* model, ShaderBase* vertexShader, ShaderBase* pixelShader, BufferBase* matrixBuffer, BufferBase* materialBuffer)
	{
		prefab = factory->CreatePrefab("GenjiPrefab", model, matrixBuffer, 0);
		prefab->SetVertexShader(vertexShader);
		prefab->SetPixelShader(pixelShader);
		prefab->SetMaterialBuffer({ materialBuffer, 3, &material, GraphicsEngineSpace::ShaderType::PIXEL });

		struct GenjiVertex
		{
			HeraclesMath::Vector position;
			HeraclesMath::Vector normal;
			HeraclesMath::Vector texCoord;
			HeraclesMath::Vector tangent;
		};

		prefab->CreateVertexBuffer<GenjiVertex>(factory, [](const GraphicsEngineSpace::VertexData& data)-> GenjiVertex
			{
				GenjiVertex temp;
				temp.position = data.position;
				temp.normal = data.normal;
				temp.texCoord = { data.texCoord.x, data.texCoord.y, 0.0f, 0.0f };
				temp.tangent = data.tangent;

				return temp;
			});
	}

	void Genji::Update(float tick)
	{
		transform.UpdateWorldTransform();

		//transform.position.x -= 0.01f;
	}

	void Genji::Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick)
	{
		using namespace GraphicsEngineSpace;

		auto materials = prefab->GetMaterials();

		for (auto iter : materials)
		{
			auto materialData = iter.second->GetMaterialData();
			auto maps = materialData.maps;

			material.ambient = materialData.ambient;
			material.diffuse = materialData.diffuse;
			material.specular = materialData.specular;

			for (int i = 0; i < maps.size(); i++)
			{
				if (maps[i].type == MapType::DIFFUSE)
					maps[i].map->SetUpTexture(0, ShaderType::PIXEL);
				else if (maps[i].type == MapType::NORMAL)
					maps[i].map->SetUpTexture(1, ShaderType::PIXEL);
			}

			break;
		}

		prefab->PrepareRender(transform.GetWorldTransform(), tick);
		prefab->Render(engine);
	}

	void Genji::SetMetallic(float metallic)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetMetallic(metallic);
	}

	void Genji::SetRoughness(float roughness)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetRoughness(roughness);
	}

	void Genji::SetLight(const Vector& dir, const Vector& color, int index)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetLightDirection(dir, index);
		pbrModel->SetLightColor(color, index);
	}
}