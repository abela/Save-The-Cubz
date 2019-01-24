//
//  UiObject.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/26/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef UiObject_h
#define UiObject_h

#include "GameObject.h"
using namespace game;

namespace ui
{
    class UiObject : public GameObject
    {
    public:
        UiObject(const string textureFile, int posX, int posY, float rot, float scale);
        UiObject(int posX, int posY, float rot, float scale);
        virtual ~UiObject();
        void Draw() override;
    };
}

#endif /* UiObject_h */
