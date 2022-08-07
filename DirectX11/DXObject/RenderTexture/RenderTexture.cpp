/********************************
*								*
*	Render Texture.cpp			*
*								*
*	Created : 2022/06/14		*
*	Updated : 2022/06/15		*
*********************************/

#include "RenderTexture.h"

#define RELEASE_PTR(x) \
if ((x) != nullptr)\
{\
	(x)->Release();\
	(x) = nullptr;\
}

namespace DX11
{
	RenderTexture::RenderTexture(DXGI_FORMAT format)
		: device(nullptr)
		, renderTarget(nullptr)
		, renderTargetView(nullptr)
		, shaderResourceView(nullptr)
		, format(format)
		, width(1)
		, height(1)
	{

	}

	RenderTexture::~RenderTexture()
	{

	}

	ID3D11Texture2D* RenderTexture::GetRenderTarget() const
	{
		return renderTarget;
	}

	ID3D11RenderTargetView* RenderTexture::GetRenderTargetView() const
	{
		return renderTargetView;
	}

	ID3D11ShaderResourceView* RenderTexture::GetShaderResourceView() const
	{
		return shaderResourceView;
	}

	DXGI_FORMAT RenderTexture::GetFormat()
	{
		return format;
	}

	UINT RenderTexture::GetWidth()
	{
		return width;
	}

	UINT RenderTexture::GetHeight()
	{
		return height;
	}

	void RenderTexture::SetDevice(ID3D11Device* device)
	{
		this->device = nullptr;
		this->device = device;
	}

	bool RenderTexture::OnResize(UINT width, UINT height)
	{
		if (this->width == width && this->height == height)
			return false;

		if (device == nullptr)
			return false;

		HRESULT hr = S_OK;

		this->width = width < 1 ? 1 : width;
		this->height = height < 1 ? 1 : height;

		RELEASE_PTR(renderTarget);
		RELEASE_PTR(renderTargetView);
		RELEASE_PTR(shaderResourceView);

		// Create RT
		CD3D11_TEXTURE2D_DESC renderTargetDesc
		{
			format,
			width,
			height,
			1,
			1,
			D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE,
			D3D11_USAGE_DEFAULT,
			0,
			1
		};

		hr = device->CreateTexture2D(&renderTargetDesc, nullptr, &renderTarget);

		if (FAILED(hr))
			return false;

		// Create RTV
		CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc
		{
			D3D11_RTV_DIMENSION_TEXTURE2D,
			format
		};

		hr = device->CreateRenderTargetView(renderTarget, &renderTargetViewDesc, &renderTargetView);

		if (FAILED(hr))
			return false;

		// Create SRV
		CD3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc
		{
			D3D11_SRV_DIMENSION_TEXTURE2D,
			format
		};

		hr = device->CreateShaderResourceView(renderTarget, &shaderResourceViewDesc, &shaderResourceView);

		if (FAILED(hr))
			return false;

		return true;
	}

	void RenderTexture::Release()
	{
		RELEASE_PTR(renderTarget);
		RELEASE_PTR(renderTargetView);
		RELEASE_PTR(shaderResourceView);
		this->device = nullptr;
	}

	void RenderTexture::OMSetRenderTarget(ID3D11DeviceContext* deviceContext, ID3D11DepthStencilView* depthView)
	{
		deviceContext->OMSetRenderTargets(1, &renderTargetView, depthView);
	}

	void RenderTexture::ClearRenderTargetView(ID3D11DeviceContext* deviceContext, ID3D11DepthStencilView* depthView, const FLOAT color[4])
	{
		deviceContext->OMSetRenderTargets(1, &renderTargetView, depthView);
		deviceContext->ClearRenderTargetView(renderTargetView, color);
	}
}