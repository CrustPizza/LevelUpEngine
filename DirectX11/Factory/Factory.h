/********************************
*								*
*	Factory.h					*
*								*
*	Created : 2022/06/17		*
*	Updated : 2022/08/17		*
*********************************/

#pragma once

#include <d3d11_1.h>
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
	using GraphicsEngineSpace::FontBase;
	using GraphicsEngineSpace::USAGE;
	using GraphicsEngineSpace::FilterOption;

	class Factory : public FactoryBase
	{
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
		DirectX::SpriteBatch* spriteBatch;
		ID3D11DepthStencilState* depthState;

	public:
		Factory(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~Factory();

		void SetSpriteBatch(DirectX::SpriteBatch* spriteBatch);
		void SetDepthState(ID3D11DepthStencilState* depthState);

		TextureBase* CreateTexture(const std::string& name, const std::string& path) override;
		LayoutBase* CreateLayout(const std::string& name) override;

		ShaderBase* CreateVertexShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel, LayoutBase* layout) override;
		ShaderBase* CreatePixelShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel) override;

		BufferBase* CreateVertexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size) override;
		BufferBase* CreateIndexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size) override;
		BufferBase* CreateConstantBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize) override;

		SamplerBase* CreateSampler(const std::string& name, FilterOption filter) override;
		FontBase* CreateFontObject(const std::string& name, const std::string& path) override;
	};
}