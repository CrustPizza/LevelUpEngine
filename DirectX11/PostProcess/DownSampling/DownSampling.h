/********************************
*								*
*	Down Sampling.h				*
*								*
*	Created : 2022/07/22		*
*	Updated : 2022/07/25		*
*********************************/

#pragma once

#include "DXObject/RenderTexture/RenderTexture.h"
#include "DXObject/Shader/PixelShader/PixelShader.h"
#include "DXObject/Buffer/ConstantBuffer/ConstantBuffer.h"
#include "Inc/SpriteBatch.h"
#include "Factory/Factory.h"

namespace DX11
{
	class DownSampling
	{
		ID3D11DeviceContext* deviceContext;

		PixelShader* shader;
		ConstantBuffer* threshBuffer;

		RenderTexture* downTexture;
		DirectX::SpriteBatch* spriteBatch;
		HeraclesMath::Vector threshold;

	public:
		DownSampling(ID3D11DeviceContext* deviceContext);
		~DownSampling();

		void Init(Factory* factory, ID3D11Device* device, DXGI_FORMAT format, DirectX::SpriteBatch* spriteBatch, float threshold = 0.0f);
		void OnResize(long width, long height);
		void SetThreshold(float threshold);

		RenderTexture* GetRenderTexture();

		ID3D11ShaderResourceView* operator ()(ID3D11ShaderResourceView* src, ID3D11DepthStencilView* depthView = nullptr, ID3D11DepthStencilState* depthState = nullptr);

	private:
		void Draw(ID3D11ShaderResourceView* texture, long width, long height, ID3D11DepthStencilState* depthState);
	};
}