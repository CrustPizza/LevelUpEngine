/********************************
*								*
*	Pixel Shader.h				*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/01		*
*********************************/

#pragma once

#include "../GraphicsEngine/Bases/ShaderBase.h"
#include <d3d11_1.h>

namespace DX11
{
	using GraphicsEngineSpace::ShaderBase;
	using GraphicsEngineSpace::Shader;

	class PixelShader : public ShaderBase
	{
		ID3D11DeviceContext* deviceContext;
		ID3D11PixelShader* shader;

	public:
		PixelShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3DBlob* shaderBlob);
		~PixelShader() override;

		bool SetUpShader() override;

		Shader* GetShader() override;

	private:
		bool CreateShader(ID3D11Device* device, ID3DBlob* shaderBlob);
	};
}