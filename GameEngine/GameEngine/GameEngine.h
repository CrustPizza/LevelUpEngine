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
#include "Object/Pillar/Pillar.h"
#include "Object/Mannequin/Mannequin.h"
#include "Object/Ely/Ely.h"
#include "Object/Heracles/Heracles.h"

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
		Cube* pbrCube;
		Genji* genji;
		Genji* pbrGenji;
		Pig* pig;
		Pig* pigs[10];

		Heracles* heracles;

		GraphicsEngineSpace::DirectionalLight* dLight;

		Cube* cubes[10];
		GraphicsEngineSpace::PointLight* pLight[10];
		
		GraphicsEngineSpace::SkyBoxBase* skyBox;
		GraphicsEngineSpace::IBLTexture* ibl;
		GraphicsEngineSpace::Canvas* canvas;
		GraphicsEngineSpace::SpriteAnimation* spriteAnim;
		GraphicsEngineSpace::SpriteAnimation* spriteAnim1;
		GraphicsEngineSpace::SpriteAnimation* spriteAnim2;
		GraphicsEngineSpace::SpriteAnimation* spriteAnim3;
		GraphicsEngineSpace::SpriteAnimation* spriteAnim4;
		GraphicsEngineSpace::SpriteAnimation* spriteAnim5;
		GraphicsEngineSpace::SpriteAnimation* spriteAnim6;
		GraphicsEngineSpace::SpriteAnimation* spriteAnim7;
		GraphicsEngineSpace::SpriteAnimation* spriteAnim8;

		Pillar* pillar;
		Mannequin* mannequin;
		Ely* ely;

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