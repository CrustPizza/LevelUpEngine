/********************************
*								*
*	DirectX11.cpp				*
*								*
*	Created : 2022/06/11		*
*	Updated : 2022/07/25		*
*********************************/

#include "DirectX11.h"
#include <DirectXColors.h>
#include <tchar.h>
#include <DirectXMath.h>

#include "Factory/Factory.h"

#include "DXObject/Buffer/VertexBuffer/VertexBuffer.h"
#include "DXObject/Buffer/IndexBuffer/IndexBuffer.h"

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
		, annotationCount(0)

		, renderTarget(nullptr)
		, renderTargetView(nullptr)

		, depth(nullptr)
		, depthView(nullptr)

		, blendState(nullptr)
		, depthState(nullptr)

		, viewPort{}

		, spriteBatch(nullptr)
		, spriteFont(nullptr)
		, effect2D(nullptr)

		, backBufferFormat(DXGI_FORMAT_B8G8R8A8_UNORM)
		, depthBufferFormat(DXGI_FORMAT_D32_FLOAT)
		, driverType(D3D_DRIVER_TYPE_NULL)
		, featureLevel(D3D_FEATURE_LEVEL_11_1)

		, backScreen(nullptr)
		, depthBuffer(nullptr)
		, albedoBuffer(nullptr)
		, normalBuffer(nullptr)
		, worldPosBuffer(nullptr)

		, factory(nullptr)

		, bloom(nullptr)
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
		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // D3D Debug Mode 설정
		// 디버그 모드에서는 런타임 때 들어오는 파라미터를 검증한다.
#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,	// GPU 사용
			D3D_DRIVER_TYPE_WARP,		// GPU는 없지만 CPU가 SIMD같은 기능을 지원하는 경우 (병렬 처리)
			D3D_DRIVER_TYPE_REFERENCE	// 100% 소프트웨어 디바이스, GPU 없어도 사용가능
		};

		UINT driverTypesSize = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,		// 최우선적으로 하드웨어에서 지원되길 바라는 기능 수준
			D3D_FEATURE_LEVEL_11_0,		// 위가 안된다면 이것
			D3D_FEATURE_LEVEL_10_1,		// ...
			D3D_FEATURE_LEVEL_10_0
		};

		UINT featureLevelsSize = ARRAYSIZE(featureLevels);

		// 더블 버퍼링 == 스왑 체인
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;						// 길이
		sd.BufferDesc.Height = height;						// 높이
		sd.BufferDesc.Format = backBufferFormat;	// 색상 포맷
		sd.BufferDesc.RefreshRate.Numerator = 0;			// 프레임 분자
		sd.BufferDesc.RefreshRate.Denominator = 1;			// 프레임 분모, 1초에 60프레임
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = true;	// 창모드 여부

		for (UINT i = 0; i < driverTypesSize; i++)
		{
			// 지원되는 Driver와 FeatureLevel을 확인하여 D3D 객체들을 생성한다.
			driverType = driverTypes[i];

			// Helper 함수, Device 생성 과정과 SwapChain 생성 과정을 분리해서 사용할 수 있음.
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

		depthBuffer = new RenderTexture(backBufferFormat);
		depthBuffer->SetDevice(d3dDevice);

		albedoBuffer = new RenderTexture(backBufferFormat);
		albedoBuffer->SetDevice(d3dDevice);

		normalBuffer = new RenderTexture(backBufferFormat);
		normalBuffer->SetDevice(d3dDevice);

		worldPosBuffer = new RenderTexture(backBufferFormat);
		worldPosBuffer->SetDevice(d3dDevice);

		if (OnResize(width, height) != true)
			return false;

		// Blend state
		D3D11_BLEND_DESC descBlend = {};
		ZeroMemory(&descBlend, sizeof(D3D11_BLEND_DESC));

		descBlend.RenderTarget[0].BlendEnable = true;
		descBlend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_GREEN | D3D11_COLOR_WRITE_ENABLE_BLUE;
		descBlend.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descBlend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		descBlend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descBlend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descBlend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		descBlend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		hr = d3dDevice->CreateBlendState(&descBlend, &blendState);
		if (FAILED(hr))
			return false;

		deviceContext->QueryInterface<ID3DUserDefinedAnnotation>(&annotation);

		// Factory
		factory = new Factory(d3dDevice, deviceContext);

		// Sprite
		spriteBatch = new DirectX::SpriteBatch(deviceContext);
		spriteFont = new DirectX::SpriteFont(d3dDevice, _T("Font/gulim9k.spritefont"));
		spriteFont->SetLineSpacing(14.0f);

		effect2D = new Effect2D(deviceContext);
		effect2D->Init(factory);

		// Post Process
		bloom = new Bloom(deviceContext);
		bloom->Init(factory, d3dDevice, backBufferFormat, spriteBatch);

		blur = new Blur(deviceContext);
		blur->Init(factory, d3dDevice, backBufferFormat, spriteBatch);

		downSampler = new DownSampling(deviceContext);
		downSampler->Init(factory, d3dDevice, backBufferFormat, spriteBatch);

		combine = new Combine(deviceContext);
		combine->Init(factory, d3dDevice, backBufferFormat, spriteBatch);

		return true;
	}

	FactoryBase* const DirectX11::CreateFactory()
	{
		return new Factory(d3dDevice, deviceContext);
	}

	bool DirectX11::OnResize(UINT width, UINT height)
	{
		if (d3dDevice == nullptr)
			return false;

		HRESULT hr = S_OK;

		// Resize하기전에 버퍼를 초기화하라는 오류가 뜬다. 그래서 초기화
		RELEASE_PTR(renderTarget);
		RELEASE_PTR(renderTargetView);
		RELEASE_PTR(depth);
		RELEASE_PTR(depthView);
		RELEASE_PTR(depthState);
		RELEASE_PTR(blendState);

		// 이하 리사이즈만 제외하고 생성 과정과 같음
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
		descDSS.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

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

		// 그려질 화면의 영역 결정
		viewPort.Width = static_cast<FLOAT>(width);
		viewPort.Height = static_cast<FLOAT>(height);
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		// RS == Rasterizer Stage
		deviceContext->RSSetViewports(1, &viewPort);

		backScreen->OnResize(width, height);
		depthBuffer->OnResize(width, height);
		albedoBuffer->OnResize(width, height);
		normalBuffer->OnResize(width, height);
		worldPosBuffer->OnResize(width, height);

		return true;
	}

	bool DirectX11::DrawSprite(Texture* texture, long posX, long posY, long width, long height, float z)
	{
		return DrawSprite(reinterpret_cast<ID3D11ShaderResourceView*>(texture), RECT{ posX, posY, posX + width, posY + height }, nullptr, z);
	}

	bool DirectX11::DrawSprite(Texture* texture, const HeraclesMath::Rect& dest, const HeraclesMath::Rect& src, float z)
	{
		RECT dxDest = { dest.left, dest.top, dest.right, dest.bottom };
		RECT dxSrc = { src.left, src.top, src.right, src.bottom };

		return DrawSprite(reinterpret_cast<ID3D11ShaderResourceView*>(texture), dxDest, &dxSrc,	z);
	}

	bool DirectX11::DrawSprite(ID3D11ShaderResourceView* texture, RECT dest, RECT* src, float z)
	{
		spriteBatch->Begin(DirectX::SpriteSortMode_Texture, blendState, nullptr, depthState);
		spriteBatch->Draw(texture, dest, src, DirectX::Colors::White, 0.0f, { 0.0f, 0.0f }, DirectX::SpriteEffects_None, z);
		spriteBatch->End();

		return true;
	}

	bool DirectX11::DrawSpriteOn3D(Texture* texture, HeraclesMath::Vector worldPosition[3], const HeraclesMath::Matrix& viewProjection)
	{
		if (effect2D == nullptr)
			return false;

		DirectX::XMVECTOR worldPos[3] =
		{
			{ worldPosition[0][0], worldPosition[0][1], worldPosition[0][2], worldPosition[0][3] },
			{ worldPosition[1][0], worldPosition[1][1], worldPosition[1][2], worldPosition[1][3] },
			{ worldPosition[2][0], worldPosition[2][1], worldPosition[2][2], worldPosition[2][3] }
		};

		DirectX::XMVECTOR texCoord[3] =
		{
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 0.0f, 1.0f }
		};

		DirectX::XMMATRIX viewProj;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				viewProj.r[i].m128_f32[j] = viewProjection[i][j];
			}
		}
		
		deviceContext->OMSetBlendState(blendState, nullptr, 0xff);

		effect2D->Draw(reinterpret_cast<ID3D11ShaderResourceView*>(texture), worldPos, texCoord, &viewProj);

		return true;
	}

	bool DirectX11::DrawSpriteOn3D(Texture* texture, long width, long height, const HeraclesMath::Matrix& worldViewProjection)
	{
		if (effect2D == nullptr)
			return false;

		DirectX::XMVECTOR worldPos[3];

		DirectX::XMVECTOR texCoord[3] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f } };

		for (int i = 0; i < 3; i++)
			worldPos[i] = { width / 2.0f, height / 2.0f, 0.0f, 1.0f	};

		worldPos[1].m128_f32[0] -= width;
		worldPos[2].m128_f32[1] -= height;

		DirectX::XMMATRIX transformMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				transformMatrix.r[i].m128_f32[j] = worldViewProjection[i][j];
		}

		deviceContext->OMSetBlendState(blendState, nullptr, 0xff);

		effect2D->Draw(reinterpret_cast<ID3D11ShaderResourceView*>(texture), worldPos, texCoord, &transformMatrix);

		return true;
	}

	bool DirectX11::DrawSpriteOn3D(Texture* texture, long width, long height, const HeraclesMath::Matrix& worldViewProjection, const HeraclesMath::Vector texCoord[3])
	{
		if (effect2D == nullptr)
			return false;

		DirectX::XMVECTOR worldPos[3];

		DirectX::XMVECTOR xmTexCoord[3] = { { texCoord[0].x, texCoord[0].y }, { texCoord[1].x, texCoord[1].y }, { texCoord[2].x, texCoord[2].y } };

		for (int i = 0; i < 3; i++)
			worldPos[i] = { width / 2.0f, height / 2.0f, 0.0f, 1.0f };

		worldPos[1].m128_f32[0] -= width;
		worldPos[2].m128_f32[1] -= height;

		DirectX::XMMATRIX transformMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				transformMatrix.r[i].m128_f32[j] = worldViewProjection[i][j];
		}

		deviceContext->OMSetBlendState(blendState, nullptr, 0xff);

		effect2D->Draw(reinterpret_cast<ID3D11ShaderResourceView*>(texture), worldPos, xmTexCoord, &transformMatrix);

		return true;
	}

	bool DirectX11::DrawMesh(BufferBase* vertices, BufferBase* indices)
	{
		VertexBuffer* vb = dynamic_cast<VertexBuffer*>(vertices);

		if (vb == nullptr)
			return false;

		IndexBuffer* ib = dynamic_cast<IndexBuffer*>(indices);

		if (ib == nullptr)
			return false;

		vb->SetUpBuffer(0, nullptr, ShaderType::NONE);
		ib->SetUpBuffer(0, nullptr, ShaderType::NONE);

		UINT indicesSize = ib->GetSize();

		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		deviceContext->DrawIndexed(indicesSize, 0, 0);

		return true;
	}

	bool DirectX11::DrawTextColor(std::string& text, HeraclesMath::Vector color, HeraclesMath::Vector position, float rotation, HeraclesMath::Vector scale)
	{
		if (spriteBatch == nullptr || spriteFont == nullptr)
			return false;

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, depthState);
		spriteFont->DrawString(spriteBatch, text.c_str(), DirectX::XMVECTOR{ position.x, position.y }, DirectX::XMVECTOR{ color.x, color.y, color.z }, HeraclesMath::ConvertDegreeToRadian(rotation), DirectX::g_XMZero, DirectX::XMVECTOR{ scale.x, scale.y }, DirectX::SpriteEffects_None, position.z);
		spriteBatch->End();

		return true;
	}

	bool DirectX11::DrawLine(BufferBase* vertices, BufferBase* indices)
	{
		VertexBuffer* vb = dynamic_cast<VertexBuffer*>(vertices);

		if (vb == nullptr)
			return false;

		IndexBuffer* ib = dynamic_cast<IndexBuffer*>(indices);

		if (ib == nullptr)
			return false;

		vb->SetUpBuffer(0, nullptr, ShaderType::NONE);
		ib->SetUpBuffer(0, nullptr, ShaderType::NONE);

		UINT indicesSize = ib->GetSize();

		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		deviceContext->DrawIndexed(indicesSize, 0, 0);

		return true;
	}

	bool DirectX11::SetUpShader(ShaderBase* shader)
	{
		shader->SetUpShader();

		return true;
	}

	bool DirectX11::GraphicsDebugBeginEvent(const std::string& name)
	{
		if (annotation == nullptr)
			return false;

		std::wstring wstr;

		wstr.assign(name.begin(), name.end());

		annotation->BeginEvent(wstr.c_str());

		annotationCount++;

		return true;
	}

	bool DirectX11::GraphicsDebugEndEvent()
	{
		if (annotation == nullptr || annotationCount <= 0)
			return false;

		annotation->EndEvent();
		annotationCount--;

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

		deviceContext->ClearDepthStencilView(depthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		backScreen->ClearRenderTargetView(deviceContext, depthView, DirectX::Colors::Black);
		depthBuffer->ClearRenderTargetView(deviceContext, depthView, DirectX::Colors::Black);
		albedoBuffer->ClearRenderTargetView(deviceContext, depthView, DirectX::Colors::Black);
		normalBuffer->ClearRenderTargetView(deviceContext, depthView, DirectX::Colors::Black);
		worldPosBuffer->ClearRenderTargetView(deviceContext, depthView, DirectX::Colors::Black);
		deviceContext->OMSetRenderTargets(1, &renderTargetView, depthView);
		deviceContext->ClearRenderTargetView(renderTargetView, DirectX::Colors::Black);
		deviceContext->OMSetDepthStencilState(depthState, 0);

		ID3D11RenderTargetView* mrt[] =
		{
			backScreen->GetRenderTargetView(),
			depthBuffer->GetRenderTargetView(),
			albedoBuffer->GetRenderTargetView(),
			normalBuffer->GetRenderTargetView(),
			worldPosBuffer->GetRenderTargetView()
		};

		deviceContext->OMSetRenderTargets(ARRAYSIZE(mrt), mrt, depthView);

		annotation->EndEvent();
	}

	void DirectX11::Render()
	{
		annotation->BeginEvent(_T("Render"));

		annotation->EndEvent();
	}

	void DirectX11::PostProcess()
	{
		annotation->BeginEvent(_T("Post Process"));

		//downSampler->OnResize(backScreen->GetWidth() / 2, backScreen->GetHeight());

		//auto downSRV = (*downSampler)(backScreen->GetShaderResourceView());

		//(*blur)(downSampler->GetRenderTexture(), 4.0f);
		//(*combine)(backScreen, downSRV);
		//(*blur)(backScreen, 4.0f);

		annotation->BeginEvent(_T("Bloom"));

		(*bloom)(backScreen);

		annotation->EndEvent();

		backScreen->OMSetRenderTarget(deviceContext, depthView);

		annotation->EndEvent();
	}

	void DirectX11::EndRender()
	{
		annotation->BeginEvent(_T("Present"));

		backScreen->OMSetRenderTarget(deviceContext, depthView);

		ID3D11ShaderResourceView* null[] = { nullptr };

		auto depthSRV = depthBuffer->GetShaderResourceView();

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, depthState);
		spriteBatch->Draw(depthSRV, RECT{ static_cast<long>(viewPort.Width * 0.8f), 0, static_cast<long>(viewPort.Width), static_cast<long>(viewPort.Height * 0.25f )});
		spriteBatch->End();

		auto albedoSRV = albedoBuffer->GetShaderResourceView();

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, depthState);
		spriteBatch->Draw(albedoSRV, RECT{ static_cast<long>(viewPort.Width * 0.8f), static_cast<long>(viewPort.Height * 0.25f), static_cast<long>(viewPort.Width), static_cast<long>(viewPort.Height * 0.5f )});
		spriteBatch->End();

		auto normalSRV = normalBuffer->GetShaderResourceView();

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, depthState);
		spriteBatch->Draw(normalSRV, RECT{ static_cast<long>(viewPort.Width * 0.8f), static_cast<long>(viewPort.Height * 0.5f), static_cast<long>(viewPort.Width), static_cast<long>(viewPort.Height * 0.75f )});
		spriteBatch->End();

		auto worldPosSRV = worldPosBuffer->GetShaderResourceView();

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, depthState);
		spriteBatch->Draw(worldPosSRV, RECT{ static_cast<long>(viewPort.Width * 0.8f), static_cast<long>(viewPort.Height * 0.75f), static_cast<long>(viewPort.Width), static_cast<long>(viewPort.Height)});
		spriteBatch->End();

		deviceContext->PSSetShaderResources(0, 1, null);

		deviceContext->OMSetRenderTargets(1, &renderTargetView, depthView);
		deviceContext->CopyResource(renderTarget, backScreen->GetRenderTarget());

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
		delete effect2D;

		DELETE_RELEASE_PTR(backScreen);
		DELETE_RELEASE_PTR(depthBuffer);
		DELETE_RELEASE_PTR(albedoBuffer);
		DELETE_RELEASE_PTR(normalBuffer);
		DELETE_RELEASE_PTR(worldPosBuffer);

		delete factory;

		delete bloom;

		delete blur;
		delete downSampler;
		delete combine;
	}

	void DirectX11::DebugRender()
	{
		backScreen->OMSetRenderTarget(deviceContext, depthView);

		ID3D11ShaderResourceView* null[] = { nullptr };

		auto depthSRV = depthBuffer->GetShaderResourceView();

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, depthState);
		spriteBatch->Draw(depthSRV, RECT{ static_cast<long>(viewPort.Width * 0.8f), 0, static_cast<long>(viewPort.Width), static_cast<long>(viewPort.Height * 0.25f) });
		spriteBatch->End();

		auto albedoSRV = albedoBuffer->GetShaderResourceView();

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, depthState);
		spriteBatch->Draw(albedoSRV, RECT{ static_cast<long>(viewPort.Width * 0.8f), static_cast<long>(viewPort.Height * 0.25f), static_cast<long>(viewPort.Width), static_cast<long>(viewPort.Height * 0.5f) });
		spriteBatch->End();

		auto normalSRV = normalBuffer->GetShaderResourceView();

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, depthState);
		spriteBatch->Draw(normalSRV, RECT{ static_cast<long>(viewPort.Width * 0.8f), static_cast<long>(viewPort.Height * 0.5f), static_cast<long>(viewPort.Width), static_cast<long>(viewPort.Height * 0.75f) });
		spriteBatch->End();

		auto worldPosSRV = worldPosBuffer->GetShaderResourceView();

		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, depthState);
		spriteBatch->Draw(worldPosSRV, RECT{ static_cast<long>(viewPort.Width * 0.8f), static_cast<long>(viewPort.Height * 0.75f), static_cast<long>(viewPort.Width), static_cast<long>(viewPort.Height) });
		spriteBatch->End();

		deviceContext->PSSetShaderResources(0, 1, null);
	}

	DirectX11DeclSpec DirectX11* CreateDirectX11()
	{
		return new DirectX11;
	}
}