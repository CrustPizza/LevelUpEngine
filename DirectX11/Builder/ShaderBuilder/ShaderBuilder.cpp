/********************************
*								*
*	Shader Builder.cpp			*
*								*
*	Created : 2022/06/27		*
*	Updated : 2022/06/27		*
*********************************/

#include "ShaderBuilder.h"

namespace DX11
{
	ShaderBuilder::ShaderBuilder(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
		: device(device)
		, deviceContext(deviceContext)
		, shaderBlob(nullptr)
	{

	}

	ShaderBuilder::~ShaderBuilder()
	{
		if (shaderBlob != nullptr)
			shaderBlob->Release();
	}

	bool ShaderBuilder::CompileShaderFromFile(const TCHAR* path, const char* entryName, const char* shaderModel, ID3DBlob** blobOut)
	{
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
		dwShaderFlags |= D3DCOMPILE_DEBUG;

		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		ID3DBlob* errorBlob = nullptr;

		HRESULT hr = D3DCompileFromFile(
			path,
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entryName,
			shaderModel,
			dwShaderFlags,
			0,
			blobOut,
			&errorBlob);

		if (FAILED(hr) == true)
		{
			if (errorBlob != nullptr)
			{
				OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
				errorBlob->Release();
			}

			return false;
		}

		if (errorBlob != nullptr)
			errorBlob->Release();

		return true;
	}
}