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

		struct __declspec(align(16)) Parameter
		{
			int mipLevels[4];
		};

		BufferBase* mipLevelCB;
		TextureBase* radiance;
		TextureBase* irradiance;

		Parameter param;

	public:
		IBLTexture();
		~IBLTexture();

		void SetIBLTexture(TextureBase* radiance, TextureBase* irradiance, BufferBase* mipLevelCB);

		virtual void SetUpIBL(unsigned int mipLevelSlot, unsigned int radianceSlot, unsigned int irradianceSlot, ShaderType type);
	};
}