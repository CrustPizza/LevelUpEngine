/********************************
*								*
*	Vertex Shader.h				*
*								*
*	Created : 2022/06/29		*
*	Updated : 2022/06/29		*
*********************************/

#include "VertexShader.h"
#include <assert.h>

namespace DX11
{
	VertexShader::VertexShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3DBlob* shaderBlob, D3D11_INPUT_ELEMENT_DESC* layoutElements, UINT elementsSize)
		: ShaderBase(GraphicsEngineSpace::ShaderType::VERTEX)
		, deviceContext(deviceContext)
		, shader(nullptr)
		, layout(nullptr)
	{
		if (CreateShader(device, shaderBlob) != true)
		{
			// 抗寇 贸府
			assert(0);
		}

		if (CreateLayout(device, shaderBlob, layoutElements, elementsSize) != true)
		{
			// 抗寇 贸府
			assert(0);
		}
	}

	VertexShader::~VertexShader()
	{
		if (shader != nullptr)
			shader->Release();

		if (layout != nullptr)
			layout->Release();
	}

	bool VertexShader::SetUpShader()
	{
		deviceContext->VSSetShader(shader, nullptr, 0);
		deviceContext->IASetInputLayout(layout);

		return true;
	}

	Shader* VertexShader::GetShader()
	{
		return reinterpret_cast<Shader*>(shader);
	}

	bool VertexShader::CreateShader(ID3D11Device* device, ID3DBlob* shaderBlob)
	{
		HRESULT hr = device->CreateVertexShader
		(
			shaderBlob->GetBufferPointer(),
			shaderBlob->GetBufferSize(),
			nullptr,
			&shader
		);
		
		return SUCCEEDED(hr);
	}

	bool VertexShader::CreateLayout(ID3D11Device* device, ID3DBlob* shaderBlob, D3D11_INPUT_ELEMENT_DESC* layoutElements, UINT elementsSize)
	{
		HRESULT hr = device->CreateInputLayout
		(
			layoutElements,
			elementsSize,
			shaderBlob->GetBufferPointer(),
			shaderBlob->GetBufferSize(),
			&layout
		);

		return SUCCEEDED(hr);
	}
}