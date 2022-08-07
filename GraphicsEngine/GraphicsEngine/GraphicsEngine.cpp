/********************************
*								*
*	Graphics Engine.cpp			*
*								*
*	Created : 2022/06/15		*
*	Updated : 2022/07/01		*
*********************************/

#include "GraphicsEngine.h"
#include "../DirectX11/DirectX11Framework.h"

namespace GraphicsEngineSpace
{
	GraphicsEngine::GraphicsEngine()
		: graphicsDLL(nullptr)
		, graphicsEngine(nullptr)
		, factory(nullptr)
		, resourceManager(nullptr)
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

	Factory* const GraphicsEngine::CreateFactory()
	{
		if (factory != nullptr)
			return factory;

		if (graphicsEngine == nullptr)
			return nullptr;

		FactoryBase* graphicsFactory = graphicsEngine->CreateFactory();

		if (graphicsFactory == nullptr)
			return nullptr;

		factory = new Factory;
		resourceManager = new ResourceManager;
		factory->InitFactory(graphicsFactory, resourceManager);

		return factory;
	}

	ResourceManager* const GraphicsEngine::GetResourceManager()
	{
		return resourceManager;
	}

	bool GraphicsEngine::OnResize(UINT width, UINT height)
	{
		return graphicsEngine->OnResize(width, height);
	}

	bool GraphicsEngine::DrawSprite(Texture* texture, long posX, long posY, long width, long height, float z)
	{
		return graphicsEngine->DrawSprite(texture, posX, posY, width, height, z);
	}

	bool GraphicsEngine::DrawMesh(BufferBase* vertices, BufferBase* indices)
	{
		return graphicsEngine->DrawMesh(vertices, indices);
	}

	bool GraphicsEngine::DrawTextColor(std::string& text, Vector color, Vector position, float rotation, Vector scale)
	{
		return graphicsEngine->DrawTextColor(text, color, position, rotation, scale);
	}

	bool GraphicsEngine::SetUpShader(ShaderBase* shader)
	{
		return graphicsEngine->SetUpShader(shader);
	}

	bool GraphicsEngine::SetUpShader(const std::string& name)
	{
		ShaderBase* shader = resourceManager->GetShader(name);

		if (shader == nullptr)
			return false;

		SetUpShader(shader);
		shader->Release();

		return true;
	}

	bool GraphicsEngine::GraphicsDebugBeginEvent(const std::string& name)
	{
		if (graphicsEngine == nullptr)
			return false;

		return graphicsEngine->GraphicsDebugBeginEvent(name);
	}

	bool GraphicsEngine::GraphicsDebugEndEvent()
	{
		if (graphicsEngine == nullptr)
			return false;

		return graphicsEngine->GraphicsDebugEndEvent();
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
		if (resourceManager != nullptr)
			delete resourceManager;

		if (factory != nullptr)
			delete factory;

		if (graphicsEngine != nullptr)
		{
			graphicsEngine->Release();
			delete graphicsEngine;
		}

		if (graphicsDLL != nullptr)
			FreeLibrary(graphicsDLL);
	}

	void GraphicsEngine::DebugRender(int fps, float deltaTime)
	{
		std::string fpsStr = "FPS : ";
		fpsStr += std::to_string(fps);

		std::string dtStr = "DeltaTime : ";
		dtStr += std::to_string(deltaTime);

		graphicsEngine->DrawTextColor(fpsStr, Vector{ 1.0f, 1.0f, 0.0f, }, Vector{ 10.0f, 10.0f }, 0.0f, Vector{ 1.5f, 1.5f });
		graphicsEngine->DrawTextColor(dtStr, Vector{ 1.0f, 1.0f, 0.0f, }, Vector{ 10.0f, 40.0f }, 0.0f, Vector{ 1.5f, 1.5f });
	}

	GraphicsEngineDeclSpec GraphicsEngine* CreateGraphicsEngine()
	{
		return new GraphicsEngine;
	}
}