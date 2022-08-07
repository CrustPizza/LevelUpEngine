/********************************
*								*
*	Application.h				*
*								*
*	Created : 2022/06/10		*
*	Updated : 2022/07/20		*
*********************************/

#pragma once
#include "Windows/WindowConstructor.h"

#define WINDOW_TEMP

namespace GameEngineSpace
{
	/// <summary>
	/// ���� ��Ƽ �÷����� �Ѵٸ�? ������ Ŭ����
	/// </summary>
	class Application
	{
#ifdef WINDOW_TEMP
		using Platform = WindowConstructor;
#else
		using Platform = ? ;
#endif

		Platform* app;

	public:
		Application();
		~Application();

		template <typename... Types>
		bool CreateApp(Types... args);

		void SetOnResizeFunc(std::function<void(UINT, UINT)> onResize);
		void SetOnMouseMove(std::function<void(float, float)> mouseMove);

		UINT GetWidth();
		UINT GetHeight();

#ifdef WINDOW_TEMP
		HWND GetWndHandle();
#else

#endif
	};

	template<typename ...Types>
	inline bool Application::CreateApp(Types ...args)
	{
		app = new Platform(args...);

		if (app == nullptr)
			return false;

		app->OnResize();

		return true;
	}
}