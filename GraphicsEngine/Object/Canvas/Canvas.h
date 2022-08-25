/********************************
*								*
*	Canvas.h					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/10		*
*********************************/

#pragma once

#include <map>
#include "Object/TextUI/TextUI.h"
#include "Object/ButtonUI/ButtonUI.h"
#include "Object/TextureUI/TextureUI.h"
#include "Object/ProgressBar/ProgressBar.h"
#include "Object/SpriteAnimationUI/SpriteAnimationUI.h"

namespace GraphicsEngineSpace
{
	class Canvas : public UIBase
	{
		std::map<std::string, TextUI*> textUIList;
		std::map<std::string, Canvas*> canvasList;
		std::map<std::string, ButtonUI*> buttonUIList;
		std::map<std::string, TextureUI*> textureUIList;
		std::map<std::string, ProgressBar*> progressBarList;
		std::map<std::string, SpriteAnimationUI*> SpriteAnimationUIList;

	public:
		Canvas(float width, float height);
		~Canvas();

		virtual TextUI* CreateTextUI(const std::string& name);
		virtual Canvas* CreateCanvas(const std::string& name);
		virtual ButtonUI* CreateButtonUI(const std::string& name);
		virtual TextureUI* CreateTextureUI(const std::string& name);
		virtual ProgressBar* CreateProgressBar(const std::string& name);
		virtual SpriteAnimationUI* CreateSpriteAnimationUI(const std::string& name);

		virtual TextUI* GetTextUI(const std::string& name);
		virtual Canvas* GetCanvas(const std::string& name);
		virtual ButtonUI* GetButtonUI(const std::string& name);
		virtual TextureUI* GetTextureUI(const std::string& name);
		virtual ProgressBar* GetProgressBar(const std::string& name);
		virtual SpriteAnimationUI* GetSpriteAnimationUI(const std::string& name);

		virtual ButtonUI* CollidedButtonWithMouse(float mouseX, float mouseY, bool isClicked);
		virtual void SetScaleAllCanvas(Vector scale);

		void Render(GraphicsEngineBase* engine, float tick = 0.0f) override;
		virtual void Release();

	private:
		ButtonUI* FindCollidedButton(float mouseX, float mouseY, bool isClicked);
	};
}