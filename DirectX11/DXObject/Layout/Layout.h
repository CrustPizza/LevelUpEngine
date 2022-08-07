/********************************
*								*
*	Layout.h					*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/01		*
*********************************/

#pragma once

#include "../GraphicsEngine/Bases/LayoutBase.h"
#include <vector>
#include <d3d11_1.h>

namespace DX11
{
	using GraphicsEngineSpace::LayoutBase;
	using GraphicsEngineSpace::UINT;
	using GraphicsEngineSpace::GraphicsFormat;
	using GraphicsEngineSpace::InputLayout;

	class Layout : public LayoutBase
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
		
	public:
		Layout();
		~Layout() override;

		void AddElements(const char* semantic, UINT index, GraphicsFormat format, UINT slot, UINT offset /* instancing 데이터 추가할지 말지*/) override;

		InputLayout* GetLayout() override;
		UINT GetLayoutSize() override;
	};
}