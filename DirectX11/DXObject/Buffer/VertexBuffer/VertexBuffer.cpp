/********************************
*								*
*	Vertex Buffer.cpp			*
*								*
*	Created : 2022/07/02		*
*	Updated : 2022/07/20		*
*********************************/

#include "VertexBuffer.h"

namespace DX11
{
	VertexBuffer::VertexBuffer(ID3D11DeviceContext* deviceContext)
		: BufferBase(GraphicsEngineSpace::BufferType::VERTEX)
		, deviceContext(deviceContext)
		, buffer(nullptr)
		, stride(0)
	{

	}

	VertexBuffer::~VertexBuffer()
	{
		if (buffer != nullptr)
		{
			buffer->Release();
		}
	}

	ID3D11Buffer* VertexBuffer::GetBuffer()
	{
		return buffer;
	}

	UINT VertexBuffer::GetStride()
	{
		return stride;
	}

	bool VertexBuffer::SetUpBuffer(unsigned int slot, void* data, ShaderType targetType)
	{
		if (buffer == nullptr)
			return false;

		UINT offset = 0;

		deviceContext->IASetVertexBuffers(slot, 1, &buffer, &stride, &offset);

		return true;
	}

	bool VertexBuffer::CreateBuffer(ID3D11Device* device, D3D11_USAGE usage, UINT CPUflag, UINT typeSize, void* vertices, UINT size)
	{
		D3D11_BUFFER_DESC bufferDescription;
		ZeroMemory(&bufferDescription, sizeof(D3D11_BUFFER_DESC));
		bufferDescription.Usage = usage;
		bufferDescription.ByteWidth = typeSize * size;
		bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDescription.CPUAccessFlags = CPUflag;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
		initData.pSysMem = vertices;

		HRESULT hr = device->CreateBuffer(&bufferDescription, &initData, &buffer);

		stride = typeSize;

		return SUCCEEDED(hr);
	}
}