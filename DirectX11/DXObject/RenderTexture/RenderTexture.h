/********************************
*								*
*	Render Texture.h			*
*								*
*	Created : 2022/06/14		*
*	Updated : 2022/06/17		*
*********************************/

#pragma once

#include <d3d11_1.h>
#include "DXObject/DXObjectBase.h"

namespace DX11
{
	class RenderTexture
	{
		ID3D11Device* device;
		ID3D11Texture2D* renderTarget;
		ID3D11RenderTargetView* renderTargetView;
		ID3D11ShaderResourceView* shaderResourceView;

		DXGI_FORMAT format;

		UINT width;
		UINT height;

	public:
		RenderTexture(DXGI_FORMAT format);
		~RenderTexture();

		ID3D11Texture2D* GetRenderTarget() const;
		ID3D11RenderTargetView* GetRenderTargetView() const;
		ID3D11ShaderResourceView* GetShaderResourceView() const;

		DXGI_FORMAT GetFormat();
		UINT GetWidth();
		UINT GetHeight();

		void SetDevice(ID3D11Device* device);
		bool OnResize(UINT width, UINT height);
		void Release();

		void OMSetRenderTarget(ID3D11DeviceContext* deviceContext, ID3D11DepthStencilView* depthView = nullptr);
		void ClearRenderTargetView(ID3D11DeviceContext* deviceContext, ID3D11DepthStencilView* depthView, const FLOAT color[4]);
	};
}