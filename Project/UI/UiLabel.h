//
//  UiLabel.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/27/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef UiLabel_h
#define UiLabel_h
#include "SDL_ttf.h"
#include "UiObject.h"

namespace ui {
    class UiLabel : public UiObject
    {
    public:
        UiLabel(const char *fontName,
                const char *value,
                SDL_Rect rect,
                int rot,
                int scale,
                int fontSize,
                SDL_Color fontColor);
        ~UiLabel();
        void Draw() override;
        void SetText(const char *value);
    private:
        SDL_Texture *text;
        SDL_Rect rect;
        TTF_Font* font;
        SDL_Color fontColor;
    };
}

#endif /* UiLabel_h */
