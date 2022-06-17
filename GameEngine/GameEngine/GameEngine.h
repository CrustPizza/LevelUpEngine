/********************************
*								*
*	Game Engine.h				*
*								*
*	Created : 2022/06/11		*
*	Updated : 2022/06/15		*
*********************************/

#pragma once
#include "../../GraphicsEngine/GraphicsEngineFramework.h"
#include "../Application/Application.h"

#ifdef GameEngine_Export
#define GameEngineDeclSpec __declspec( dllexport )
#else
#define GameEngineDeclSpec __declspec( dllimport )
#endif

class GameEngineDeclSpec GameEngine
{
public:
	enum class EngineType
	{
		DirectX
	};

private:
	// Screen
	Application* app;

	// Renderer
	GraphicsEngine* graphicsEngine;
	HMODULE graphicsDLL;

public:
	GameEngine();
	virtual ~GameEngine();

	virtual bool CreateEngine(EngineType engineType, HINSTANCE hInstance, RECT wndSize);
	virtual int Run();
};

extern "C"
{
	GameEngineDeclSpec GameEngine* CreateGameEngine();
	using GameEngineConstructor = GameEngine*(*)(void);
}