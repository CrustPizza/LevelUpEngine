/********************************
*								*
*	Vertex Shader.h				*
*								*
*	Created : 2022/06/29		*
*	Updated : 2022/06/29		*
*********************************/

#pragma once

#include "../GraphicsEngine/Bases/ShaderBase.h"
#include <d3d11_1.h>

namespace DX11
{
	using GraphicsEngineSpace::ShaderBase;
	using GraphicsEngineSpace::Shader;
	
	class VertexShader : public ShaderBase
	{
		ID3D11DeviceContext* deviceContext;
		ID3D11VertexShader* shader;
		ID3D11InputLayout* layout;

	public:
		VertexShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3DBlob* shaderBlob, D3D11_INPUT_ELEMENT_DESC* layoutElements, UINT elementsSize);
		~VertexShader() override;

		bool SetUpShader() override;

		Shader* GetShader() override;

	private:
		bool CreateShader(ID3D11Device* device, ID3DBlob* shaderBlob);
		bool CreateLayout(ID3D11Device* device, ID3DBlob* shaderBlob, D3D11_INPUT_ELEMENT_DESC* layoutElements, UINT elementsSize);
	};
}