/********************************
*								*
*	Buffer Builder.h			*
*								*
*	Created : 2022/07/02		*
*	Updated : 2022/07/02		*
*********************************/

#include "BufferBuilder.h"

namespace DX11
{
	BufferBuilder::BufferBuilder(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
		: device(device)
		, deviceContext(deviceContext)
	{

	}

	BufferBuilder::~BufferBuilder()
	{

	}
}