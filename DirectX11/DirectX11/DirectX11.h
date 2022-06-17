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
/// DirectX11 �׷��Ƚ� ����
/// �߻�ȭ�� GraphicsEngineBase�� ��� �޾Ƽ�
/// �������� �ʿ��� �κ� ��ü�� ����
/// 
/// 2022. 06. 17
/// </summary>
class DirectX11DeclSpec DirectX11 : public GraphicsEngineBase
{
private:
	// DirectX ���� ����

	// D3D Object
	ID3D11Device*				d3dDevice;		// ��ü (����, ���� ��� ��)
	ID3D11DeviceContext*		deviceContext;	// �帧 (�׸���, ���º�ȯ ��)
	IDXGISwapChain*				swapChain;		// ��ũ�� ����
	ID3DUserDefinedAnnotation*	annotation;		// �׷��� ����� ����

	// Render Object
	ID3D11Texture2D*			renderTarget;
	ID3D11RenderTargetView*		renderTargetView;

	ID3D11Texture2D*			depth;			// ���� �ؽ���
	ID3D11DepthStencilView*		depthView;		// ���� ��

	ID3D11BlendState*			blendState;
	ID3D11DepthStencilState*	depthState;

	D3D11_VIEWPORT				viewPort;

	// Sprite
	DirectX::SpriteBatch*	spriteBatch;
	DirectX::SpriteFont*	spriteFont;

	// Properties
	DXGI_FORMAT			backBufferFormat;
	DXGI_FORMAT			depthBufferFormat;	
	D3D_DRIVER_TYPE		driverType;			// GPU ���� Ÿ��
	D3D_FEATURE_LEVEL	featureLevel;		// DirectX ���� ���� ����

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