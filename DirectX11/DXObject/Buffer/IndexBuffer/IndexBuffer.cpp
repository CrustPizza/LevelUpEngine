/********************************
*								*
*	Index Buffer.cpp			*
*								*
*	Created : 2022/07/02		*
*	Updated : 2022/07/20		*
*********************************/

#include "IndexBuffer.h"

namespace DX11
{
	IndexBuffer::IndexBuffer(ID3D11DeviceContext* deviceContext)
		: BufferBase(GraphicsEngineSpace::BufferType::INDEX)
		, deviceContext(deviceContext)
		, buffer(nullptr)
		, size(0)
	{

	}

	IndexBuffer::~IndexBuffer()
	{
		if (buffer != nullptr)
		{
			buffer->Release();
		}
	}

	ID3D11Buffer* IndexBuffer::GetBuffer()
	{
		return buffer;
	}

	UINT IndexBuffer::GetSize()
	{
		return size;
	}

	bool IndexBuffer::SetUpBuffer(unsigned int slot, void* data, ShaderType targetType)
	{
		if (buffer == nullptr)
			return false;

		deviceContext->IASetIndexBuffer(buffer, DXGI_FORMAT_R16_UINT, 0);

		return true;
	}

	bool IndexBuffer::CreateBuffer(ID3D11Device* device, D3D11_USAGE usage, UINT CPUflag, UINT typeSize, void* indices, UINT size)
	{
		D3D11_BUFFER_DESC bufferDescription;
		ZeroMemory(&bufferDescription, sizeof(D3D11_BUFFER_DESC));
		bufferDescription.Usage = usage;
		bufferDescription.ByteWidth = typeSize * size;
		bufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDescription.CPUAccessFlags = CPUflag;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
		initData.pSysMem = indices;

		HRESULT hr = device->CreateBuffer(&bufferDescription, &initData, &buffer);

		this->size = size;

		return SUCCEEDED(hr);
	}
}