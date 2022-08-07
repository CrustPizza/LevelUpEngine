/********************************
*								*
*	Shader Base.h				*
*								*
*	Created : 2022/06/24		*
*	Updated : 2022/06/24		*
*********************************/

#pragma once

#include <string>
#include "Bases/ResourceBase.h"

namespace GraphicsEngineSpace
{
	enum class ShaderType
	{
		NONE,
		VERTEX,
		PIXEL
	};

	struct Shader
	{
		int unused;
	};

	class ShaderBase : public ResourceBase<ShaderBase>
	{
	protected:
		ShaderType type;

	public:
		ShaderBase(ShaderType type)
			: type(type) {}
		virtual ~ShaderBase() = default;

		virtual bool SetUpShader() abstract;
		virtual Shader* GetShader() abstract;
	};
}