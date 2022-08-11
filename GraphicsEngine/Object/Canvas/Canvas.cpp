/********************************
*								*
*	Canvas.cpp					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/10		*
*********************************/

#include "Canvas.h"

namespace GraphicsEngineSpace
{
    Canvas::Canvas(float width, float height)
    {
        this->width = width;
        this->height = height;

        anchor.hLocation = HorizontalLocation::LEFT;
        anchor.vLocation = VerticalLocation::TOP;

        pivot.hLocation = HorizontalLocation::LEFT;
        pivot.vLocation = VerticalLocation::TOP;
    }

    Canvas::~Canvas()
    {
        Release();
    }

    TextUI* Canvas::CreateTextUI(const std::string& name)
    {
        std::string newUIName = name;
        int ID = 1;

        while (textUIList.find(newUIName) != textUIList.end())
        {
            newUIName = name + std::to_string(ID++);
        }

        TextUI* newTextUI = new TextUI;

        newTextUI->SetParent(this);
        newTextUI->SetWidth(this->width / 4);
        newTextUI->SetHeight(this->height / 4);

        textUIList[newUIName] = newTextUI;

        return textUIList[newUIName];
    }

    Canvas* Canvas::CreateCanvas(const std::string& name)
    {
        std::string newUIName = name;
        int ID = 1;

        while (canvasList.find(newUIName) != canvasList.end())
        {
            newUIName = name + std::to_string(ID++);
        }

        Canvas* newCanvas = new Canvas(width, height);

        newCanvas->SetParent(this);

        canvasList[newUIName] = newCanvas;

        return canvasList[newUIName];
    }

    ButtonUI* Canvas::CreateButtonUI(const std::string& name)
    {
        std::string newUIName = name;
        int ID = 1;

        while (buttonUIList.find(newUIName) != buttonUIList.end())
        {
            newUIName = name + std::to_string(ID++);
        }

        ButtonUI* newButtonUI = new ButtonUI;

        newButtonUI->SetParent(this);
        newButtonUI->SetWidth(this->width / 4);
        newButtonUI->SetHeight(this->height / 4);

        buttonUIList[newUIName] = newButtonUI;

        return buttonUIList[newUIName];
    }

    TextureUI* Canvas::CreateTextureUI(const std::string& name)
    {
        std::string newUIName = name;
        int ID = 1;

        while (textureUIList.find(newUIName) != textureUIList.end())
        {
            newUIName = name + std::to_string(ID++);
        }

        TextureUI* newTextureUI = new TextureUI;

        newTextureUI->SetParent(this);
        newTextureUI->SetWidth(this->width / 4);
        newTextureUI->SetHeight(this->height / 4);

        textureUIList[newUIName] = newTextureUI;

        return textureUIList[newUIName];
    }

    ProgressBar* Canvas::CreateProgressBar(const std::string& name)
    {
        std::string newUIName = name;
        int ID = 1;

        while (progressBarList.find(newUIName) != progressBarList.end())
        {
            newUIName = name + std::to_string(ID++);
        }

        ProgressBar* newProgressBar = new ProgressBar;

        newProgressBar->SetParent(this);
        newProgressBar->SetWidth(this->width / 4);
        newProgressBar->SetHeight(this->height / 4);

        progressBarList[newUIName] = newProgressBar;

        return progressBarList[newUIName];
    }

    TextUI* Canvas::GetTextUI(const std::string& name)
    {
        auto result = textUIList.find(name);

        if (result == textUIList.end())
            return nullptr;

        return result->second;
    }

    Canvas* Canvas::GetCanvas(const std::string& name)
    {
        auto result = canvasList.find(name);

        if (result == canvasList.end())
            return nullptr;

        return result->second;
    }

    ButtonUI* Canvas::GetButtonUI(const std::string& name)
    {
        auto result = buttonUIList.find(name);

        if (result == buttonUIList.end())
            return nullptr;

        return result->second;
    }

    TextureUI* Canvas::GetTextureUI(const std::string& name)
    {
        auto result = textureUIList.find(name);

        if (result == textureUIList.end())
            return nullptr;

        return result->second;
    }

    ProgressBar* Canvas::GetProgressBar(const std::string& name)
    {
        auto result = progressBarList.find(name);

        if (result == progressBarList.end())
            return nullptr;

        return result->second;
    }

    ButtonUI* Canvas::CollidedButtonWithMouse(float mouseX, float mouseY, bool isClicked)
    {
        ButtonUI* collidedButton = nullptr;
        float minZ = 1.0f;

        for (auto iter : buttonUIList)
        {
            if (iter.second == nullptr || iter.second->isEnable != true)
                continue;

            auto buttonScreenPosition = iter.second->GetScreenPosition();

            if (mouseX < buttonScreenPosition.x || mouseY < buttonScreenPosition.y)
            {
                iter.second->buttonState = ButtonState::DEFAULT;
                continue;
            }

            if (mouseX > buttonScreenPosition.x + iter.second->GetWidth() ||
                mouseY > buttonScreenPosition.y + iter.second->GetHeight())
            {
                iter.second->buttonState = ButtonState::DEFAULT;
                continue;
            }

            if (buttonScreenPosition.z <= minZ)
            {
                collidedButton = iter.second;
                minZ = buttonScreenPosition.z;
            }
        }

        if (collidedButton == nullptr)
            return nullptr;

        if (isClicked == true)
        {
            if (collidedButton->buttonState == ButtonState::DOWN)
                collidedButton->buttonState = ButtonState::PRESS;
            else if (collidedButton->buttonState != ButtonState::PRESS)
                collidedButton->buttonState = ButtonState::DOWN;
        }
        else
        {
            if (collidedButton->buttonState == ButtonState::DOWN ||
                collidedButton->buttonState == ButtonState::PRESS)
                collidedButton->buttonState = ButtonState::UP;
            else
                collidedButton->buttonState = ButtonState::HOVER;
        }

        return collidedButton;
    }

    void Canvas::Render(GraphicsEngineBase* engine)
    {
        if (isEnable != true || engine == nullptr)
            return;

        for (auto* iter : child)
        {
            if (iter != nullptr)
                iter->Render(engine);
        }
    }

    void Canvas::Release()
    {
        for (auto iter : textUIList)
        {
            if (iter.second != nullptr)
                delete iter.second;
        }

        textUIList.clear();

        for (auto iter : canvasList)
        {
            if (iter.second != nullptr)
                delete iter.second;
        }

        canvasList.clear();

        for (auto iter : buttonUIList)
        {
            if (iter.second != nullptr)
                delete iter.second;
        }

        buttonUIList.clear();

        for (auto iter : textureUIList)
        {
            if (iter.second != nullptr)
                delete iter.second;
        }

        textureUIList.clear();

        for (auto iter : progressBarList)
        {
            if (iter.second != nullptr)
                delete iter.second;
        }

        progressBarList.clear();

        child.clear();
    }
}