/********************************
*								*
*	Effect 2D.cpp				*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#include "Effect2D.h"

namespace DX11
{
	using namespace GraphicsEngineSpace;
	using namespace DirectX;

	Effect2D::Effect2D(ID3D11DeviceContext* deviceContext)
		: vertexShader(nullptr)
		, pixelShader(nullptr)
		, vertexBuffer(nullptr)
		, indexBuffer(nullptr)
		, viewProjCB(nullptr)
		, sampler(nullptr)
		, deviceContext(deviceContext)
	{

	}

	Effect2D::~Effect2D()
	{
		delete vertexShader;
		delete pixelShader;
		delete vertexBuffer;
		delete indexBuffer;
		delete viewProjCB;
		delete sampler;
	}

	void Effect2D::Init(Factory* factory)
	{
		LayoutBase* layout = factory->CreateLayout("Effect2DLayout");

		layout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
		layout->AddElements("TEXCOORD", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);

		vertexShader = factory->CreateVertexShader("Effect2DVS", "Shader/Texture2D/Texture2DVS.hlsl", "main", "vs_5_0", layout);
		pixelShader = factory->CreatePixelShader("Effect2DPS", "Shader/Texture2D/Texture2DPS.hlsl", "main", "ps_5_0");

		delete layout;

		TextureVertex temp[4];

		vertexBuffer = dynamic_cast<VertexBuffer*>(factory->CreateVertexBuffer("Effect2DVB", USAGE::DYNAMIC, D3D11_CPU_ACCESS_WRITE, sizeof(TextureVertex), temp, 4));

		WORD indices[] =
		{
			0, 1, 2,
			1, 3, 2
		};

		indexBuffer = factory->CreateIndexBuffer("Effect2DIB", USAGE::DEFAULT, 0, sizeof(WORD), indices, 6);

		viewProjCB = factory->CreateConstantBuffer("Effect2DCB", USAGE::DEFAULT, 0, sizeof(DirectX::XMMATRIX));

		sampler = factory->CreateSampler("Effect2DSampler", FilterOption::LINEAR);
	}

	void Effect2D::SetVertexShader(ShaderBase* shader)
	{
		if (vertexShader != nullptr)
			delete vertexShader;

		vertexShader = shader;
	}

	void Effect2D::SetPixelShader(ShaderBase* shader)
	{
		if (pixelShader != nullptr)
			delete pixelShader;

		pixelShader = shader;
	}

	void Effect2D::SetVertexBuffer(VertexBuffer* buffer)
	{
		if (vertexBuffer != nullptr)
			delete vertexBuffer;

		vertexBuffer = buffer;
	}

	void Effect2D::SetIndexBuffer(BufferBase* buffer)
	{
		if (indexBuffer != nullptr)
			delete indexBuffer;

		indexBuffer = buffer;
	}

	void Effect2D::SetViewProjBuffer(BufferBase* buffer)
	{
		if (viewProjCB != nullptr)
			delete viewProjCB;

		viewProjCB = buffer;
	}

	void Effect2D::SetSampler(SamplerBase* sampler)
	{
		if (this->sampler != nullptr)
			delete this->sampler;

		this->sampler = sampler;
	}

	void Effect2D::Draw(ID3D11ShaderResourceView* texture, DirectX::XMVECTOR position[3], DirectX::XMVECTOR texCoord[3], void* transformMatrix)
	{
		auto buffer = vertexBuffer->GetBuffer();
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;

		deviceContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedBuffer);

		auto vertices = static_cast<TextureVertex*>(mappedBuffer.pData);

		for (int i = 0; i < 3; i++)
		{
			vertices[i].position = position[i];
			vertices[i].texCoord = texCoord[i];
		}

		vertices[3].position = position[1] + position[2] - position[0];
		vertices[3].texCoord = { texCoord[1].m128_f32[0], texCoord[2].m128_f32[1] };

		deviceContext->Unmap(buffer, 0);

		vertexShader->SetUpShader();
		pixelShader->SetUpShader();

		vertexBuffer->SetUpBuffer(0, nullptr, ShaderType::NONE);
		indexBuffer->SetUpBuffer(0, nullptr, ShaderType::NONE);

		viewProjCB->SetUpBuffer(4, transformMatrix, ShaderType::VERTEX);
		deviceContext->PSSetShaderResources(0, 1, &texture);

		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		deviceContext->DrawIndexed(6, 0, 0);
	}
}