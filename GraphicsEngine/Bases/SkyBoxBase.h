/********************************
*								*
*	Sky Box Base.h				*
*								*
*	Created : 2022/08/03		*
*	Updated : 2022/08/03		*
*********************************/

#pragma once

#include "Bases/ShaderBase.h"
#include "Bases/BufferBase.h"
#include "Bases/TextureBase.h"
#include "Bases/SamplerBase.h"
#include "Bases/GraphicsEngineBase.h"
#include "Bases/ResourceBase.h"
#include "../HeraclesMath/HeraclesMath.h"

#pragma comment(lib, "../MathLibrary/HeraclesMath.lib")

namespace GraphicsEngineSpace
{
	using HeraclesMath::Matrix;
	class Factory;

	class SkyBoxBase : public ResourceBase<SkyBoxBase>
	{
		ShaderBase* vertexShader;
		ShaderBase* pixelShader;

		BufferBase* vertexBuffer;
		BufferBase* indexBuffer;
		BufferBase* viewProjBuffer;

		TextureBase* cubeMap;
		SamplerBase* sampler;

	public:
		SkyBoxBase()
			: vertexShader(nullptr)
			, pixelShader(nullptr)
			, vertexBuffer(nullptr)
			, indexBuffer(nullptr)
			, viewProjBuffer(nullptr)
			, cubeMap(nullptr)
			, sampler(nullptr) {}
		~SkyBoxBase() = default;

		void SetTexture(TextureBase* cubeMap) { this->cubeMap = cubeMap; }

		void Render(GraphicsEngineBase* engine, Matrix viewProjection) const
		{
			if (vertexBuffer == nullptr || indexBuffer == nullptr || cubeMap == nullptr)
				return;

			if (vertexShader != nullptr)
				vertexShader->SetUpShader();

			if (pixelShader != nullptr)
				pixelShader->SetUpShader();

			if (viewProjBuffer != nullptr)
				viewProjBuffer->SetUpBuffer(0, &viewProjection, ShaderType::VERTEX);

			if (sampler != nullptr)
				sampler->SetUpSampler(0, ShaderType::PIXEL);

			cubeMap->SetUpTexture(0, ShaderType::PIXEL);

			engine->DrawMesh(vertexBuffer, indexBuffer);
		}

	private:
		friend Factory;
	};
}