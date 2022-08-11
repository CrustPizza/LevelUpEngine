/********************************
*								*
*	Cube.cpp					*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#include "Cube.h"

namespace GameEngineSpace
{
	using GraphicsEngineSpace::USAGE;

	Cube::Cube()
		: prefab(nullptr)
	{
		transform.scale *= 2.0f;
	}

	Cube::~Cube()
	{

	}

	void Cube::Init(GraphicsEngineSpace::Factory* factory, ModelBase* model)
	{
		pbrModel = factory->CreateNoneTextureModel("CubePBR", model);
		pbrModel->SetAlpha(1.0f);
		pbrModel->SetMetallic(1.0f);
		pbrModel->SetRoughness(0.2f);

		prefab = pbrModel->GetPrefab();

		transform.position.y -= 5.0f;
		transform.scale.x *= 50.0f;
		transform.scale.z *= 50.0f;
	}

	void Cube::Init(GraphicsEngineSpace::Factory* factory, ModelBase* model, ShaderBase* vertexShader, ShaderBase* pixelShader, BufferBase* matrixBuffer)
	{
		prefab = factory->CreatePrefab("CubePrefab", model, matrixBuffer, 0);
		prefab->SetVertexShader(vertexShader);
		prefab->SetPixelShader(pixelShader);

		struct CubeVertex
		{
			HeraclesMath::Vector position;
			HeraclesMath::Vector color;
		};

		prefab->CreateVertexBuffer<CubeVertex>(factory, [](const GraphicsEngineSpace::VertexData& data)-> CubeVertex
			{
				CubeVertex temp;
				temp.position = data.position;
				temp.color = { 1.0f, 1.0f, 1.0f, 1.0f };

				return temp;
			});
	}

	void Cube::Update(float tick)
	{
		transform.UpdateWorldTransform();
	}

	void Cube::Render(GraphicsEngineSpace::GraphicsEngineBase* engine, float tick)
	{
		prefab->PrepareRender(transform.GetWorldTransform(), tick);
		prefab->Render(engine);
	}

	void Cube::SetLight(const Vector& dir, const Vector& color, int index)
	{
		if (pbrModel == nullptr)
			return;

		pbrModel->SetLightDirection(dir, index);
		pbrModel->SetLightColor(color, index);
	}
}