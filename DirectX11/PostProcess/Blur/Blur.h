/********************************
*								*
*	Blur.h						*
*								*
*	Created : 2022/07/20		*
*	Updated : 2022/07/22		*
*********************************/

#pragma once

#include "Factory/Factory.h"

#include "DXObject/Shader/PixelShader/PixelShader.h"
#include "DXObject/Buffer/ConstantBuffer/ConstantBuffer.h"

#include "PostProcess/DownSampling/DownSampling.h"
#include "PostProcess/Combine/Combine.h"

#include "../HeraclesMath/HeraclesMath.h"

#pragma comment(lib, "../MathLibrary/HeraclesMath.lib")

namespace DX11
{
	constexpr int BLUR_DEPTH = 15;

	class Bloom;

	class Blur
	{
		struct BlurParameter
		{
			HeraclesMath::Vector blurOffset[BLUR_DEPTH];
			HeraclesMath::Vector weights[BLUR_DEPTH];
		};

		ID3D11DeviceContext* deviceContext;

		BlurParameter param;
		PixelShader* shader;
		ConstantBuffer* paramBuffer;

		RenderTexture* verticalBlur;
		RenderTexture* horizontalBlur;
		DownSampling* downSampler;
		Combine* combine;

		DirectX::SpriteBatch* spriteBatch;
		
	public:
		Blur(ID3D11DeviceContext* deviceContext);
		~Blur();

		void Init(Factory* factory, ID3D11Device* device, DXGI_FORMAT format, DirectX::SpriteBatch* spriteBatch);
		void Clear();

		void operator ()(RenderTexture* blurTarget, float theta, ID3D11DepthStencilView* depthView = nullptr, ID3D11DepthStencilState* depthState = nullptr);

	private:
		void SetParameters(float x, float y, float theta);

		friend Bloom;
	};
}