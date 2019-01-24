//
//  UiButton.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/26/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "UiButton.h"

namespace ui {
    UiButton::UiButton(const string textureFile, int posX, int posY, float rot, float scale) :
    UiObject(textureFile, posX, posY, rot, scale), m_mouseButtonDown(false)
    {
        
    }
    UiButton::~UiButton()
    {
        
    }
    bool UiButton::ButtonDown()
    {
        m_mouseButtonDown = false;
        if(MouseIsInButton())
        {
            if(engine::EngineInstance().getMouseButtonDown())
            {
                if (engine::EngineInstance().GetMouseButtonDownFlag() == false)
                {
                    engine::EngineInstance().SetMouseButtonDownFlag(true);
                    m_mouseButtonDown = true;
                }
            }
        }
        //
        Draw();
        //
        return m_mouseButtonDown;
    }
    //
    void UiButton::Draw()
    {
        UiObject::Draw();
        MouseIsInButton();
    }
    //
    bool UiButton::MouseIsInButton()
    {
        int mouseX = engine::EngineInstance().GetMouseX();
        int mouseY = engine::EngineInstance().GetMouseY();
        //
        return ((mouseX > mCenterPoint.x - mTextureWidth/2) && (mouseX < mCenterPoint.x + mTextureWidth / 2) &&
                (mouseY > mCenterPoint.y - mTextureHeight / 2) && (mouseY < mCenterPoint.y + mTextureHeight / 2));
    }
    //
}
