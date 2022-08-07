/********************************
*								*
*	Application.cpp				*
*								*
*	Created : 2022/06/10		*
*	Updated : 2022/07/20		*
*********************************/

#include "Application.h"
#include "../GraphicsEngine/GraphicsEngine/GraphicsEngine.h"

namespace GameEngineSpace
{
	Application::Application()
		: app(nullptr)
	{

	}

	Application::~Application()
	{
		delete app;
	}

	void Application::SetOnResizeFunc(std::function<void(UINT, UINT)> onResize)
	{
		app->SetOnResizeFunc(onResize);
	}

	void Application::SetOnMouseMove(std::function<void(float, float)> mouseMove)
	{
		app->SetOnMouseMove(mouseMove);
	}

	UINT Application::GetWidth()
	{
		return app->GetWidth();
	}

	UINT Application::GetHeight()
	{
		return app->GetHeight();
	}

#ifdef WINDOW_TEMP
	HWND Application::GetWndHandle()
	{
		if (app == nullptr)
			return nullptr;

		return app->GetWndHandle();
	}
#endif
}