/********************************
*								*
*	DirectX11.h					*
*								*
*	Created : 2022/06/11		*
*	Updated : 2022/06/17		*
*********************************/

#pragma once

#include "../../GraphicsEngine/GraphicsEngine/EngineBase/GraphicsEngineBase.h"
#include "../RenderTexture/RenderTexture.h"
#include "../Inc/SpriteBatch.h"
#include "../Inc/SpriteFont.h"

#ifdef DirectX11_Export
#define DirectX11DeclSpec __declspec( dllexport )
#else
#define DirectX11DeclSpec __declspec( dllimport )
#endif

/// <summary>
/// DirectX11 그래픽스 엔진
/// 추상화된 GraphicsEngineBase를 상속 받아서
/// 랜더링에 필요한 부분 전체를 구현
/// 
/// 2022. 06. 17
/// </summary>
class DirectX11DeclSpec DirectX11 : public GraphicsEngineBase
{
private:
	// DirectX 관련 변수

	// D3D Object
	ID3D11Device*				d3dDevice;		// 몸체 (생성, 제거 기능 등)
	ID3D11DeviceContext*		deviceContext;	// 흐름 (그리기, 상태변환 등)
	IDXGISwapChain*				swapChain;		// 스크린 버퍼
	ID3DUserDefinedAnnotation*	annotation;		// 그래픽 디버그 헬퍼

	// Render Object
	ID3D11Texture2D*			renderTarget;
	ID3D11RenderTargetView*		renderTargetView;

	ID3D11Texture2D*			depth;			// 뎁스 텍스쳐
	ID3D11DepthStencilView*		depthView;		// 뎁스 뷰

	ID3D11BlendState*			blendState;
	ID3D11DepthStencilState*	depthState;

	D3D11_VIEWPORT				viewPort;

	// Sprite
	DirectX::SpriteBatch*	spriteBatch;
	DirectX::SpriteFont*	spriteFont;

	// Properties
	DXGI_FORMAT			backBufferFormat;
	DXGI_FORMAT			depthBufferFormat;	
	D3D_DRIVER_TYPE		driverType;			// GPU 지원 타입
	D3D_FEATURE_LEVEL	featureLevel;		// DirectX 버전 지원 수준

	// MRT
	RenderTexture* backScreen;
	RenderTexture* rt1;
	RenderTexture* rt2;
	RenderTexture* rt3;

public:
	DirectX11();
	~DirectX11();

	virtual bool InitDevice(HWND hWnd, UINT width, UINT height);
	virtual bool OnResize(UINT width, UINT height);

private:
	bool CreateBackScreen();

public:
	void BeginRender()	override;
	void Render()		override;
	void PostProcess()	override;
	void EndRender()	override;
	void Release()		override;
};

extern "C"
{
	DirectX11DeclSpec DirectX11* CreateDirectX11();
	using DirectX11Constructor = DirectX11*(*)(void);
}