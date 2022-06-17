/********************************
*								*
*	DirectX11.cpp				*
*								*
*	Created : 2022/06/11		*
*	Updated : 2022/06/17		*
*********************************/

#include "DirectX11.h"
#include <DirectXColors.h>
#include <tchar.h>

#define RELEASE_PTR(x) \
if ((x) != nullptr)\
{\
	(x)->Release();\
	(x) = nullptr;\
}

#define DELETE_RELEASE_PTR(x) \
if ((x) != nullptr)\
{\
	(x)->Release();\
	delete (x);\
	(x) = nullptr;\
}

namespace DX11
{
	DirectX11::DirectX11()
		: d3dDevice(nullptr)
		, deviceContext(nullptr)
		, swapChain(nullptr)
		, annotation(nullptr)

		, renderTarget(nullptr)
		, renderTargetView(nullptr)

		, depth(nullptr)
		, depthView(nullptr)

		, blendState(nullptr)
		, depthState(nullptr)

		, viewPort{}

		, spriteBatch(nullptr)
		, spriteFont(nullptr)

		, backBufferFormat(DXGI_FORMAT_B8G8R8A8_UNORM)
		, depthBufferFormat(DXGI_FORMAT_D32_FLOAT)
		, driverType(D3D_DRIVER_TYPE_NULL)
		, featureLevel(D3D_FEATURE_LEVEL_11_1)

		, backScreen(nullptr)
		, rt1(nullptr)
		, rt2(nullptr)
		, rt3(nullptr)
	{

	}

	DirectX11::~DirectX11()
	{

	}

	bool DirectX11::InitDevice(HWND hWnd, UINT width, UINT height)
	{
		HRESULT hr = S_OK;
		UINT deviceFlags = 0;

#ifdef _DEBUG
		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // D3D Debug Mode ����
		// ����� ��忡���� ��Ÿ�� �� ������ �Ķ���͸� �����Ѵ�.
#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,	// GPU ���
			D3D_DRIVER_TYPE_WARP,		// GPU�� ������ CPU�� SIMD���� ����� �����ϴ� ��� (���� ó��)
			D3D_DRIVER_TYPE_REFERENCE	// 100% ����Ʈ���� ����̽�, GPU ��� ��밡��
		};

		UINT driverTypesSize = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,		// �ֿ켱������ �ϵ����� �����Ǳ� �ٶ�� ��� ����
			D3D_FEATURE_LEVEL_11_0,		// ���� �ȵȴٸ� �̰�
			D3D_FEATURE_LEVEL_10_1,		// ...
			D3D_FEATURE_LEVEL_10_0
		};

		UINT featureLevelsSize = ARRAYSIZE(featureLevels);

		// ���� ���۸� == ���� ü��
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;						// ����
		sd.BufferDesc.Height = height;						// ����
		sd.BufferDesc.Format = backBufferFormat;	// ���� ����
		sd.BufferDesc.RefreshRate.Numerator = 0;			// ������ ����
		sd.BufferDesc.RefreshRate.Denominator = 1;			// ������ �и�, 1�ʿ� 60������
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = true;	// â��� ����

		for (UINT i = 0; i < driverTypesSize; i++)
		{
			// �����Ǵ� Driver�� FeatureLevel�� Ȯ���Ͽ� D3D ��ü���� �����Ѵ�.
			driverType = driverTypes[i];

			// Helper �Լ�, Device ���� ������ SwapChain ���� ������ �и��ؼ� ����� �� ����.
			hr = D3D11CreateDeviceAndSwapChain(
				nullptr,
				driverType,
				nullptr,
				deviceFlags,
				featureLevels,
				featureLevelsSize,
				D3D11_SDK_VERSION,
				&sd,
				&swapChain,
				&d3dDevice,
				&featureLevel,
				&deviceContext);

			if (SUCCEEDED(hr) == true)
				break;
		}

		if (FAILED(hr) == true)
			return false;

		CreateBackScreen();

		if (OnResize(width, height) != true)
			return false;

		// Blend state
		D3D11_BLEND_DESC descBlend = {};
		ZeroMemory(&descBlend, sizeof(D3D11_BLEND_DESC));

		descBlend.RenderTarget[0].BlendEnable = true;
		descBlend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		descBlend.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		descBlend.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descBlend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descBlend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descBlend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descBlend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		hr = d3dDevice->CreateBlendState(&descBlend, &blendState);
		if (FAILED(hr))
			return false;

		deviceContext->QueryInterface<ID3DUserDefinedAnnotation>(&annotation);

		spriteBatch = new DirectX::SpriteBatch(deviceContext);
		spriteFont = new DirectX::SpriteFont(d3dDevice, _T("Font/gulim9k.spritefont"));
		spriteFont->SetLineSpacing(14.0f);

		return true;
	}

	bool DirectX11::OnResize(UINT width, UINT height)
	{
		if (d3dDevice == nullptr)
			return false;

		HRESULT hr = S_OK;

		// Resize�ϱ����� ���۸� �ʱ�ȭ�϶�� ������ ���. �׷��� �ʱ�ȭ
		RELEASE_PTR(renderTarget);
		RELEASE_PTR(renderTargetView);
		RELEASE_PTR(depth);
		RELEASE_PTR(depthView);
		RELEASE_PTR(depthState);

		// ���� ������� �����ϰ� ���� ������ ����
		hr = swapChain->ResizeBuffers(1, width, height, backBufferFormat, 0);

		if (FAILED(hr) == true)
			return false;

		hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&renderTarget));

		if (FAILED(hr) == true)
			return false;

		hr = d3dDevice->CreateRenderTargetView(renderTarget, nullptr, &renderTargetView);

		if (FAILED(hr) == true)
			return false;

		// Create depth stencil texture
		D3D11_TEXTURE2D_DESC descDepth = {};
		descDepth.Width = width;
		descDepth.Height = height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = depthBufferFormat;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;

		hr = d3dDevice->CreateTexture2D(&descDepth, nullptr, &depth);
		if (FAILED(hr))
			return false;

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		hr = d3dDevice->CreateDepthStencilView(depth, &descDSV, &depthView);
		if (FAILED(hr))
			return false;

		// Depth state
		D3D11_DEPTH_STENCIL_DESC descDSS = {};
		ZeroMemory(&descDSS, sizeof(D3D11_DEPTH_STENCIL_DESC));

		descDSS.DepthEnable = true;
		descDSS.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSS.DepthFunc = D3D11_COMPARISON_LESS;

		descDSS.StencilEnable = false;
		descDSS.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		descDSS.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

		descDSS.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSS.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		descDSS.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSS.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		hr = d3dDevice->CreateDepthStencilState(&descDSS, &depthState);
		if (FAILED(hr))
			return false;

		// �׷��� ȭ���� ���� ����
		viewPort.Width = static_cast<FLOAT>(width);
		viewPort.Height = static_cast<FLOAT>(height);
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		// RS == Rasterizer Stage
		deviceContext->RSSetViewports(1, &viewPort);

		backScreen->OnResize(width, height);

		return true;
	}

	bool DirectX11::CreateBackScreen()
	{
		if (backScreen != nullptr)
			return false;

		backScreen = new RenderTexture(backBufferFormat);

		if (backScreen == nullptr)
			return false;

		backScreen->SetDevice(d3dDevice);

		return true;
	}

	void DirectX11::BeginRender()
	{
		annotation->BeginEvent(_T("Clear"));

		auto backRT = backScreen->GetRenderTargetView();

		deviceContext->OMSetRenderTargets(1, &renderTargetView, depthView);
		deviceContext->ClearRenderTargetView(renderTargetView, DirectX::Colors::AliceBlue);
		deviceContext->ClearDepthStencilView(depthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		//deviceContext->OMSetDepthStencilState(depthState, 0);
		deviceContext->OMSetRenderTargets(1, &backRT, depthView);
		deviceContext->ClearRenderTargetView(backScreen->GetRenderTargetView(), DirectX::Colors::Black);

		annotation->EndEvent();
	}

	void DirectX11::Render()
	{

	}

	void DirectX11::PostProcess()
	{
		deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
		spriteBatch->Begin();
		auto backSRV = backScreen->GetShaderResourceView();
		spriteBatch->Draw(backSRV, RECT{ 0, 0, static_cast<long>(viewPort.Width * 0.75f), static_cast<long>(viewPort.Height) });
		spriteBatch->End();

		ID3D11ShaderResourceView* null[] = { nullptr, nullptr };
		deviceContext->PSSetShaderResources(0, 2, null);
	}

	void DirectX11::EndRender()
	{
		annotation->BeginEvent(_T("Present"));

		swapChain->Present(0, 0);

		annotation->EndEvent();
	}

	void DirectX11::Release()
	{
		if (deviceContext != nullptr)
			deviceContext->ClearState();

		RELEASE_PTR(d3dDevice);
		RELEASE_PTR(deviceContext);
		RELEASE_PTR(swapChain);
		RELEASE_PTR(annotation);

		RELEASE_PTR(renderTarget);
		RELEASE_PTR(renderTargetView);

		RELEASE_PTR(depth);
		RELEASE_PTR(depthView);

		RELEASE_PTR(blendState);
		RELEASE_PTR(depthState);

		delete spriteBatch;
		delete spriteFont;

		DELETE_RELEASE_PTR(backScreen);
	}

	DirectX11DeclSpec DirectX11* CreateDirectX11()
	{
		return new DirectX11;
	}
}