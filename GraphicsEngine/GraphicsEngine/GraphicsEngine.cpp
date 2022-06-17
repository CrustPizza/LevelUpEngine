/********************************
*								*
*	Graphics Engine.cpp			*
*								*
*	Created : 2022/06/15		*
*	Updated : 2022/06/17		*
*********************************/

#include "GraphicsEngine.h"
#include "../../DirectX11/DirectX11Framework.h"

namespace GraphicsEngineSpace
{
	GraphicsEngine::GraphicsEngine()
		: graphicsDLL(nullptr)
		, graphicsEngine(nullptr)
	{

	}

	GraphicsEngine::~GraphicsEngine()
	{

	}

	bool GraphicsEngine::CreateDirectXEngine(HWND hWnd, UINT width, UINT height)
	{
#ifdef x64
#ifdef _DEBUG
		graphicsDLL = LoadLibrary(_T("DLL/DirectX11_Debug_x64.dll"));
#else
		graphicsDLL = LoadLibrary(_T("DLL/DirectX11_Release_x64.dll"));
#endif
#else
#ifdef _DEBUG
		graphicsDLL = LoadLibrary(_T("DLL/DirectX11_Debug_x86.dll"));
#else
		graphicsDLL = LoadLibrary(_T("DLL/DirectX11_Release_x86.dll"));
#endif
#endif

		if (graphicsDLL == nullptr)
		{
			// TO DO
			// DLL 로드 실패
			OutputDebugString(_T("Load DirectX11 dll failed.\n"));
			return false;
		}

		OutputDebugString(_T("Load DirectX11 dll success.\n"));

		using DX11::DirectX11Constructor;

		DirectX11Constructor dx11Constructor = (DirectX11Constructor)GetProcAddress(graphicsDLL, "CreateDirectX11");
		DX11::DirectX11* dxEngine = dx11Constructor();

		if (dxEngine->InitDevice(hWnd, width, height) != true)
		{
			// TO DO

			OutputDebugString(_T("Init DirectX11 failed.\n"));
			return false;
		}

		graphicsEngine = dxEngine;

		return true;
	}

	bool GraphicsEngine::OnResize(UINT width, UINT height)
	{
		return graphicsEngine->OnResize(width, height);
	}

	void GraphicsEngine::BeginRender()
	{
		graphicsEngine->BeginRender();
	}

	void GraphicsEngine::Render()
	{
		graphicsEngine->Render();
	}

	void GraphicsEngine::PostProcess()
	{
		graphicsEngine->PostProcess();
	}

	void GraphicsEngine::EndRender()
	{
		graphicsEngine->EndRender();
	}

	void GraphicsEngine::Release()
	{
		if (graphicsEngine != nullptr)
		{
			graphicsEngine->Release();
			delete graphicsEngine;
		}

		if (graphicsDLL != nullptr)
			FreeLibrary(graphicsDLL);
	}

	GraphicsEngineDeclSpec GraphicsEngine* CreateGraphicsEngine()
	{
		return new GraphicsEngine;
	}
}