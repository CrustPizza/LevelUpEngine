/********************************
*								*
*	Shader Builder.h			*
*								*
*	Created : 2022/06/27		*
*	Updated : 2022/06/27		*
*********************************/

#pragma once

#include <vector>
#include <string>
#include <d3d11_1.h>
#include <d3dcompiler.h>

namespace DX11
{
	class ShaderBuilder
	{
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
		ID3DBlob* shaderBlob;

	public:
		ShaderBuilder(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		~ShaderBuilder();

		template<typename T, typename ...Types>
		T* CreateShader(const std::string& path, const std::string& entryName, const std::string& shaderModel, Types ...args);

	private:
		bool CompileShaderFromFile(const TCHAR* path, const char* entryName, const char* shaderModel, ID3DBlob** blobOut);
	};

	template<typename T, typename ...Types>
	inline T* ShaderBuilder::CreateShader(const std::string& path, const std::string& entryName, const std::string& shaderModel, Types ...args)
	{
		if (shaderBlob != nullptr)
		{
			shaderBlob->Release();
			shaderBlob = nullptr;
		}

		std::wstring wpath;

		wpath.assign(path.begin(), path.end());

		if (CompileShaderFromFile(wpath.c_str(), entryName.c_str(), shaderModel.c_str(), &shaderBlob) != true)
			return nullptr;

		T* newShader = new T(device, deviceContext, shaderBlob, args...);

		if (newShader == nullptr)
		{
			// 예외 처리
			assert(0);
		}

		return newShader;
	}
}