/********************************
*								*
*	IBL Texture.h				*
*								*
*	Created : 2022/08/07		*
*	Updated : 2022/08/07		*
*********************************/

#pragma once

#include "Bases/BufferBase.h"
#include "Bases/TextureBase.h"
#include "Bases/ResourceBase.h"

namespace GraphicsEngineSpace
{
	class IBLTexture : public ResourceBase<IBLTexture>
	{
		BufferBase* mipLevelCB;
		TextureBase* radiance;
		TextureBase* irradiance;

		int mipLevels;

	public:
		IBLTexture();
		~IBLTexture();

		void SetIBLTexture(TextureBase* radiance, TextureBase* irradiance);

		void SetUpIBL(unsigned int mipLevelSlot, unsigned int radianceSlot, unsigned int irradianceSlot, ShaderType type);
	};
}