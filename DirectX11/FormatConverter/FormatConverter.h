/********************************
*								*
*	Format Converter.h			*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/02		*
*********************************/

#pragma once

#include <d3d11_1.h>
#include "../GraphicsEngine/Define/GraphicsFormat.h"
#include "../GraphicsEngine/Define/GraphicsUsage.h"
#include "../GraphicsEngine/Define/GraphicsFilterOption.h"

namespace DX11
{
	DXGI_FORMAT GetDxFormat(GraphicsEngineSpace::GraphicsFormat format);
	D3D11_USAGE GetDxUsage(GraphicsEngineSpace::USAGE usage);
	D3D11_FILTER GetDxFilter(GraphicsEngineSpace::FilterOption filter);
}