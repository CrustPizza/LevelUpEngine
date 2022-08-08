/********************************
*								*
*	Game Engine.h				*
*								*
*	Created : 2022/06/11		*
*	Updated : 2022/07/26		*
*********************************/

#pragma once
#include "../GraphicsEngine/GraphicsEngineFramework.h"
#include "Application/Application.h"
#include "Factory/Factory.h"
#include "Camera/Camera.h"
#include "Object/Cube/Cube.h"
#include "Object/Genji/Genji.h"
#include "Object/Pig/Pig.h"

namespace GameEngineSpace
{
#ifdef GameEngine_Export
#define GameEngineDeclSpec __declspec( dllexport )
#else
#define GameEngineDeclSpec __declspec( dllimport )
#endif

	using GraphicsEngineSpace::GraphicsEngine;

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

		// Factory
		Factory* factory;
		GraphicsEngineSpace::Factory* graphicsFactory;

		// Manager
		SceneManager*	sceneManager;
		Input*			inputManager;

		// Camera
		Camera camera;

		// Test
		Cube* cube;
		Cube* pbrCube;
		Genji* genji;
		Genji* pbrGenji;
		Pig* pig;
		Pig* pigs[10];

		GraphicsEngineSpace::DirectionalLight* dLight;
		GraphicsEngineSpace::PointLight* pLight;
		
		GraphicsEngineSpace::SkyBoxBase* skyBox;
		GraphicsEngineSpace::IBLTexture* ibl;

	public:
		GameEngine();
		virtual ~GameEngine();

		virtual bool CreateEngine(EngineType engineType, HINSTANCE hInstance, RECT wndSize);
		virtual Factory* const CreateFactory();
		virtual int Run();

		virtual bool SetEntryScene(std::string name);

	private:
		void Init();
		void Update();
		void Render();
		void Release();
	};

	extern "C"
	{
		GameEngineDeclSpec GameEngine* CreateGameEngine();
		using GameEngineConstructor = GameEngine * (*)(void);
	}
}