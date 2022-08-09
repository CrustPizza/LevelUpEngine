/********************************
*								*
*	DirectX11.h					*
*								*
*	Created : 2022/06/11		*
*	Updated : 2022/07/25		*
*********************************/

#pragma once

#include "../GraphicsEngine/Bases/GraphicsEngineBase.h"
#include "DXObject/RenderTexture/RenderTexture.h"
#include "DXObject/D3DTexture/D3DTexture.h"
#include "Inc/SpriteBatch.h"
#include "Inc/SpriteFont.h"
#include "Factory/Factory.h"

#include "DXObject/Effect2D/Effect2D.h"

#include "PostProcess/Blur/Blur.h"
#include "PostProcess/Bloom/Bloom.h"
#include "PostProcess/Combine/Combine.h"
#include "PostProcess/DownSampling/DownSampling.h"

namespace DX11
{
#ifdef DirectX11_Export
#define DirectX11DeclSpec __declspec( dllexport )
#else
#define DirectX11DeclSpec __declspec( dllimport )
#endif

	using GraphicsEngineSpace::GraphicsEngineBase;
	using GraphicsEngineSpace::MeshBase;

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
		unsigned int				annotationCount;

		// Render Object
		ID3D11Texture2D*		renderTarget;
		ID3D11RenderTargetView*	renderTargetView;

		ID3D11Texture2D*		depth;			// 뎁스 텍스쳐
		ID3D11DepthStencilView*	depthView;		// 뎁스 뷰

		ID3D11BlendState*			blendState;
		ID3D11DepthStencilState*	depthState;

		D3D11_VIEWPORT viewPort;

		// Sprite
		DirectX::SpriteBatch*	spriteBatch;
		DirectX::SpriteFont*	spriteFont;
		Effect2D*				effect2D;

		// Properties
		DXGI_FORMAT			backBufferFormat;
		DXGI_FORMAT			depthBufferFormat;
		D3D_DRIVER_TYPE		driverType;			// GPU 지원 타입
		D3D_FEATURE_LEVEL	featureLevel;		// DirectX 버전 지원 수준

		// Back
		RenderTexture* backScreen;

		// Factory
		Factory* factory;

		// Post Process
		Bloom*			bloom;

		// Test
		Blur* blur;
		DownSampling* downSampler;
		Combine* combine;

	public:
		DirectX11();
		~DirectX11();

		virtual bool InitDevice(HWND hWnd, UINT width, UINT height);

		virtual FactoryBase* const CreateFactory() override;
		virtual bool OnResize(UINT width, UINT height) override;

		bool DrawSprite(Texture* texture, long posX, long posY, long width, long height, float z) override;
		bool DrawSprite(ID3D11ShaderResourceView* texture, long posX, long posY, long width, long height, float z);
		bool DrawSpriteOn3D(Texture* texture, HeraclesMath::Vector worldPosition[3], const HeraclesMath::Matrix& viewProjection) override;
		bool DrawSpriteOn3D(Texture* texture, long width, long height, const HeraclesMath::Matrix& worldViewProjection) override;
		bool DrawSpriteOn3D(Texture* texture, long width, long height, const HeraclesMath::Matrix& worldViewProjection, const HeraclesMath::Vector texCoord[3]) override;


		bool DrawMesh(BufferBase* vertices, BufferBase* indices) override;
		bool DrawTextColor(std::string& text, HeraclesMath::Vector color, HeraclesMath::Vector position, float rotation, HeraclesMath::Vector scale) override;

		bool SetUpShader(ShaderBase* shader) override;

		bool GraphicsDebugBeginEvent(const std::string& name) override;
		bool GraphicsDebugEndEvent() override;

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
		using DirectX11Constructor = DirectX11* (*)(void);
	}
}