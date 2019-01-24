//
//  UiProgressBar.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/26/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef UiProgressBar_h
#define UiProgressBar_h

#include "UiObject.h"

namespace ui {
    class UiProgressBar : public UiObject
    {
    public:
        UiProgressBar(int posX,
                      int posY,
                      int width,
                      int height,
                      float percentage,
                      SDL_Color FGColor);
        ~UiProgressBar();
        
        int GetInitialWidth();
        void SetProgress(int progress);
        void Draw() override;
    private:
        int mInitialTextureWidth;
        int mPercentage;
        SDL_Color FGColor;
        SDL_Color BGColor;
    };
}

#endif /* UiProgressBar_h */
