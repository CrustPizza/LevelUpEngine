/********************************
*								*
*	DirectX11 Framework.h		*
*								*
*	Created : 2022/06/14		*
*	Updated : 2022/06/15		*
*********************************/

#pragma once

/* Windows */
#include <Windows.h>
#include <tchar.h>

/* DirectX11 */
#include "DirectX11/DirectX11.h"

/* Libarary */
#ifdef x64
#ifdef _DEBUG
#pragma comment(lib, "Lib/DirectXTK_Debug_x64.lib")
#else
#pragma comment(lib, "Lib/DirectXTK_Release_x64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "Lib/DirectXTK_Debug_x86.lib")
#else
#pragma comment(lib, "Lib/DirectXTK_Release_x86.lib")
#endif
#endif

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")