/********************************
*								*
*	Application.cpp				*
*								*
*	Created : 2022/06/10		*
*	Updated : 2022/06/15		*
*********************************/

#include "Application.h"
#include "../../GraphicsEngine/GraphicsEngine/GraphicsEngine.h"

namespace GameEngineSpace
{
	Application::Application()
		: app(nullptr)
		, onResize(nullptr)
	{

	}

	Application::~Application()
	{
		delete app;
	}

	void Application::SetOnResizeFunc(std::function<void(UINT, UINT)> onResize)
	{
		this->onResize = onResize;
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

	void Application::OnResize(UINT width, UINT height)
	{
		if (onResize == nullptr)
			return;

		onResize(width, height);
	}
#endif
}