/********************************
*								*
*	Render Texture.h			*
*								*
*	Created : 2022/06/14		*
*	Updated : 2022/06/15		*
*********************************/

#pragma once
#include <d3d11_1.h>

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

	void SetDevice(ID3D11Device* device);
	bool OnResize(UINT width, UINT height);
	void Release();
};