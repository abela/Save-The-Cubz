//
//  UiObject.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/26/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "UiObject.h"

namespace ui
{
    UiObject::UiObject(const string textureFile, int posX, int posY, float rot, float scale) :
    GameObject(textureFile,posX, posY, rot, scale)
    {
        
    }
    //
    UiObject::UiObject(int posX, int posY, float rot, float scale) : GameObject(posY,posY,rot,scale)
    {
        
    }
    //
    UiObject::~UiObject()
    {
        
    }
    //
    void UiObject::Draw()
    {
        GameObject::Draw();
    }
    //
}
