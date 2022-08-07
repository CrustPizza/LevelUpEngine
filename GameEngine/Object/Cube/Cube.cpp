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
		transform.scale *= 0.1f;
	}

	Cube::~Cube()
	{

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

		prefab->Update(transform.GetWorldTransform(), tick);
	}

	void Cube::Render(GraphicsEngineSpace::GraphicsEngineBase* engine)
	{

		prefab->Render(engine);
	}
}