/********************************
*								*
*	Application.h				*
*								*
*	Created : 2022/06/10		*
*	Updated : 2022/06/15		*
*********************************/

#pragma once
#include "Windows/WindowConstructor.h"

#define WINDOW_TEMP

namespace GameEngineSpace
{
	/// <summary>
	/// 만약 멀티 플랫폼을 한다면? 관리할 클래스
	/// </summary>
	class Application
	{
#ifdef WINDOW_TEMP
		using Platform = WindowConstructor;
#else
		using Platform = ? ;
#endif

		Platform* app;

		std::function<void(UINT, UINT)> onResize;

	public:
		Application();
		~Application();

		template <typename... Types>
		bool CreateApp(Types... args);

		void SetOnResizeFunc(std::function<void(UINT, UINT)> onResize);

		UINT GetWidth();
		UINT GetHeight();

#ifdef WINDOW_TEMP
		HWND GetWndHandle();
		void OnResize(UINT width, UINT height);
#else

#endif
	};

	template<typename ...Types>
	inline bool Application::CreateApp(Types ...args)
	{
		app = new Platform(args...);

		if (app == nullptr)
			return false;

		app->SetOnResizeFunc([this](UINT width, UINT height)
			{
				this->OnResize(width, height);
			});

		app->OnResize();

		return true;
	}
}