/********************************
*								*
*	Game Engine.cpp				*
*								*
*	Created : 2022/06/11		*
*	Updated : 2022/06/15		*
*********************************/

#include "GameEngine.h"

GameEngine::GameEngine()
	: app(nullptr)
	, graphicsEngine(nullptr)
	, graphicsDLL(nullptr)
{
	
}

GameEngine::~GameEngine()
{
	delete app;
	delete graphicsEngine;
	if (graphicsDLL != nullptr)
		FreeLibrary(graphicsDLL);
}

bool GameEngine::CreateEngine(EngineType engineType, HINSTANCE hInstance, RECT wndSize)
{
	switch (engineType)
	{

	case EngineType::DirectX:
	{
		app = new Application;

		if (app == nullptr)
			return false;

		if (app->CreateApp(hInstance, wndSize) != true)
			return false;
#ifdef x64
#ifdef _DEBUG
		graphicsDLL = LoadLibrary(_T("DLL/GraphicsEngine_Debug_x64.dll"));
#else
		graphicsDLL = LoadLibrary(_T("DLL/GraphicsEngine_Release_x64.dll"));
#endif
#else
#ifdef _DEBUG
		graphicsDLL = LoadLibrary(_T("DLL/GraphicsEngine_Debug_x86.dll"));
#else
		graphicsDLL = LoadLibrary(_T("DLL/GraphicsEngine_Release_x86.dll"));
#endif
#endif

		if (graphicsDLL == nullptr)
		{
			// TO DO
			// DLL 로드 실패
			OutputDebugString(_T("Load graphics engine dll failed.\n"));
			return false;
		}

		OutputDebugString(_T("Load graphics engine dll success.\n"));

		GraphicsEngineConstructor graphicsConstructor = (GraphicsEngineConstructor)GetProcAddress(graphicsDLL, "CreateGraphicsEngine");
		graphicsEngine = graphicsConstructor();

		if (graphicsEngine->CreateDirectXEngine(app->GetWndHandle(), app->GetWidth(), app->GetHeight()) != true)
		{
			// TO DO

			OutputDebugString(_T("Create DirectX dll failed.\n"));
			return false;
		}

		app->SetOnResizeFunc([&](UINT width, UINT height)
			{
				graphicsEngine->OnResize(width, height);
			});

		return true;
	}

	}

	return false;
}

int GameEngine::Run()
{
	if (graphicsEngine == nullptr)
		return -1;

	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			graphicsEngine->BeginRender();
			graphicsEngine->Render();
			graphicsEngine->PostProcess();
			graphicsEngine->EndRender();
		}
	}

	graphicsEngine->Release();

	return static_cast<int>(msg.lParam);
}

GameEngineDeclSpec GameEngine* CreateGameEngine()
{
	return new GameEngine;
}