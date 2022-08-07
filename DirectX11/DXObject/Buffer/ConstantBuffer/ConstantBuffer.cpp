/********************************
*								*
*	Constant Buffer.h			*
*								*
*	Created : 2022/07/02		*
*	Updated : 2022/07/20		*
*********************************/

#include "ConstantBuffer.h"

namespace DX11
{
	ConstantBuffer::ConstantBuffer(ID3D11DeviceContext* deviceContext)
		: BufferBase(GraphicsEngineSpace::BufferType::CONSTANT)
		, deviceContext(deviceContext)
		, buffer(nullptr)
		, size(0)
	{

	}

	ConstantBuffer::~ConstantBuffer()
	{
		if (buffer != nullptr)
		{
			buffer->Release();
		}
	}

	bool ConstantBuffer::SetUpBuffer(unsigned int slot, void* data, ShaderType targetType)
	{
		if (buffer == nullptr)
			return false;

		deviceContext->UpdateSubresource(buffer, 0, nullptr, data, size, 0);

		switch (targetType)
		{

		case ShaderType::VERTEX:
		{
			deviceContext->VSSetConstantBuffers(slot, 1, &buffer);

			return true;
		}

		case ShaderType::PIXEL:
		{
			deviceContext->PSSetConstantBuffers(slot, 1, &buffer);

			return true;
		}

		}

		return false;
	}

	bool ConstantBuffer::CreateBuffer(ID3D11Device* device, D3D11_USAGE usage, UINT CPUflag, UINT typeSize)
	{
		D3D11_BUFFER_DESC bufferDescription;
		ZeroMemory(&bufferDescription, sizeof(D3D11_BUFFER_DESC));
		bufferDescription.Usage = usage;
		bufferDescription.ByteWidth = typeSize;
		bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDescription.CPUAccessFlags = CPUflag;

		size = typeSize;

		HRESULT hr = device->CreateBuffer(&bufferDescription, nullptr, &buffer);

		return SUCCEEDED(hr);
	}
}