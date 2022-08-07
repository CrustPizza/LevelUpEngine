/********************************
*								*
*	Buffer Builder.h			*
*								*
*	Created : 2022/07/02		*
*	Updated : 2022/07/02		*
*********************************/

#pragma once

#include <d3d11_1.h>
#include <string>

namespace DX11
{
	class BufferBuilder
	{
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;

	public:
		BufferBuilder(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~BufferBuilder();

		template<typename T, typename ...Types>
		T* CreateBuffer(D3D11_USAGE usage, UINT CPUflag, Types ...args);
	};

	template<typename T, typename ...Types>
	inline T* BufferBuilder::CreateBuffer(D3D11_USAGE usage, UINT CPUflag, Types ...args)
	{
		ID3D11Buffer* buffer;

		T* newBuffer = new T(deviceContext);

		if (newBuffer == nullptr)
			return nullptr;

		if (newBuffer->CreateBuffer(device, usage, CPUflag, args...) != true)
			return nullptr;

		return newBuffer;
	}
}