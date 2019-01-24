//
//  UiProgressBar.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/26/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "UiProgressBar.h"
#include "GameEngine.h"
using namespace engine;

namespace ui {
    //
    UiProgressBar::UiProgressBar(int posX,
                                 int posY,
                                 int width,
                                 int height,
                                 float percentage,
                                 SDL_Color FGColor) :
    UiObject(posX, posY,0,1), mPercentage(percentage), mInitialTextureWidth(width)
    {
        mTextureWidth = width;
        mTextureHeight = height;
        mPercentage = percentage;
        this->FGColor = FGColor;
        //
    }
    //
    UiProgressBar::~UiProgressBar()
    {
        mDestroyed = true;
    }
    
    int UiProgressBar::GetInitialWidth()
    {
        return mInitialTextureWidth;
    }
    //
    void UiProgressBar::SetProgress(int progress)
    {
        mTextureWidth = progress;
    }
    //
    void UiProgressBar::Draw()
    {
        SDL_Rect fgrect = { mCenterPoint.x, mCenterPoint.y, mTextureWidth, mTextureHeight };
        //
        SDL_SetRenderDrawColor(EngineInstance().GetRenderer(), FGColor.r, FGColor.g, FGColor.b, FGColor.a);
        //
        SDL_RenderFillRect(EngineInstance().GetRenderer(), &fgrect);
        //
    }
    
}
