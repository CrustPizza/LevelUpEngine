/********************************
*								*
*	Blur.cpp					*
*								*
*	Created : 2022/07/20		*
*	Updated : 2022/07/22		*
*********************************/

#include "Blur.h"

namespace DX11
{
	Blur::Blur(ID3D11DeviceContext* deviceContext)
		: deviceContext(deviceContext)
		, param{}
		, shader(nullptr)
		, paramBuffer(nullptr)
		, verticalBlur(nullptr)
		, horizontalBlur(nullptr)
		, downSampler(nullptr)
		, combine(nullptr)
		, spriteBatch(nullptr)
	{

	}

	Blur::~Blur()
	{
		delete shader;
		delete paramBuffer;

		if (verticalBlur != nullptr)
		{
			verticalBlur->Release();
			delete verticalBlur;
		}

		if (horizontalBlur != nullptr)
		{
			horizontalBlur->Release();
			delete horizontalBlur;
		}

		delete downSampler;
		delete combine;
	}

	void Blur::Init(Factory* factory, ID3D11Device* device, DXGI_FORMAT format, DirectX::SpriteBatch* spriteBatch)
	{
		ShaderBase* gaussianBlur = factory->CreatePixelShader("GaussianBlurPS", "Shader/GaussianBlur/GaussianBlurPS.hlsl", "main", "ps_5_0");

		shader = dynamic_cast<PixelShader*>(gaussianBlur);

		BufferBase* buffer = factory->CreateConstantBuffer("BlurParameterCB", USAGE::DEFAULT, 0, sizeof(BlurParameter));

		paramBuffer = dynamic_cast<ConstantBuffer*>(buffer);

		this->spriteBatch = spriteBatch;

		verticalBlur = new RenderTexture(format);
		verticalBlur->SetDevice(device);
		horizontalBlur = new RenderTexture(format);
		horizontalBlur->SetDevice(device);

		downSampler = new DownSampling(deviceContext);
		downSampler->Init(factory, device, format, spriteBatch);
		downSampler->SetThreshold(0.0f);

		combine = new Combine(deviceContext);
		combine->Init(factory, device, format, spriteBatch);
	}

	void Blur::Clear()
	{
		const FLOAT color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		verticalBlur->ClearRenderTargetView(deviceContext, nullptr, color);
		horizontalBlur->ClearRenderTargetView(deviceContext, nullptr, color);
		downSampler->GetRenderTexture()->ClearRenderTargetView(deviceContext, nullptr, color);
		combine->Clear();
	}

	void Blur::operator()(RenderTexture* blurTarget, float theta, ID3D11DepthStencilView* depthView, ID3D11DepthStencilState* depthState)
	{
		long width = blurTarget->GetWidth() / 2;
		long height = blurTarget->GetHeight() / 2;

		verticalBlur->OnResize(width, height);
		horizontalBlur->OnResize(width, height);
		downSampler->OnResize(width, height);
		auto downSRV = (*downSampler)(blurTarget->GetShaderResourceView(), depthView, depthState);

		SetParameters(1.0f / static_cast<float>(width), 0.0f, theta);
		horizontalBlur->OMSetRenderTarget(deviceContext, depthView);
		spriteBatch->Begin(DirectX::SpriteSortMode_Immediate, nullptr, nullptr, depthState, nullptr,
			[=]()
			{
				shader->SetUpShader();
				paramBuffer->SetUpBuffer(8, &param, ShaderType::PIXEL);
			});
		spriteBatch->Draw(downSRV, RECT{ 0, 0, width, height });
		spriteBatch->End();

		SetParameters(0.0f, 1.0f / static_cast<float>(height), theta);
		verticalBlur->OMSetRenderTarget(deviceContext, depthView);
		spriteBatch->Begin(DirectX::SpriteSortMode_Immediate, nullptr, nullptr, depthState, nullptr,
			[=]()
			{
				shader->SetUpShader();
				paramBuffer->SetUpBuffer(8, &param, ShaderType::PIXEL);
			});
		spriteBatch->Draw(horizontalBlur->GetShaderResourceView(), RECT{ 0, 0, width, height });
		spriteBatch->End();

		(*combine)(blurTarget, verticalBlur->GetShaderResourceView(), depthView, depthState);
	}

	void Blur::SetParameters(float x, float y, float theta)
	{
		param.weights[0].x = HeraclesMath::ComputeGaussian(0, theta);
		param.blurOffset[0].x = 0.0f;
		param.blurOffset[0].y = 0.0f;

		float totalWeights = 0.0f;

		for (int i = 0; i < BLUR_DEPTH / 2; i++)
		{
			float weight = HeraclesMath::ComputeGaussian(i + 1.0f, theta);

			param.weights[i * 2 + 1].x = weight;
			param.weights[i * 2 + 2].x = weight;

			totalWeights += weight * 2;

			float sampleOffset = i * 2.0f + 1.5f;

			HeraclesMath::Vector delta = { x * sampleOffset, y * sampleOffset };

			param.blurOffset[i * 2 + 1].x = delta.x;
			param.blurOffset[i * 2 + 1].y = delta.y;
			param.blurOffset[i * 2 + 2].x = -delta.x;
			param.blurOffset[i * 2 + 2].y = -delta.y;
		}

		for (int i = 0; i < BLUR_DEPTH; i++)
		{
			param.weights[i].x /= totalWeights;
		}
	}
}