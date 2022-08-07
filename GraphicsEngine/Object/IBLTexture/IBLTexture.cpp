/********************************
*								*
*	IBL Texture.h				*
*								*
*	Created : 2022/08/07		*
*	Updated : 2022/08/07		*
*********************************/

#include "IBLTexture.h"

namespace GraphicsEngineSpace
{
	IBLTexture::IBLTexture()
		: mipLevelCB(nullptr)
		, radiance(nullptr)
		, irradiance(nullptr)
		, mipLevels(1)
	{

	}

	IBLTexture::~IBLTexture()
	{

	}

	void IBLTexture::SetIBLTexture(TextureBase* radiance, TextureBase* irradiance)
	{
		this->radiance = radiance;
		this->irradiance = irradiance;

		mipLevels = radiance->GetMipLevels();
	}

	void IBLTexture::SetUpIBL(unsigned int mipLevelSlot, unsigned int radianceSlot, unsigned int irradianceSlot, ShaderType type)
	{
		if (radiance == nullptr || irradiance == nullptr)
			return;

		mipLevelCB->SetUpBuffer(mipLevelSlot, &mipLevels, type);
	
		radiance->SetUpTexture(radianceSlot, type);
		irradiance->SetUpTexture(irradianceSlot, type);
	}
}