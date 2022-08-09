/********************************
*								*
*	Canvas.h					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#pragma once

#include <map>
#include "Object/TextUI/TextUI.h"
#include "Object/TextureUI/TextureUI.h"

namespace GraphicsEngineSpace
{
	class Canvas : public UIBase
	{
		std::map<std::string, TextUI*> textUIList;
		std::map<std::string, TextureUI*> textureUIList;

	public:
		Canvas(float width, float height);
		~Canvas();

		virtual TextUI* CreateTextUI(const std::string& name);
		virtual TextureUI* CreateTextureUI(const std::string& name);

		virtual TextUI* GetTextUI(const std::string& name);
		virtual TextureUI* GetTextureUI(const std::string& name);

		virtual void Render(GraphicsEngineBase* engine);
	};
}