/********************************
*								*
*	WinMain.cpp					*
*								*
*	Created : 2022/06/10		*
*	Updated : 2022/06/14		*
*********************************/

#include "../GameEngine/GameEngineFramework.h"
#include <crtdbg.h>

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPTSTR cmdLine, int cmdShowOpt)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#ifdef x64
#ifdef _DEBUG
	HMODULE hDll = LoadLibrary(_T("DLL/GameEngine_Debug_x64.dll"));
#else
	HMODULE hDll = LoadLibrary(_T("DLL/GameEngine_Release_x64.dll"));
#endif
#else
#ifdef _DEBUG
	HMODULE hDll = LoadLibrary(_T("DLL/GameEngine_Debug_x86.dll"));
#else
	HMODULE hDll = LoadLibrary(_T("DLL/GameEngine_Release_x86.dll"));
#endif
#endif

	if (hDll == nullptr)
	{
		// TO DO
		// DLL 로드 실패
		OutputDebugString(_T("Load game engine dll failed.\n"));
		return -1;
	}

	OutputDebugString(_T("Load game engine dll success.\n"));

	using GameEngineSpace::GameEngineConstructor;

	GameEngineConstructor gameConstructor = (GameEngineConstructor)GetProcAddress(hDll, "CreateGameEngine");
	GameEngineSpace::GameEngine* gameEngine = gameConstructor();

	gameEngine->CreateEngine(GameEngineSpace::GameEngine::EngineType::DirectX, hInstance, { 0, 0, 1600, 900 });

	gameEngine->Run();

	delete gameEngine;

	FreeLibrary(hDll);

	return 0;
}