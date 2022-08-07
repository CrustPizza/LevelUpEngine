/********************************
*								*
*	Factory.h					*
*								*
*	Created : 2022/06/17		*
*	Updated : 2022/07/26		*
*********************************/

#pragma once

#include <string>
#include "DXObject/DXObjectBase.h"
#include "DXObject/RenderTexture/RenderTexture.h"
#include "../GraphicsEngine/Bases/FactoryBase.h"

namespace DX11
{
	using GraphicsEngineSpace::FactoryBase;
	using GraphicsEngineSpace::TextureBase;
	using GraphicsEngineSpace::LayoutBase;
	using GraphicsEngineSpace::ShaderBase;
	using GraphicsEngineSpace::BufferBase;
	using GraphicsEngineSpace::SamplerBase;
	using GraphicsEngineSpace::USAGE;
	using GraphicsEngineSpace::FilterOption;

	class Factory : public FactoryBase
	{
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;

	public:
		Factory(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~Factory();

		TextureBase* CreateTexture(const std::string& name, const std::string& path) override;
		LayoutBase* CreateLayout(const std::string& name) override;

		ShaderBase* CreateVertexShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel, LayoutBase* layout) override;
		ShaderBase* CreatePixelShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel) override;

		BufferBase* CreateVertexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size) override;
		BufferBase* CreateIndexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size) override;
		BufferBase* CreateConstantBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize) override;

		SamplerBase* CreateSampler(const std::string& name, FilterOption filter) override;
	};
}