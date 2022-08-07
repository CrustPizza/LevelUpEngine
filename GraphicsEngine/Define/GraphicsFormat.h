/********************************
*								*
*	Graphics Format.h			*
*								*
*	Created : 2022/06/30		*
*	Updated : 2022/06/30		*
*********************************/

#pragma once

namespace GraphicsEngineSpace
{
	enum class GraphicsFormat
	{
		// RGBA - Float
		Float_R32G32B32A32,
		Float_R16G16B16A16,

		// RGBA - UINT
		UINT_R32G32B32A32,
		UINT_R16G16B16A16,
		UINT_R8G8B8A8,

		// RGB - Float
		Float_R32G32B32,

		// RGB - UINT
		UINT_R32G32B32,

		// RG - Float
		Float_R32G32,
		Float_R16G16,

		// RG - UINT
		UINT_R32G32,
		UINT_R16G16,
		UINT_R8G8,

	};
}