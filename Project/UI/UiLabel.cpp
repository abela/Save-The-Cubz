//
//  UiLabel.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/27/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "UiLabel.h"

#include "GameEngine.h"
using namespace engine;

namespace ui {
    UiLabel::UiLabel(const char *fontName,
                     const char *value,
                     SDL_Rect rect,
                     int rot,
                     int scale,
                     int fontSize,
                     SDL_Color fontColor) :
    UiObject(rect.x,rect.y,rot,scale)
    {
        this->fontColor = fontColor;
        this->rect = rect;
        font = TTF_OpenFont(fontName, 24);
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, value, fontColor);
        mTextureToDraw = SDL_CreateTextureFromSurface(EngineInstance().GetRenderer(), surfaceMessage);
        SDL_FreeSurface(surfaceMessage);
    }
    
    UiLabel::~UiLabel()
    {
        
    }
    
    void UiLabel::SetText(const char *value)
    {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, value, fontColor);
        mTextureToDraw = SDL_CreateTextureFromSurface(EngineInstance().GetRenderer(), surfaceMessage);
        SDL_FreeSurface(surfaceMessage);
    }
    
    void UiLabel::Draw()
    {
         SDL_RenderCopy(EngineInstance().GetRenderer(), mTextureToDraw, NULL, &rect);
    }
}
