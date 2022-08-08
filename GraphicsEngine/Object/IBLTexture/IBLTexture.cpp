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
	{
		param.mipLevels[0] = 1;
		param.mipLevels[1] = 1;
		param.mipLevels[2] = 1;
		param.mipLevels[3] = 1;
	}

	IBLTexture::~IBLTexture()
	{

	}

	void IBLTexture::SetIBLTexture(TextureBase* radiance, TextureBase* irradiance, BufferBase* mipLevelCB)
	{
		this->radiance = radiance;
		this->irradiance = irradiance;

		this->mipLevelCB = mipLevelCB;
		param.mipLevels[0] = radiance->GetMipLevels() / 2;
		param.mipLevels[1] = radiance->GetMipLevels() / 2;
		param.mipLevels[2] = radiance->GetMipLevels() / 2;
		param.mipLevels[3] = radiance->GetMipLevels() / 2;
	}

	void IBLTexture::SetUpIBL(unsigned int mipLevelSlot, unsigned int radianceSlot, unsigned int irradianceSlot, ShaderType type)
	{
		if (radiance == nullptr || irradiance == nullptr)
			return;

		mipLevelCB->SetUpBuffer(mipLevelSlot, &param, type);
	
		radiance->SetUpTexture(radianceSlot, type);
		irradiance->SetUpTexture(irradianceSlot, type);
	}
}