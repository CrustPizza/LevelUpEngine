/********************************
*								*
*	Cube.h						*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#pragma once

#include "../GraphicsEngine/Bases/PrefabBase.h"
#include "../GraphicsEngine/GraphicsEngine/Factory/Factory.h"
#include "Object/ObjectBase/ObjectBase.h"

namespace GameEngineSpace
{
	using GraphicsEngineSpace::PrefabBase;
	using GraphicsEngineSpace::ModelBase;
	using GraphicsEngineSpace::ShaderBase;
	using GraphicsEngineSpace::BufferBase;

	class Cube : public ObjectBase
	{
		struct cbMatrix
		{
			HeraclesMath::Matrix worldMatrix;
			HeraclesMath::Matrix worldInvMatrix;
		};

		PrefabBase* prefab;
		
	public:
		Cube();
		~Cube();

		void Init(GraphicsEngineSpace::Factory* factory, ModelBase* model, ShaderBase* vertexShader, ShaderBase* pixelShader, BufferBase* matrixBuffer);
		void Update(float tick) override;
		void Render(GraphicsEngineSpace::GraphicsEngineBase* engine) override;
	};
}