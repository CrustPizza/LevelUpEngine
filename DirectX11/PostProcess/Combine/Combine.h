/********************************
*								*
*	Combine.h					*
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
	class Combine
	{
		struct CombineParameter
		{
			float baseSaturation;
			float sourceSaturation;
			float baseIntensity;
			float sourceIntensity;
		};

		ID3D11DeviceContext* deviceContext;
		PixelShader* shader;
		ConstantBuffer* paramBuffer;
		RenderTexture* combineTexture;
		DirectX::SpriteBatch* spriteBatch;

	public:
		CombineParameter param;

	public:
		Combine(ID3D11DeviceContext* deviceContext);
		~Combine();

		void Init(Factory* factory, ID3D11Device* device, DXGI_FORMAT format, DirectX::SpriteBatch* spriteBatch);
		void Clear();

		void operator ()(RenderTexture* dest, ID3D11ShaderResourceView* src, ID3D11DepthStencilView* depthView = nullptr, ID3D11DepthStencilState* depthState = nullptr);
	};
}