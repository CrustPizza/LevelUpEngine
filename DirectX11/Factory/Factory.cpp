/********************************
*								*
*	Factory.cpp					*
*								*
*	Created : 2022/06/17		*
*	Updated : 2022/07/26		*
*********************************/

#include "Factory.h"

#include "Builder/BufferBuilder/BufferBuilder.h"
#include "Builder/SamplerBuilder/SamplerBuilder.h"
#include "Builder/ShaderBuilder/ShaderBuilder.h"
#include "Builder/TextureBuilder/TextureBuilder.h"

#include "DXObject/Shader/VertexShader/VertexShader.h"
#include "DXObject/Shader/PixelShader/PixelShader.h"

#include "DXObject/Layout/Layout.h"

#include "DXObject/Buffer/VertexBuffer/VertexBuffer.h"
#include "DXObject/Buffer/IndexBuffer/IndexBuffer.h"
#include "DXObject/Buffer/ConstantBuffer/ConstantBuffer.h"

#include "FormatConverter/FormatConverter.h"

namespace DX11
{
	Factory::Factory(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
		: device(device)
		, deviceContext(deviceContext)
	{

	}

	Factory::~Factory()
	{

	}

	TextureBase* Factory::CreateTexture(const std::string& name, const std::string& path)
	{
		TextureBuilder builder(device, deviceContext);

		TextureBase* newTexture = builder.CreateTexture(path);

		return newTexture;
	}

	LayoutBase* Factory::CreateLayout(const std::string& name)
	{
		LayoutBase* newLayout = new Layout;

		return newLayout;
	}

	ShaderBase* Factory::CreateVertexShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel, LayoutBase* layout)
	{
		ShaderBuilder builder(device, deviceContext);

		ShaderBase* newShader = builder.CreateShader<VertexShader>(path, entryName, shaderModel, reinterpret_cast<D3D11_INPUT_ELEMENT_DESC*>(layout->GetLayout()), layout->GetLayoutSize());

		return newShader;
	}

	ShaderBase* Factory::CreatePixelShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel)
	{
		ShaderBuilder builder(device, deviceContext);

		ShaderBase* newShader = builder.CreateShader<PixelShader>(path, entryName, shaderModel);

		return newShader;
	}

	BufferBase* Factory::CreateVertexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size)
	{
		BufferBuilder builder(device, deviceContext);

		BufferBase* newBuffer = builder.CreateBuffer<VertexBuffer>(GetDxUsage(usage), CPUflag, typeSize, dataPtr, size);

		return newBuffer;
	}

	BufferBase* Factory::CreateIndexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size)
	{
		BufferBuilder builder(device, deviceContext);

		BufferBase* newBuffer = builder.CreateBuffer<IndexBuffer>(GetDxUsage(usage), CPUflag, typeSize, dataPtr, size);

		return newBuffer;
	}

	BufferBase* Factory::CreateConstantBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize)
	{
		BufferBuilder builder(device, deviceContext);

		BufferBase* newBuffer = builder.CreateBuffer<ConstantBuffer>(GetDxUsage(usage), CPUflag, typeSize);

		return newBuffer;
	}

	SamplerBase* Factory::CreateSampler(const std::string& name, FilterOption filter)
	{
		SamplerBuilder builder(device, deviceContext);

		SamplerBase* newSampler = builder.CreateSampler(GetDxFilter(filter));

		return newSampler;
	}
}