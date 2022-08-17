/********************************
*								*
*	Factory Base.h				*
*								*
*	Created : 2022/06/20		*
*	Updated : 2022/07/08		*
*********************************/

#pragma once

#include <string>
#include "Define/GraphicsUsage.h"
#include "Define/GraphicsFilterOption.h"

namespace GraphicsEngineSpace
{
	class GraphicsEngine;

	class ModelBase;
	class TextureBase;
	class LayoutBase;
	class ShaderBase;
	class BufferBase;
	class PrefabBase;
	class SamplerBase;
	class FontBase;

	class FactoryBase
	{
	public:
		FactoryBase() = default;
		virtual ~FactoryBase() = default;

		virtual TextureBase* CreateTexture(const std::string& name, const std::string& path) abstract;
		virtual LayoutBase* CreateLayout(const std::string& name) abstract;

		virtual ShaderBase* CreateVertexShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel, LayoutBase* layout) abstract;
		virtual ShaderBase* CreatePixelShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel) abstract;

		virtual BufferBase* CreateVertexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size) abstract;
		virtual BufferBase* CreateIndexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size) abstract;
		virtual BufferBase* CreateConstantBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize) abstract;
	
		virtual SamplerBase* CreateSampler(const std::string& name, FilterOption filter) abstract;
		virtual FontBase* CreateFontObject(const std::string& name, const std::string& path) abstract;
	};
}