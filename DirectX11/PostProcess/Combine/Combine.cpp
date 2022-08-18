/********************************
*								*
*	Combine.cpp					*
*								*
*	Created : 2022/07/22		*
*	Updated : 2022/07/25		*
*********************************/

#include "Combine.h"

namespace DX11
{
	Combine::Combine(ID3D11DeviceContext* deviceContext)
		: deviceContext(deviceContext)
		, shader(nullptr)
		, paramBuffer(nullptr)
		, combineTexture(nullptr)
		, spriteBatch(nullptr)
		, param{ 1.0f, 1.0f, 1.0f, 1.0f }
	{

	}

	Combine::~Combine()
	{
		delete shader;
		delete paramBuffer;

		if (combineTexture != nullptr)
		{
			combineTexture->Release();
			delete combineTexture;
		}
	}

	void Combine::Init(Factory* factory, ID3D11Device* device, DXGI_FORMAT format, DirectX::SpriteBatch* spriteBatch)
	{
		ShaderBase* combinePS = factory->CreatePixelShader("TextureCombinePS", "Shader/TextureCombine/TextureCombinePS.hlsl", "main", "ps_5_0");
		this->shader = dynamic_cast<PixelShader*>(combinePS);

		BufferBase* buffer = factory->CreateConstantBuffer("TextureCombineCB", USAGE::DEFAULT, 0, sizeof(CombineParameter));
		this->paramBuffer = dynamic_cast<ConstantBuffer*>(buffer);

		this->spriteBatch = spriteBatch;

		combineTexture = new RenderTexture(format);
		combineTexture->SetDevice(device);
	}

	void Combine::Clear()
	{
		const FLOAT color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		combineTexture->ClearRenderTargetView(deviceContext, nullptr, color);
	}

	void Combine::operator()(RenderTexture* dest, ID3D11ShaderResourceView* src, ID3D11DepthStencilView* depthView, ID3D11DepthStencilState* depthState)
	{
		ID3D11ShaderResourceView* null[] = { nullptr, nullptr };

		long width = dest->GetWidth();
		long height = dest->GetHeight();

		combineTexture->OnResize(width, height);

		combineTexture->OMSetRenderTarget(deviceContext, depthView);
		spriteBatch->Begin(DirectX::SpriteSortMode_Immediate, nullptr, nullptr, depthState, nullptr,
			[=]()
			{
				shader->SetUpShader();
				paramBuffer->SetUpBuffer(8, &param, ShaderType::PIXEL);
				deviceContext->PSSetShaderResources(1, 1, &src);
			});
		spriteBatch->Draw(dest->GetShaderResourceView(), RECT{ 0, 0, width, height });
		spriteBatch->End();

		deviceContext->PSSetShaderResources(0, 2, null);
		deviceContext->CopyResource(dest->GetRenderTarget(), combineTexture->GetRenderTarget());
	}
}