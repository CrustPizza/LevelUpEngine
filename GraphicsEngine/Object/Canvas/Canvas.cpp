/********************************
*								*
*	Canvas.cpp					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
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
        for (auto iter : textUIList)
        {
            if (iter.second != nullptr)
                delete iter.second;
        }

        for (auto iter : textureUIList)
        {
            if (iter.second != nullptr)
                delete iter.second;
        }
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

    TextUI* Canvas::GetTextUI(const std::string& name)
    {
        auto result = textUIList.find(name);

        if (result == textUIList.end())
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

    void Canvas::Render(GraphicsEngineBase* engine)
    {
        for (auto iter : textureUIList)
        {
            if (iter.second != nullptr)
                iter.second->Render(engine);
        }

        for (auto iter : textUIList)
        {
            if (iter.second != nullptr)
                iter.second->Render(engine);
        }
    }
}