/********************************
*								*
*	Window Constructor.h		*
*								*
*	Created : 2022/06/10		*
*	Updated : 2022/07/20		*
*********************************/

#pragma once
#include <Windows.h>
#include <tchar.h>
#include <functional>

namespace GameEngineSpace
{
	/// <summary>
	/// Window 생성 클래스
	/// </summary>
	class WindowConstructor
	{
		HWND hWnd;
		HINSTANCE hInstance;
		LPCWSTR appName;
		RECT wndSize;

		std::function<void(UINT, UINT)> onResize;
		std::function<void(float, float)> onMouseMove;

	public:
		WindowConstructor();
		WindowConstructor(HINSTANCE hInstance, RECT wndSize, DWORD style = WS_OVERLAPPEDWINDOW, int showOpt = SW_NORMAL, LPCWSTR appName = _T("LevelUpEngine"));
		~WindowConstructor();

		HWND GetWndHandle();
		void OnResize();
		void OnMouseMove(LPARAM lParam);

		void SetOnResizeFunc(std::function<void(UINT, UINT)> onResize);
		void SetOnMouseMove(std::function<void(float, float)> mouseMove);

		const RECT& GetWndSize();
		UINT GetWidth();
		UINT GetHeight();

		void SetWndSize(RECT wndSize);

	private:
		bool RegistWindowClass();
		bool CreateWnd(DWORD style, int showOpt);

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}