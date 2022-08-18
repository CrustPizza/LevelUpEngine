/********************************
*								*
*	Down Sampling.cpp			*
*								*
*	Created : 2022/07/22		*
*	Updated : 2022/07/25		*
*********************************/

#include "DownSampling.h"

namespace DX11
{
	DownSampling::DownSampling(ID3D11DeviceContext* deviceContext)
		: deviceContext(deviceContext)
		, shader(nullptr)
		, threshBuffer(nullptr)
		, downTexture(nullptr)
		, spriteBatch(nullptr)
		, threshold{}
	{

	}

	DownSampling::~DownSampling()
	{
		if (downTexture != nullptr)
		{
			downTexture->Release();
			delete downTexture;
		}

		delete threshBuffer;
		delete shader;
	}

	void DownSampling::Init(Factory* factory, ID3D11Device* device, DXGI_FORMAT format, DirectX::SpriteBatch* spriteBatch, float threshold)
	{
		ShaderBase* downSamplePS = factory->CreatePixelShader("DownSamplingPS", "Shader/DownSampling/DownSamplingPS.hlsl", "main", "ps_5_0");
		this->shader = dynamic_cast<PixelShader*>(downSamplePS);

		BufferBase* buffer = factory->CreateConstantBuffer("DownSamplingParameterCB", USAGE::DEFAULT, 0, sizeof(HeraclesMath::Vector));
		threshBuffer = dynamic_cast<ConstantBuffer*>(buffer);

		downTexture = new RenderTexture(format);

		if (downTexture == nullptr)
			return;

		this->spriteBatch = spriteBatch;
		this->threshold.x = threshold;

		downTexture->SetDevice(device);
	}

	void DownSampling::OnResize(long width, long height)
	{
		downTexture->OnResize(width, height);
	}

	void DownSampling::SetThreshold(float threshold)
	{
		this->threshold.x = threshold;
	}

	RenderTexture* DownSampling::GetRenderTexture()
	{
		return downTexture;
	}

	ID3D11ShaderResourceView* DownSampling::operator()(ID3D11ShaderResourceView* src, ID3D11DepthStencilView* depthView, ID3D11DepthStencilState* depthState)
	{
		long width = downTexture->GetWidth();
		long height = downTexture->GetHeight();

		downTexture->OMSetRenderTarget(deviceContext, depthView);
		Draw(src, width, height, depthState);

		return downTexture->GetShaderResourceView();
	}

	void DownSampling::Draw(ID3D11ShaderResourceView* texture, long width, long height, ID3D11DepthStencilState* depthState)
	{
		spriteBatch->Begin(DirectX::SpriteSortMode_Immediate, nullptr, nullptr, depthState, nullptr,
			[=]()
			{
				shader->SetUpShader();
				threshBuffer->SetUpBuffer(8, &threshold, ShaderType::PIXEL);
			});
		spriteBatch->Draw(texture, RECT{ 0, 0, width, height });
		spriteBatch->End();
	}
}