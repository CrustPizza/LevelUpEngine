/********************************
*								*
*	Graphics Engine.h			*
*								*
*	Created : 2022/06/15		*
*	Updated : 2022/07/01		*
*********************************/

#pragma once

#include <Windows.h>
#include "GraphicsEngine/Factory/Factory.h"
#include "Bases/GraphicsEngineBase.h"

namespace GraphicsEngineSpace
{
#ifdef GraphicsEngine_Export
#define GraphicsEngineDeclSpec __declspec( dllexport )
#else
#define GraphicsEngineDeclSpec __declspec( dllimport )
#endif

	/// <summary>
	/// 외부에서 사용하는 Render의 관리자?
	/// 
	/// 2022. 06. 30
	/// </summary>
	class GraphicsEngineDeclSpec GraphicsEngine : public GraphicsEngineBase
	{
	private:
		HMODULE graphicsDLL;
		GraphicsEngineBase* graphicsEngine;

		// 주로 그리기와 관련된 객체를 생성한다.
		Factory* factory;

		// Factory에서 만든 객체들을 ResourceManager에서 관리한다.
		ResourceManager* resourceManager;

	public:
		GraphicsEngine();
		~GraphicsEngine() override;

		virtual bool CreateDirectXEngine(HWND hWnd, UINT width, UINT height);

		Factory* const CreateFactory() override;

		virtual ResourceManager* const GetResourceManager();

		bool OnResize(UINT width, UINT height) override;

		bool DrawSprite(Texture* texture, long posX, long posY, long width, long height, float z) override;

		bool DrawMesh(BufferBase* vertices, BufferBase* indices) override;
		bool DrawTextColor(std::string& text, Vector color, Vector position, float rotation = 0.0f, Vector scale = { 1.0f, 1.0f }) override;

		bool SetUpShader(ShaderBase* shader) override;
		bool SetUpShader(const std::string& name);

		bool GraphicsDebugBeginEvent(const std::string& name) override;
		bool GraphicsDebugEndEvent() override;

		void BeginRender() override;
		void Render() override;
		void PostProcess() override;
		void EndRender() override;
		void Release() override;

		virtual void DebugRender(int fps, float deltaTime);
	};

	extern "C"
	{
		GraphicsEngineDeclSpec GraphicsEngine* CreateGraphicsEngine();
		using GraphicsEngineConstructor = GraphicsEngine* (*)(void);
	}
}