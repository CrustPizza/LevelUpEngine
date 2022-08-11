/********************************
*								*
*	Pig.cpp						*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/08/02		*
*********************************/

#include "Pig.h"
#include "Manager/Input/Input.h"

namespace GameEngineSpace
{
	Pig::Pig()
		: pbrModel(nullptr)
		, prefab(nullptr)
		, model(nullptr)
	{

	}

	Pig::~Pig()
	{

	}

	void Pig::Init(GraphicsEngineSpace::Factory* factory, ModelBase* model)
	{
		static int ID = 0;

		pbrModel = factory->CreateSkinningAlbedoModel("PigPBR_" + std::to_string(ID++), model);
		pbrModel->SetAlpha(1.0f);
		pbrModel->SetMetallic(0.5f);
		pbrModel->SetRoughness(0.0f);

		prefab = pbrModel->GetPrefab();
		this->model = model;
		this->model->SetAnimationKey("Idle");

		transform.position.x += 2.0f;
		transform.scale = { 0.1f, 0.1f, 0.1f };
	}

	void Pig::Init(GraphicsEngineSpace::Factory* factory, ModelBase* model, ShaderBase* vertexShader, ShaderBase* pixelShader, BufferBase* matrixBuffer, BufferBase* boneBuffer, BufferBase* materialBuffer)
	{
		prefab = factory->CreatePrefab("PigPrefab", model, matrixBuffer, 0);
		prefab->SetVertexShader(vertexShader);
		prefab->SetPixelShader(pixelShader);
		prefab->SetMaterialBuffer({ materialBuffer, 3, &material, GraphicsEngineSpace::ShaderType::PIXEL });
		this->model = model;
		this->model->SetAnimationKey("Idle");

		GraphicsEngineSpace::ConstantBufferSetting boneMatrixElements;
		boneMatrixElements.buffer = boneBuffer;
		boneMatrixElements.data = model->GetBoneMatrix();
		boneMatrixElements.slot = 2;
		boneMatrixElements.type = GraphicsEngineSpace::ShaderType::VERTEX;
		prefab->AddOnceBuffer(boneMatrixElements);

		struct PigVertex
		{
			HeraclesMath::Vector position;
			HeraclesMath::Vector normal;
			HeraclesMath::Vector texCoord;
			HeraclesMath::Vector tangent;
			HeraclesMath::Vector weights;
			unsigned int		 weightsIndex;
		};

		prefab->CreateVertexBuffer<PigVertex>(factory, [](const GraphicsEngineSpace::VertexData& data)-> PigVertex
			{
				PigVertex temp;
				temp.position = data.position;
				temp.normal = data.normal;
				temp.texCoord = { data.texCoord.x, data.texCoord.y, 0.0f, 0.0f };
				temp.tangent = data.tangent;
				temp.weights = data.weights1;
				temp.weightsIndex = data.weightIndex1;

				return temp;
			});

		transform.position.x += 2.0f;
		transform.scale = { 0.1f, 0.1f, 0.1f };
	}

	void Pig::Update(float tick)
	{
		transform.UpdateWorldTransform();

		if (Move() == true)
			animSwitch = true;
		else
			animSwitch = false;
	}

	void Pig::Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick)
	{
		using namespace GraphicsEngineSpace;

		auto& materials = prefab->GetMaterials();
		//auto materials = pbrModel->GetPrefab()->GetMaterials();

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

		//if (animSwitch == true)
		//	prefab->SetAnimationKey("Walk");
		//else
		//	prefab->SetAnimationKey("Idle");

		prefab->PrepareRender(transform.GetWorldTransform(), tick);
		prefab->Render(engine);
		//pbrModel->Render(engine);
	}

	void Pig::AddForce(const Vector& v)
	{
		velocity += v;
	}

	bool Pig::Move()
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

	void Pig::LookAt(const Vector& targetPos)
	{
		Matrix rtm = MatrixLookAtLH(transform.position, targetPos, Vector::UnitY);

		transform.rotation = ConvertRotationMatrixToEuler(MatrixInverse(rtm));
	}

	void Pig::SetMetallic(float metallic)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetMetallic(metallic);
	}

	void Pig::SetRoughness(float roughness)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetRoughness(roughness);
	}

	void Pig::SetLight(const Vector& dir, const Vector& color, int index)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetLightDirection(dir, index);
		pbrModel->SetLightColor(color, index);
	}
}