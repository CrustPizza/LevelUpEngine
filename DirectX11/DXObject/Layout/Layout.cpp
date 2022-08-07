/********************************
*								*
*	Layout.cpp					*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/01		*
*********************************/

#include "Layout.h"
#include "FormatConverter/FormatConverter.h"

namespace DX11
{
	Layout::Layout()
	{

	}

	Layout::~Layout()
	{

	}

	void Layout::AddElements(const char* semantic, UINT index, GraphicsFormat format, UINT slot, UINT offset)
	{
		D3D11_INPUT_ELEMENT_DESC desc
		{
			semantic,
			index,
			GetDxFormat(format),
			slot,
			offset,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		};

		layout.push_back(desc);
	}

	InputLayout* Layout::GetLayout()
	{
		return reinterpret_cast<InputLayout*>(layout.data());
	}

	UINT Layout::GetLayoutSize()
	{
		return layout.size();
	}
}