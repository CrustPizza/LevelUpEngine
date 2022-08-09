/********************************
*								*
*	Effect 2D.h					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#pragma once

#include "Factory/Factory.h"

#include "DXObject/Shader/VertexShader/VertexShader.h"
#include "DXObject/Shader/PixelShader/PixelShader.h"

#include "DXObject/Buffer/VertexBuffer/VertexBuffer.h"
#include "DXObject/Buffer/IndexBuffer/IndexBuffer.h"

#include "DXObject/Sampler/Sampler.h"
#include "DXObject/Layout/Layout.h"

#include <DirectXMath.h>

namespace DX11
{
	class Effect2D
	{
		struct TextureVertex
		{
			DirectX::XMVECTOR position;
			DirectX::XMVECTOR texCoord;
		};

		ShaderBase* vertexShader;
		ShaderBase* pixelShader;

		VertexBuffer* vertexBuffer;
		BufferBase* indexBuffer;
		BufferBase* viewProjCB;

		SamplerBase* sampler;
		ID3D11DeviceContext* deviceContext;

	public:
		Effect2D(ID3D11DeviceContext* deviceContext);
		~Effect2D();

		void Init(Factory* factory);

		void SetVertexShader(ShaderBase* shader);
		void SetPixelShader(ShaderBase* shader);

		void SetVertexBuffer(VertexBuffer* buffer);
		void SetIndexBuffer(BufferBase* buffer);
		void SetViewProjBuffer(BufferBase* buffer);

		void SetSampler(SamplerBase* sampler);

		void Draw(ID3D11ShaderResourceView* texture, DirectX::XMVECTOR position[3], DirectX::XMVECTOR texCoord[3], void* transformMatrix);
	};
}