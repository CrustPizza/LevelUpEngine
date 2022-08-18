/********************************
*								*
*	Graphics Engine.cpp			*
*								*
*	Created : 2022/06/15		*
*	Updated : 2022/08/11		*
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
		, fontName("����")
		, width(0)
		, height(0)
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
			// DLL �ε� ����
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
		this->width = width;
		this->height = height;

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
		this->width = width;
		this->height = height;

		return graphicsEngine->OnResize(width, height);
	}

	bool GraphicsEngine::DrawSprite(Texture* texture, long posX, long posY, long width, long height, float z)
	{
		return graphicsEngine->DrawSprite(texture, posX, posY, width, height, z);
	}

	bool GraphicsEngine::DrawSprite(Texture* texture, const Rect& dest, const Rect& src, float z)
	{
		return graphicsEngine->DrawSprite(texture, dest, src, z);
	}

	bool GraphicsEngine::DrawSpriteOn3D(Texture* texture, HeraclesMath::Vector worldPosition[3], const HeraclesMath::Matrix& viewProjection)
	{
		return graphicsEngine->DrawSpriteOn3D(texture, worldPosition, viewProjection);
	}

	bool GraphicsEngine::DrawSpriteOn3D(Texture* texture, long width, long height, const HeraclesMath::Matrix& worldViewProjection)
	{
		return graphicsEngine->DrawSpriteOn3D(texture, width, height, worldViewProjection);
	}

	bool GraphicsEngine::DrawSpriteOn3D(Texture* texture, long width, long height, const Matrix& worldViewProjection, const Vector texCoord[3])
	{
		return graphicsEngine->DrawSpriteOn3D(texture, width, height, worldViewProjection, texCoord);
	}

	bool GraphicsEngine::DrawMesh(BufferBase* vertices, BufferBase* indices)
	{
		return graphicsEngine->DrawMesh(vertices, indices);
	}

	bool GraphicsEngine::DrawTextColor(std::string& text, Vector color, Vector position, float rotation, Vector scale)
	{
		return resourceManager->GetFont(fontName)->DrawTextColor(text, color, position, rotation, scale);
	}

	bool GraphicsEngine::DrawTextColor(const std::string& fontName, std::string& text, Vector color, Vector position, float rotation, Vector scale)
	{
		FontBase* font = resourceManager->GetFont(fontName);

		if (font == nullptr)
			return false;

		return font->DrawTextColor(text, color, position, rotation, scale);
	}

	bool GraphicsEngine::DrawTextColor(const std::string& fontName, std::wstring& text, Vector color, Vector position, float rotation, Vector scale)
	{
		FontBase* font = resourceManager->GetFont(fontName);

		if (font == nullptr)
			return false;

		return font->DrawTextColor(text, color, position, rotation, scale);
	}

	bool GraphicsEngine::DrawLine(BufferBase* vertices, BufferBase* indices)
	{
		resourceManager->GetShader("LineVS")->SetUpShader();
		resourceManager->GetShader("LinePS")->SetUpShader();
		resourceManager->GetBuffer("ColorCB")->SetUpBuffer(6, const_cast<Vector*>(&Vector::One), ShaderType::PIXEL);

		return graphicsEngine->DrawLine(vertices, indices);
	}

	bool GraphicsEngine::DrawLine(BufferBase* vertices, BufferBase* indices, const Vector& color, const Matrix& worldTransform)
	{
		resourceManager->GetShader("LineVS")->SetUpShader();
		resourceManager->GetShader("LinePS")->SetUpShader();
		resourceManager->GetBuffer("WorldMatrixCB")->SetUpBuffer(0, const_cast<Matrix*>(&worldTransform), ShaderType::VERTEX);
		resourceManager->GetBuffer("ColorCB")->SetUpBuffer(6, const_cast<Vector*>(&color), ShaderType::PIXEL);

		return graphicsEngine->DrawLine(vertices, indices);
	}

	bool GraphicsEngine::SetFontName(const std::string& fontName)
	{
		FontBase* font = resourceManager->GetFont(fontName);

		if (font == nullptr)
			return false;

		this->fontName = fontName;

		return true;
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

	void GraphicsEngine::BeginShadowRender()
	{

	}

	void GraphicsEngine::EndShadowRender()
	{

	}

	void GraphicsEngine::BeginRender()
	{
		graphicsEngine->BeginRender();
	}

	void GraphicsEngine::Render()
	{
		DirectionalLight* dLight = resourceManager->GetDirectionalLight();

		if (dLight != nullptr)
		{
			graphicsEngine->BeginShadowRender();

			resourceManager->GetShader("ShadowMapPS")->SetUpShader();

			Vector position = Vector::Backward * MatrixRotationFromVector(dLight->rotation);
			position *= 10.0f;

			Matrix lightProjection = OrthographicOffCenterMatrix(position.x - 200, position.x + 200, position.y - 200, position.y + 200, position.z - 200, position.z + 200);
			//Matrix lightProjection = OrthographicMatrix(300, 300, -300, 300.0f);

			Matrix lightViewProjection = ViewMatrix(position, dLight->rotation) * lightProjection;
			lightViewProjection = MatrixTranspose(lightViewProjection);

			resourceManager->GetBuffer("LightViewProjectionCB")->SetUpBuffer(7, &lightViewProjection, ShaderType::VERTEX);

			for (auto& iter : renderQueue)
			{
				if (iter.prefab != nullptr)
				{
					graphicsEngine->GraphicsDebugBeginEvent(iter.prefab->model->GetName() + "_Shadow");
					iter.prefab->PrepareRender(iter.worldTransform, iter.animationTime);

					if (iter.prefab->isSkinning == true)
					{
						resourceManager->GetShader("ShadowSkinningMapVS")->SetUpShader();
						resourceManager->GetBuffer("BoneMatrixCB")->SetUpBuffer(3, iter.prefab->model->GetBoneMatrix(), ShaderType::VERTEX);
					}
					else
					{
						resourceManager->GetShader("ShadowMapVS")->SetUpShader();
					}

					iter.prefab->ShadowRender(graphicsEngine);
					graphicsEngine->GraphicsDebugEndEvent();
				}
			}

			graphicsEngine->EndShadowRender();
		}

		graphicsEngine->GraphicsDebugBeginEvent("Render");

		for (auto& iter : renderQueue)
		{
			if (iter.prefab != nullptr)
			{
				graphicsEngine->GraphicsDebugBeginEvent(iter.prefab->model->GetName());
				iter.prefab->PrepareRender(iter.worldTransform, iter.animationTime);
				iter.prefab->RenderImpl(graphicsEngine);
				graphicsEngine->GraphicsDebugEndEvent();
			}
		}

		renderQueue.clear();

		graphicsEngine->GraphicsDebugEndEvent();
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

	void GraphicsEngine::DebugRender(int fps, float deltaTime, bool showMRT)
	{
		std::string fpsStr = "FPS : ";
		fpsStr += std::to_string(fps);

		std::string dtStr = "DeltaTime : ";
		dtStr += std::to_string(deltaTime);

		DrawTextColor(fpsStr, Vector{ 1.0f, 1.0f, 0.0f, }, Vector{ 10.0f, 10.0f }, 0.0f, Vector{ 1.5f, 1.5f });
		DrawTextColor(dtStr, Vector{ 1.0f, 1.0f, 0.0f, }, Vector{ 10.0f, 40.0f }, 0.0f, Vector{ 1.5f, 1.5f });

		if (showMRT == true)
			graphicsEngine->DebugRender();
	}

	void GraphicsEngine::AddRenderQueue(const RenderData& renderData)
	{
		renderQueue.push_back(renderData);
	}

	void GraphicsEngine::DebugRender()
	{
	}

	GraphicsEngineDeclSpec GraphicsEngine* CreateGraphicsEngine()
	{
		return new GraphicsEngine;
	}
}