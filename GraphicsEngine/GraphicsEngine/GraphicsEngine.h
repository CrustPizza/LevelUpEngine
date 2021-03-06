/********************************
*								*
*	Graphics Engine.h			*
*								*
*	Created : 2022/06/15		*
*	Updated : 2022/06/17		*
*********************************/

#pragma once

#include "./EngineBase/GraphicsEngineBase.h"

namespace GraphicsEngineSpace
{
#ifdef GraphicsEngine_Export
#define GraphicsEngineDeclSpec __declspec( dllexport )
#else
#define GraphicsEngineDeclSpec __declspec( dllimport )
#endif

	class GraphicsEngineDeclSpec GraphicsEngine : public GraphicsEngineBase
	{
	private:
		HMODULE graphicsDLL;
		GraphicsEngineBase* graphicsEngine;

	public:
		GraphicsEngine();
		~GraphicsEngine() override;

		virtual bool CreateDirectXEngine(HWND hWnd, UINT width, UINT height);

		bool OnResize(UINT width, UINT height) override;

		void BeginRender() override;
		void Render() override;
		void PostProcess() override;
		void EndRender() override;
		void Release() override;
	};

	extern "C"
	{
		GraphicsEngineDeclSpec GraphicsEngine* CreateGraphicsEngine();
		using GraphicsEngineConstructor = GraphicsEngine * (*)(void);
	}
}