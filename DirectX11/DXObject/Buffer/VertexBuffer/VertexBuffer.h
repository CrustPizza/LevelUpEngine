/********************************
*								*
*	Vertex Buffer.h				*
*								*
*	Created : 2022/07/02		*
*	Updated : 2022/07/20		*
*********************************/

#pragma once

#include "../GraphicsEngine/Bases/BufferBase.h"
#include <d3d11_1.h>

namespace DX11
{
	using GraphicsEngineSpace::BufferBase;
	using GraphicsEngineSpace::ShaderType;

	class BufferBuilder;

	class VertexBuffer : public BufferBase
	{
		ID3D11DeviceContext* deviceContext;
		ID3D11Buffer* buffer;
		UINT stride;

	public:
		VertexBuffer(ID3D11DeviceContext* deviceContext);
		~VertexBuffer() override;

		ID3D11Buffer* GetBuffer();
		UINT GetStride();

		bool SetUpBuffer(unsigned int slot, void* data, ShaderType targetType) override;

	private:
		bool CreateBuffer(ID3D11Device* device, D3D11_USAGE usage, UINT CPUflag, UINT typeSize, void* vertices, UINT size);

		friend BufferBuilder;
	};
}