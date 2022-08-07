/********************************
*								*
*	Texture Base.h				*
*								*
*	Created : 2022/06/17		*
*	Updated : 2022/07/28		*
*********************************/

#pragma once

#include "Bases/ResourceBase.h"
#include "Bases/ShaderBase.h"

namespace GraphicsEngineSpace
{
	struct Texture
	{
		int unused;
	};

	class TextureBase : public ResourceBase<TextureBase>
	{
	public:
		TextureBase() = default;
		virtual ~TextureBase() = default;

		virtual unsigned int GetMipLevels() abstract;
		virtual Texture* GetTexture() abstract;
		virtual bool SetUpTexture(unsigned int slot, ShaderType targetType) abstract;
	};
}