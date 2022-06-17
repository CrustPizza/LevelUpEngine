/********************************
*								*
*	Window Constructor.h		*
*								*
*	Created : 2022/06/10		*
*	Updated : 2022/06/15		*
*********************************/

#pragma once
#include <Windows.h>
#include <tchar.h>
#include <functional>

class Application;

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

public:
	WindowConstructor();
	WindowConstructor(HINSTANCE hInstance, RECT wndSize, DWORD style = WS_OVERLAPPEDWINDOW, int showOpt = SW_NORMAL, LPCWSTR appName = _T("LevelUpEngine"));
	~WindowConstructor();

	HWND GetWndHandle();
	void OnResize();

	void SetOnResizeFunc(std::function<void(UINT, UINT)> onResize);

	const RECT& GetWndSize();
	UINT GetWidth();
	UINT GetHeight();

	void SetWndSize(RECT wndSize);

private:
	bool RegistWindowClass();
	bool CreateWnd(DWORD style, int showOpt);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};