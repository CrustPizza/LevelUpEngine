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
		genji->Init(graphicsFactory, genjiModel, vertexShader, pixelShader, matrixBuffer, materialBuffer);

		pbrGenji = new Genji;
		pbrGenji->Init(graphicsFactory, genjiModel);

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
		//skyBox->SetTexture(graphicsFactory->CreateTexture("LobbyCubeMap", "Resources/Texture/lobbycube.dds"));

		dLight = graphicsFactory->CreateDirectionalLight("DLight");
		dLight->rotation.x += 45.0f;

		pLight = graphicsFactory->CreatePointLight("PLight");
		pLight->color = { 1.0f, 0.0f, 0.0f, 1.0f };
		pLight->intensity = 20.0f;

		graphicsFactory->CreateTexture("Bricks", "Resources/Texture/bricks.dds");

		ibl = graphicsFactory->CreateIBLTexture("MSIBL", "Resources/Texture/SunSubMixer_specularIBL.dds", "Resources/Texture/SunSubMixer_diffuseIBL.dds");
		skyBox->SetTexture(resourceManager->GetTexture("MSIBL_radiance"));

		canvas = graphicsFactory->CreateCanvas("Canvas", app->GetWidth(), app->GetHeight());
		TextureUI* t1 = canvas->CreateTextureUI("Image");
		TextureUI* t2 = canvas->CreateTextureUI("Image");
		TextUI* text = canvas->CreateTextUI("Text");
		t1->SetTexture(graphicsFactory->CreateTexture("Cat1", "Resources/UI/MainMenuTest.jpg"));
		t2->SetTexture(graphicsFactory->CreateTexture("Cat2", "Resources/UI/ButtonTest1.jpg"));
		text->SetText("BBBBBBBB");

		t1->SetPosition({ 0.0f, 0.0f, 0.2f });
		t2->SetPosition({ 0.0f, 0.0f, -0.1f });
		t1->SetWidth(t1->GetWidth() * 2);
		t1->SetHeight(t1->GetHeight() * 2);
		t2->SetParent(t1);
		text->SetParent(t2);
		text->SetPosition({ 0.0f, 0.0f, -0.1f });
		text->SetColor({ 1.0f, 1.0f, 0.0f });

		spriteAnim = graphicsFactory->CreateSpriteAnimation("SpriteAnimation");
		spriteAnim->SetTexture(graphicsFactory->CreateTexture("Explosion", "Resources/Effect/explosion.png"), 960, 382, 5, 2, 0.1f);
		spriteAnim->SetLoop(true);
		spriteAnim->SetPosition({ 10.0f, 10.0f, 0.0f, 1.0f });
		spriteAnim->SetWidth(2.0f);
		spriteAnim->SetHeight(2.0f);
	}

	void GameEngine::Update()
	{
		Time::instance.Update();
		inputManager->Update();
		camera.CameraMove(Time::instance.deltaTime);
		camera.CameraRotation();

		if (Input::GetInstance()->GetInputState('Z', KeyState::TOGGLE) == true)
			camera.LookAt(pig->GetTransform().position);

		sceneManager->Update();

		cube->Update(Time::instance.deltaTime);
		pbrCube->Update(Time::instance.deltaTime);
		genji->Update(Time::instance.deltaTime);
		pbrGenji->Update(Time::instance.deltaTime);

		static float metallic = 0.5f;

		if (Input::GetInstance()->GetInputState('R', KeyState::STAY) == true)
		{
			metallic += 0.5f * Time::instance.deltaTime;

			if (metallic > 1.0f)
				metallic = 1.0f;

			pbrGenji->SetMetallic(metallic);
		}
		else if (Input::GetInstance()->GetInputState('F', KeyState::STAY) == true)
		{
			metallic -= 0.5f * Time::instance.deltaTime;

			if (metallic < 0.0f)
				metallic = 0.0f;

			pbrGenji->SetMetallic(metallic);
		}

		static float roughness = 0.5f;

		if (Input::GetInstance()->GetInputState('T', KeyState::STAY) == true)
		{
			roughness += 0.5f * Time::instance.deltaTime;

			if (roughness > 1.0f)
				roughness = 1.0f;

			pbrGenji->SetRoughness(roughness);
		}
		else if (Input::GetInstance()->GetInputState('G', KeyState::STAY) == true)
		{
			roughness -= 0.5f * Time::instance.deltaTime;

			if (roughness < 0.0f)
				roughness = 0.0f;

			pbrGenji->SetRoughness(roughness);
		}

		if (Input::GetInstance()->GetInputState(VK_RIGHT, KeyState::DOWN) == true)
			pig->AddForce(Vector::UnitX * VectorReplicate(5.0f));

		if (Input::GetInstance()->GetInputState(VK_LEFT, KeyState::DOWN) == true)
			pig->AddForce(-Vector::UnitX * VectorReplicate(5.0f));

		if (Input::GetInstance()->GetInputState(VK_SPACE, KeyState::TOGGLE) == true)
			pig->Update(0.0f);
		else
			pig->Update(Time::instance.deltaTime);

		dLight->rotation.y += 1.0f * Time::instance.deltaTime;

		//pig->LookAt(-camera.GetWorldPosition());

		Vector pLightVector = pig->GetTransform().GetWorldTransform()[3] - pLight->position;
		float distance = Vector3Length(pLightVector);

		if (distance > 0.0f)
			pLightVector = Vector3Normalize(pLightVector);
		else
			pLightVector = Vector::Zero;

		Vector pLightColor;

		if (distance > pLight->intensity)
			pLightColor = Vector::Zero;
		else
			pLightColor = pLight->color * VectorReplicate(1.0f - distance / pLight->intensity);

		pig->SetLight(Vector::UnitZ * MatrixRotationFromVector(dLight->rotation), dLight->color, 0);
		pig->SetLight(pLightVector, pLightColor, 1);

		pLightVector = pbrGenji->GetTransform().GetWorldTransform()[3] - pLight->position;
		distance = Vector3Length(pLightVector);

		if (distance > 0.0f)
			pLightVector = Vector3Normalize(pLightVector);
		else
			pLightVector = Vector::Zero;

		pLightColor;

		if (distance > pLight->intensity)
			pLightColor = Vector::Zero;
		else
			pLightColor = pLight->color * VectorReplicate(1.0f - distance / pLight->intensity);

		pbrGenji->SetLight(Vector::UnitZ * MatrixRotationFromVector(dLight->rotation), dLight->color, 0);
		pbrGenji->SetLight(pLightVector, pLightColor, 1);

		for (int i = 0; i < 10; i++)
		{
			pLightVector = pigs[i]->GetTransform().GetWorldTransform()[3] - pLight->position;
			distance = Vector3Length(pLightVector);

			if (distance > 0.0f)
				pLightVector = Vector3Normalize(pLightVector);
			else
				pLightVector = Vector::Zero;

			pLightColor;

			if (distance > pLight->intensity)
				pLightColor = Vector::Zero;
			else
				pLightColor = pLight->color * VectorReplicate(1.0f - distance / pLight->intensity);

			pigs[i]->Update(Time::instance.deltaTime);
			pigs[i]->SetLight(Vector::UnitZ * MatrixRotationFromVector(dLight->rotation), dLight->color, 0);
			pigs[i]->SetLight(pLightVector, pLightColor, 1);
		}

		pLightVector = pbrCube->GetTransform().GetWorldTransform()[3] - pLight->position;
		distance = Vector3Length(pLightVector);

		if (distance > 0.0f)
			pLightVector = Vector3Normalize(pLightVector);
		else
			pLightVector = Vector::Zero;

		pLightColor;

		if (distance > pLight->intensity)
			pLightColor = Vector::Zero;
		else
			pLightColor = pLight->color * VectorReplicate(1.0f - distance / pLight->intensity);

		pbrCube->SetLight(Vector::UnitZ * MatrixRotationFromVector(dLight->rotation), dLight->color, 0);
		pbrCube->SetLight(pLightVector, pLightColor, 1);

		using GraphicsEngineSpace::HorizontalLocation;
		using GraphicsEngineSpace::VerticalLocation;

		if (Input::GetInstance()->GetInputState(VK_RETURN, KeyState::TOGGLE) == true)
		{
			if (Input::GetInstance()->GetInputState('1', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image")->SetAnchor({ HorizontalLocation::LEFT, VerticalLocation::TOP });
			if (Input::GetInstance()->GetInputState('2', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image")->SetAnchor({ HorizontalLocation::CENTER, VerticalLocation::TOP });
			if (Input::GetInstance()->GetInputState('3', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image")->SetAnchor({ HorizontalLocation::RIGHT, VerticalLocation::TOP });
			if (Input::GetInstance()->GetInputState('4', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image")->SetAnchor({ HorizontalLocation::LEFT, VerticalLocation::MIDDLE });
			if (Input::GetInstance()->GetInputState('5', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image")->SetAnchor({ HorizontalLocation::CENTER, VerticalLocation::MIDDLE });
			if (Input::GetInstance()->GetInputState('6', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image")->SetAnchor({ HorizontalLocation::RIGHT, VerticalLocation::MIDDLE });
			if (Input::GetInstance()->GetInputState('7', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image")->SetAnchor({ HorizontalLocation::LEFT, VerticalLocation::BOTTOM });
			if (Input::GetInstance()->GetInputState('8', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image")->SetAnchor({ HorizontalLocation::CENTER, VerticalLocation::BOTTOM });
			if (Input::GetInstance()->GetInputState('9', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image")->SetAnchor({ HorizontalLocation::RIGHT, VerticalLocation::BOTTOM });
		}
		else if (Input::GetInstance()->GetInputState(VK_SHIFT, KeyState::TOGGLE) == true)
		{
			if (Input::GetInstance()->GetInputState('1', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetAnchor({ HorizontalLocation::LEFT, VerticalLocation::TOP });
			if (Input::GetInstance()->GetInputState('2', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetAnchor({ HorizontalLocation::CENTER, VerticalLocation::TOP });
			if (Input::GetInstance()->GetInputState('3', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetAnchor({ HorizontalLocation::RIGHT, VerticalLocation::TOP });
			if (Input::GetInstance()->GetInputState('4', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetAnchor({ HorizontalLocation::LEFT, VerticalLocation::MIDDLE });
			if (Input::GetInstance()->GetInputState('5', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetAnchor({ HorizontalLocation::CENTER, VerticalLocation::MIDDLE });
			if (Input::GetInstance()->GetInputState('6', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetAnchor({ HorizontalLocation::RIGHT, VerticalLocation::MIDDLE });
			if (Input::GetInstance()->GetInputState('7', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetAnchor({ HorizontalLocation::LEFT, VerticalLocation::BOTTOM });
			if (Input::GetInstance()->GetInputState('8', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetAnchor({ HorizontalLocation::CENTER, VerticalLocation::BOTTOM });
			if (Input::GetInstance()->GetInputState('9', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetAnchor({ HorizontalLocation::RIGHT, VerticalLocation::BOTTOM });
		}
		else if (Input::GetInstance()->GetInputState(VK_BACK, KeyState::TOGGLE) == true)
		{
			if (Input::GetInstance()->GetInputState('1', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetPivot({ HorizontalLocation::LEFT, VerticalLocation::TOP });
			if (Input::GetInstance()->GetInputState('2', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetPivot({ HorizontalLocation::CENTER, VerticalLocation::TOP });
			if (Input::GetInstance()->GetInputState('3', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetPivot({ HorizontalLocation::RIGHT, VerticalLocation::TOP });
			if (Input::GetInstance()->GetInputState('4', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetPivot({ HorizontalLocation::LEFT, VerticalLocation::MIDDLE });
			if (Input::GetInstance()->GetInputState('5', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetPivot({ HorizontalLocation::CENTER, VerticalLocation::MIDDLE });
			if (Input::GetInstance()->GetInputState('6', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetPivot({ HorizontalLocation::RIGHT, VerticalLocation::MIDDLE });
			if (Input::GetInstance()->GetInputState('7', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetPivot({ HorizontalLocation::LEFT, VerticalLocation::BOTTOM });
			if (Input::GetInstance()->GetInputState('8', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetPivot({ HorizontalLocation::CENTER, VerticalLocation::BOTTOM });
			if (Input::GetInstance()->GetInputState('9', KeyState::DOWN) == true)
				canvas->GetTextureUI("Image1")->SetPivot({ HorizontalLocation::RIGHT, VerticalLocation::BOTTOM });
		}

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
		dLight->SetUpBuffer(1, ShaderType::PIXEL);
		graphicsEngine->GraphicsDebugEndEvent();

		/* Point Light */
		graphicsEngine->GraphicsDebugBeginEvent("Point Light");
		pLight->SetUpBuffer(2, ShaderType::PIXEL);
		graphicsEngine->GraphicsDebugEndEvent();

		/* Sampler */
		graphicsEngine->GraphicsDebugBeginEvent("LinearSampler");
		resourceManager->GetSampler("LinearSampler")->SetUpSampler(0, ShaderType::PIXEL);
		graphicsEngine->GraphicsDebugEndEvent();

		/* IBL */
		ibl->SetUpIBL(4, 4, 5, ShaderType::PIXEL);

		/* Genji */
		graphicsEngine->GraphicsDebugBeginEvent("Genji");
		genji->Render(graphicsEngine, tick);
		pbrGenji->Render(graphicsEngine, tick);
		graphicsEngine->GraphicsDebugEndEvent();

		/* Pig */
		graphicsEngine->GraphicsDebugBeginEvent("Pig");
		pig->Render(graphicsEngine, tick);

		for (int i = 0; i < 10; i++)
		{
			pigs[i]->Render(graphicsEngine, tick * i);
		}

		graphicsEngine->GraphicsDebugEndEvent();

		/* PBR Cube */
		graphicsEngine->GraphicsDebugBeginEvent("PBR Cube");
		pbrCube->Render(graphicsEngine, tick);
		graphicsEngine->GraphicsDebugEndEvent();

		static float depth = 0.0f;

		if (Input::GetInstance()->GetInputState(VK_UP, KeyState::STAY) == true)
			depth += 0.01f;
		else if (Input::GetInstance()->GetInputState(VK_DOWN, KeyState::STAY) == true)
			depth -= 0.01f;

		graphicsEngine->GraphicsDebugBeginEvent("Bricks 1");
		Vector position[3] =
		{
			{ 10.0f, 0.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
			{ 10.0f, -10.0f, 0.0f, 1.0f }
		};
		graphicsEngine->DrawSpriteOn3D(resourceManager->GetTexture("Explosion")->GetTexture(), position, viewProjection);
		Vector singlePosition = { 0.0f, 0.0f, 0.0f, 1.0f };

		static float x = 0.0f;
		if (Input::GetInstance()->GetInputState('V', KeyState::STAY) == true)
		{
			x += 0.01f;
			
		}

		singlePosition.x = x;

		Matrix rtm = MatrixLookAtLH(singlePosition, camera.GetWorldPosition(), Vector::UnitY);

		rtm = MatrixInverse(rtm);
		rtm = MatrixTranspose(rtm * camera.GetView() * camera.GetProjection());

		graphicsEngine->DrawSpriteOn3D(resourceManager->GetTexture("Explosion")->GetTexture(), 10.0f, 10.0f, rtm);
		graphicsEngine->GraphicsDebugEndEvent();

		graphicsEngine->GraphicsDebugBeginEvent("Sprite Animation");
		spriteAnim->Render(graphicsEngine, camera.GetView() * camera.GetProjection(), camera.GetWorldPosition(), tick);
		graphicsEngine->GraphicsDebugEndEvent();

		graphicsEngine->Render();

		/* Post Process */
		if (Input::GetInstance()->GetInputState(VK_TAB, KeyState::TOGGLE) == true)
			graphicsEngine->PostProcess();

		/* Texture test */
		graphicsEngine->GraphicsDebugBeginEvent("Bricks");
		graphicsEngine->DrawSprite(resourceManager->GetTexture("Explosion")->GetTexture(), 5, 5, 300, 100, 0.0f);
		graphicsEngine->GraphicsDebugEndEvent();

		canvas->Render(graphicsEngine);

		graphicsEngine->DebugRender(Time::instance.GetFPS(), Time::instance.deltaTime);

		graphicsEngine->EndRender();
	}

	void GameEngine::Release()
	{
		graphicsEngine->Release();

		delete cube;
		delete pbrCube;
		delete genji;
		delete pbrGenji;
		delete pig;

		for (int i = 0; i < 10; i++)
			delete pigs[i];
	}

	GameEngineDeclSpec GameEngine* CreateGameEngine()
	{
		return new GameEngine;
	}
}