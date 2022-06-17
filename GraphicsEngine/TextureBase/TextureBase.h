/********************************
*								*
*	Texture Base.h				*
*								*
*	Created : 2022/06/17		*
*	Updated : 2022/06/17		*
*********************************/

#pragma once

template<class T>
class TextureBase
{
protected:
	T* texture;

public:
	T* GetTexture()
	{
		return texture;
	}
};