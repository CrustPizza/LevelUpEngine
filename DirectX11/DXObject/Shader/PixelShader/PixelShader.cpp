/********************************
*								*
*	Pixel Shader.cpp			*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/01		*
*********************************/

#include "PixelShader.h"
#include <assert.h>

namespace DX11
{
	PixelShader::PixelShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3DBlob* shaderBlob)
		: ShaderBase(GraphicsEngineSpace::ShaderType::PIXEL)
		, deviceContext(deviceContext)
		, shader(nullptr)
	{
		if (CreateShader(device, shaderBlob) != true)
		{
			// 예외 처리
			assert(0);
		}
	}

	PixelShader::~PixelShader()
	{
		if (shader != nullptr)
			shader->Release();
	}

	bool PixelShader::SetUpShader()
	{
		deviceContext->PSSetShader(shader, nullptr, 0);

		return true;
	}

	Shader* PixelShader::GetShader()
	{
		return reinterpret_cast<Shader*>(shader);
	}

	bool PixelShader::CreateShader(ID3D11Device* device, ID3DBlob* shaderBlob)
	{
		HRESULT hr = device->CreatePixelShader
		(
			shaderBlob->GetBufferPointer(),
			shaderBlob->GetBufferSize(),
			nullptr,
			&shader
		);

		return SUCCEEDED(hr);
	}
}