/********************************
*								*
*	Window Constructor.cpp		*
*								*
*	Created : 2022/06/10		*
*	Updated : 2022/06/15		*
*********************************/

#include "WindowConstructor.h"
#include "../Application.h"

GameEngineSpace::WindowConstructor* thisWindow = nullptr;

namespace GameEngineSpace
{
	WindowConstructor::WindowConstructor()
		: hWnd(nullptr)
		, hInstance(nullptr)
		, appName(nullptr)
		, wndSize{}
	{
		thisWindow = this;
	}

	WindowConstructor::WindowConstructor(HINSTANCE hInstance, RECT wndSize, DWORD style, int showOpt, LPCWSTR appName)
		: hWnd(nullptr)
		, hInstance(hInstance)
		, appName(appName)
		, wndSize(wndSize)
		, onResize(nullptr)
	{
		thisWindow = this;
		RegistWindowClass();
		CreateWnd(style, showOpt);
	}

	WindowConstructor::~WindowConstructor()
	{

	}

	HWND WindowConstructor::GetWndHandle()
	{
		if (hWnd == nullptr)
			return nullptr;

		return hWnd;
	}

	void WindowConstructor::OnResize()
	{
		if (onResize == nullptr)
			return;

		onResize(GetWidth(), GetHeight());
	}

	void WindowConstructor::SetOnResizeFunc(std::function<void(UINT, UINT)> onResize)
	{
		this->onResize = onResize;
	}

	const RECT& WindowConstructor::GetWndSize()
	{
		return wndSize;
	}

	UINT WindowConstructor::GetWidth()
	{
		return wndSize.right - wndSize.left;
	}

	UINT WindowConstructor::GetHeight()
	{
		return wndSize.bottom - wndSize.top;
	}

	void WindowConstructor::SetWndSize(RECT wndSize)
	{
		this->wndSize = wndSize;
	}

	bool WindowConstructor::RegistWindowClass()
	{
		WNDCLASS wndClass;

		wndClass.hInstance = hInstance;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.lpszClassName = appName;
		wndClass.lpszMenuName = nullptr;
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

		if (!RegisterClass(&wndClass))
			return false;

		return true;
	}

	bool WindowConstructor::CreateWnd(DWORD style, int showOpt)
	{
		if (AdjustWindowRect(&wndSize, style, FALSE) == FALSE)
			return false;

		hWnd = CreateWindow(
			appName,
			appName,
			style,
			0, 0,
			wndSize.right - wndSize.left,
			wndSize.bottom - wndSize.top,
			nullptr, nullptr, hInstance, 0);

		if (hWnd == nullptr)
			return false;

		ShowWindow(hWnd, showOpt);

		return true;
	}

	LRESULT CALLBACK WindowConstructor::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);

			break;
		}

		case WM_SIZE:
		{
			RECT rect;
			GetClientRect(hWnd, &rect);
			thisWindow->SetWndSize(rect);
			thisWindow->OnResize();

			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);

			break;
		}

		default:
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		}

		return TRUE;
	}
}