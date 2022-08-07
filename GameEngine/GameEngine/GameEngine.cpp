/********************************
*								*
*	Game Engine.cpp				*
*								*
*	Created : 2022/06/11		*
*	Updated : 2022/07/20		*
*********************************/

#include "GameEngine.h"
#include "Manager/Time/Time.h"

namespace GameEngineSpace
{
	GameEngine::GameEngine()
		: app(nullptr)
		, graphicsEngine(nullptr)
		, graphicsDLL(nullptr)
		, factory(nullptr)
		, graphicsFactory(nullptr)
		, sceneManager(SceneManager::GetInstance())
		, inputManager(Input::GetInstance())
	{

	}

	GameEngine::~GameEngine()
	{
		delete app;
		delete graphicsEngine;
		delete factory;
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

			using GraphicsEngineSpace::GraphicsEngineConstructor;

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
					camera.UpdateProjectionMatrix(width, height);
				});

			app->SetOnMouseMove([&](float x, float y)
				{
					Input::GetInstance()->SetMousePos(x, y);
				});

			return true;
		}

		}

		return false;
	}

	Factory* const GameEngine::CreateFactory()
	{
		if (factory != nullptr)
			return factory;

		factory = new Factory;
		factory->sceneManager = sceneManager;
		factory->inputManager = inputManager;

		return factory;
	}

	int GameEngine::Run()
	{
		if (graphicsEngine == nullptr)
			return -1;

		MSG msg = {};

		Init();

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				Update();
				Render();
			}
		}

		Release();

		return static_cast<int>(msg.lParam);
	}

	bool GameEngine::SetEntryScene(std::string name)
	{
		return sceneManager->ChangeScene(name);
	}

	void GameEngine::Init()
	{
		using namespace GraphicsEngineSpace;

		graphicsFactory = graphicsEngine->CreateFactory();

		camera.UpdateProjectionMatrix(app->GetWidth(), app->GetHeight());
		camera.UpdateViewMatrix();

		GraphicsEngineSpace::ResourceManager* resourceManager = graphicsEngine->GetResourceManager();

		ShaderBase* vertexShader = resourceManager->GetShader("BasicModelVS");
		ShaderBase* pixelShader = resourceManager->GetShader("BasicModelPS");
		BufferBase* matrixBuffer = resourceManager->GetBuffer("MatrixCB");

		ModelBase* cubeModel = graphicsFactory->CreateModelFromASEFile("ASECube", "Resources/Model/Cube.ase");

		cube = new Cube;
		cube->Init(graphicsFactory, cubeModel, vertexShader, pixelShader, matrixBuffer);

		pbrCube = new Cube;
		pbrCube->Init(graphicsFactory, cubeModel);

		vertexShader = resourceManager->GetShader("LegacyModelVS");
		pixelShader = resourceManager->GetShader("LegacyModelPS");
		BufferBase* materialBuffer = resourceManager->GetBuffer("LegacyMaterialCB");

		ModelBase* genjiModel = graphicsFactory->CreateModelFromASEFile("ASEGenji", "Resources/Model/genji_max.ase");
		
		genji = new Genji;
		//genji->Init(graphicsFactory, genjiModel, vertexShdaer, pixelShader, matrixBuffer, materialBuffer);
		genji->Init(graphicsFactory, genjiModel);

		vertexShader = resourceManager->GetShader("SkinningModelVS");
		BufferBase* boneBuffer = resourceManager->GetBuffer("BoneMatrixCB");

		ModelBase* pigModel = graphicsFactory->CreateModelFromASEFile("ASEPig", "Resources/Model/babypig_idle_6x.ASE", "Idle");
		//ModelBase* pigIdleAnimation = graphicsFactory->CreateAnimationFromASEFile("ASEPig", "Resources/Model/babypig_walk_6x.ASE", "Walk");

		pig = new Pig;
		//pig->Init(graphicsFactory, pigModel, vertexShdaer, pixelShader, matrixBuffer, boneBuffer, materialBuffer);
		pig->Init(graphicsFactory, pigModel);
		pig->AddForce(Vector::UnitY * VectorReplicate(5));

		for (int i = 0; i < 10; i++)
		{
			pigs[i] = new Pig;
			pigs[i]->Init(graphicsFactory, pigModel);
			pigs[i]->AddForce(Vector::UnitX * VectorReplicate(i * 5));
		}

		skyBox = graphicsFactory->CreateSkyBox("SkyBox");
		skyBox->SetTexture(graphicsFactory->CreateTexture("LobbyCubeMap", "Resources/Texture/lobbycube.dds"));

		dLight = new DirectionalLightBase;
		dLight->rotation.x += 45.0f;
		dLight->SetBuffer(resourceManager->GetBuffer("DirectionalLightCB"));

		graphicsFactory->CreateTexture("Bricks", "Resources/Texture/bricks.dds");

		ibl = graphicsFactory->CreateIBLTexture("MSIBL", "Resources/Texture/SunSubMixer_diffuseIBL.dds", "Resources/Texture/SunSubMixer_specularIBL.dds");
	}

	void GameEngine::Update()
	{
		Time::instance.Update();
		inputManager->Update();
		camera.CameraMove(Time::instance.deltaTime);
		camera.CameraRotation();
		//camera.LookAt(pig->GetTransform().position);

		sceneManager->Update();

		cube->Update(Time::instance.deltaTime);
		pbrCube->Update(Time::instance.deltaTime);
		genji->Update(Time::instance.deltaTime);

		static float metallic = 0.5f;

		if (Input::GetInstance()->GetInputState('R', KeyState::STAY) == true)
		{
			metallic += 0.5f * Time::instance.deltaTime;

			if (metallic > 1.0f)
				metallic = 1.0f;

			genji->SetMetallic(metallic);
		}
		else if (Input::GetInstance()->GetInputState('F', KeyState::STAY) == true)
		{
			metallic -= 0.5f * Time::instance.deltaTime;

			if (metallic < 0.0f)
				metallic = 0.0f;

			genji->SetMetallic(metallic);
		}

		static float roughness = 0.5f;

		if (Input::GetInstance()->GetInputState('T', KeyState::STAY) == true)
		{
			roughness += 0.5f * Time::instance.deltaTime;

			if (roughness > 1.0f)
				roughness = 1.0f;

			genji->SetRoughness(roughness);
		}
		else if (Input::GetInstance()->GetInputState('G', KeyState::STAY) == true)
		{
			roughness -= 0.5f * Time::instance.deltaTime;

			if (roughness < 0.0f)
				roughness = 0.0f;

			genji->SetRoughness(roughness);
		}

		if (Input::GetInstance()->GetInputState(VK_RIGHT, KeyState::DOWN) == true)
			pig->AddForce(Vector::UnitX * VectorReplicate(5.0f));
		
		if (Input::GetInstance()->GetInputState(VK_LEFT, KeyState::DOWN) == true)
			pig->AddForce(-Vector::UnitX * VectorReplicate(5.0f));
		
		if (Input::GetInstance()->GetInputState(VK_SPACE, KeyState::TOGGLE) == true)
			pig->Update(0.0f);
		else
			pig->Update(Time::instance.deltaTime);

		for (int i = 0; i < 10; i++)
			pigs[i]->Update(Time::instance.deltaTime);

		dLight->rotation.y += 1.0f * Time::instance.deltaTime;

		//pig->LookAt(-camera.GetWorldPosition());

		pig->SetLight(Vector::UnitZ * MatrixRotationFromVector(dLight->rotation), dLight->color, 0);
		genji->SetLight(Vector::UnitZ * MatrixRotationFromVector(dLight->rotation), dLight->color, 0);

		inputManager->LateUpdate();
	}

	void GameEngine::Render()
	{
		sceneManager->Render();
		graphicsEngine->BeginRender();

		GraphicsEngineSpace::ResourceManager* resourceManager = graphicsEngine->GetResourceManager();

		using GraphicsEngineSpace::ShaderType;

		float tick = Time::instance.deltaTime;

		/* Sky Box */
		graphicsEngine->GraphicsDebugBeginEvent("SkyBox");
		Matrix viewMatrix = camera.GetView();
		viewMatrix.r[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
		const Matrix& projMatix = camera.GetProjection();
		Matrix viewProjection = MatrixTranspose(viewMatrix * projMatix);
		skyBox->Render(graphicsEngine, viewProjection);
		graphicsEngine->GraphicsDebugEndEvent();

		/* View Projection */
		graphicsEngine->GraphicsDebugBeginEvent("ViewProjection");
		viewProjection = MatrixTranspose(camera.GetView() * projMatix);
		resourceManager->GetBuffer("ViewProjectionCB")->SetUpBuffer(1, &viewProjection, ShaderType::VERTEX);
		graphicsEngine->GraphicsDebugEndEvent();

		/* Cube */
		graphicsEngine->GraphicsDebugBeginEvent("Cube");
		cube->Render(graphicsEngine, tick);
		graphicsEngine->GraphicsDebugEndEvent();

		/* Genji */
		graphicsEngine->GraphicsDebugBeginEvent("Genji");

		/* View world*/
		graphicsEngine->GraphicsDebugBeginEvent("ViewWorldPosition");
		struct viewPos
		{
			Vector viewPosition;
		} cbViewPos;

		cbViewPos.viewPosition = camera.GetWorldPosition();

		resourceManager->GetBuffer("ViewWorldPosCB")->SetUpBuffer(0, &cbViewPos, ShaderType::PIXEL);
		graphicsEngine->GraphicsDebugEndEvent();

		/* Directional Light */
		graphicsEngine->GraphicsDebugBeginEvent("Directional Light");
		dLight->SetUpBuffer(1);
		graphicsEngine->GraphicsDebugEndEvent();

		/* Sampler */
		graphicsEngine->GraphicsDebugBeginEvent("LinearSampler");
		resourceManager->GetSampler("LinearSampler")->SetUpSampler(0, ShaderType::PIXEL);
		graphicsEngine->GraphicsDebugEndEvent();

		/* IBL */
		ibl->SetUpIBL(3, 4, 5, ShaderType::PIXEL);

		genji->Render(graphicsEngine, tick);

		graphicsEngine->GraphicsDebugEndEvent();

		/* Pig */
		graphicsEngine->GraphicsDebugBeginEvent("Pig");
		pig->Render(graphicsEngine, tick);

		for (int i = 0; i < 10; i++)
		{
			pigs[i]->Render(graphicsEngine, tick* i);
		}

		graphicsEngine->GraphicsDebugEndEvent();

		graphicsEngine->Render();

		/* PBR Cube */
		graphicsEngine->GraphicsDebugBeginEvent("PBR Cube");
		pbrCube->Render(graphicsEngine, tick);
		graphicsEngine->GraphicsDebugEndEvent();

		/* Post Process */
		if (Input::GetInstance()->GetInputState(VK_TAB, KeyState::TOGGLE) == true)
			graphicsEngine->PostProcess();

		/* Texture test */
		graphicsEngine->GraphicsDebugBeginEvent("Bricks");
		graphicsEngine->DrawSprite(resourceManager->GetTexture("Bricks")->GetTexture(), 5, 5, 300, 100, 10);
		graphicsEngine->GraphicsDebugEndEvent();

		graphicsEngine->DebugRender(Time::instance.GetFPS(), Time::instance.deltaTime);

		graphicsEngine->EndRender();
	}

	void GameEngine::Release()
	{
		graphicsEngine->Release();

		delete cube;
		delete pbrCube;
		delete genji;
		delete pig;
		delete ibl;

		for (int i = 0; i < 10; i++)
			delete pigs[i];
		
		delete dLight;
	}

	GameEngineDeclSpec GameEngine* CreateGameEngine()
	{
		return new GameEngine;
	}
}