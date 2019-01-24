//
//  UiButton.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/26/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef UiButton_h
#define UiButton_h

#include "UiObject.h"

namespace ui {
    class UiButton : public UiObject
    {
    public:
        UiButton(const string textureFile, int posX, int posY, float rot, float scale);
        ~UiButton();
        bool ButtonDown();
    private:
        bool m_mouseButtonDown;
        bool MouseIsInButton();
        void Draw() override;
    };
}

#endif /* UiButton_hpp */
