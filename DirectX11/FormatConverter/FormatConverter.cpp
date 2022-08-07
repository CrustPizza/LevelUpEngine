/********************************
*								*
*	Format Converter.cpp		*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/02		*
*********************************/

#include "FormatConverter.h"

namespace DX11
{
	DXGI_FORMAT GetDxFormat(GraphicsEngineSpace::GraphicsFormat format)
	{
		using GraphicsEngineSpace::GraphicsFormat;

		switch (format)
		{

			// RGBA - Float
		case GraphicsFormat::Float_R32G32B32A32: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case GraphicsFormat::Float_R16G16B16A16: return DXGI_FORMAT_R16G16B16A16_FLOAT;

			// RGBA - UINT
		case GraphicsFormat::UINT_R32G32B32A32: return DXGI_FORMAT_R32G32B32A32_UINT;
		case GraphicsFormat::UINT_R16G16B16A16: return DXGI_FORMAT_R16G16B16A16_UINT;
		case GraphicsFormat::UINT_R8G8B8A8: return DXGI_FORMAT_R8G8B8A8_UINT;

			// RGB - Float
		case GraphicsFormat::Float_R32G32B32: return DXGI_FORMAT_R32G32B32_FLOAT;

			// RGB - UINT
		case GraphicsFormat::UINT_R32G32B32: return DXGI_FORMAT_R32G32B32_UINT;

			// RG - Float
		case GraphicsFormat::Float_R32G32: return DXGI_FORMAT_R32G32_FLOAT;
		case GraphicsFormat::Float_R16G16: return DXGI_FORMAT_R16G16_FLOAT;

			// RG - UINT
		case GraphicsFormat::UINT_R32G32: return DXGI_FORMAT_R32G32_UINT;
		case GraphicsFormat::UINT_R16G16: return DXGI_FORMAT_R16G16_UINT;
		case GraphicsFormat::UINT_R8G8: return DXGI_FORMAT_R8G8_UINT;

		}

		return DXGI_FORMAT_UNKNOWN;
	}

	D3D11_USAGE GetDxUsage(GraphicsEngineSpace::USAGE usage)
	{
		using GraphicsEngineSpace::USAGE;

		switch (usage)
		{
		case USAGE::IMMUTABLE: return D3D11_USAGE_IMMUTABLE;
		case USAGE::DYNAMIC: return D3D11_USAGE_DYNAMIC;
		case USAGE::STAGING: return D3D11_USAGE_STAGING;

		default: return D3D11_USAGE_DEFAULT;
		}
	}

	D3D11_FILTER GetDxFilter(GraphicsEngineSpace::FilterOption filter)
	{
		using GraphicsEngineSpace::FilterOption;

		switch (filter)
		{
		case FilterOption::POINT: return D3D11_FILTER_MIN_MAG_MIP_POINT;
		case FilterOption::LINEAR: return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		case FilterOption::ANISOTROPIC: return D3D11_FILTER_ANISOTROPIC;

		default: return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		}
	}
}