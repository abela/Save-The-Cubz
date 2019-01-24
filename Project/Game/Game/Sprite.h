//
//  Sprite.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/20/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef Sprite_h
#define Sprite_h

#include "GameObject.h"

namespace  game
{
    class Sprite : public GameObject
    {
    public:
        Sprite(const string textureFile, int posX, int posY, float rot, float scale);
        Sprite();
        Sprite(int posX, int posY, float rot, float scale);
        ~Sprite();
        
        int GetGridId();
        void SetGridId(int gridId);
        
        int GetColorId();
        void SetColorId(int colorId);
        // is mouse in sprite
        bool IsMouseInSprite(int mouseX, int mouseY);
        
        void SetCheckedAsAdjecent(bool checkedFlag);
        bool GetCheckedAsAdjecent();
        
        void SetRow(int row);
        void SetColumn(int column);
       
        int  GetRow();
        int  GetColumn();
        void Draw();
        void MoveToPosition(float frameDeltaTime);
        int  GetFallStepCounter();
        void UpdateStepFallCounter(bool reset);
        void SetGridSpriteRotation(bool moveGridSpriteRotation);
    private:
        int mColumn;
        int mRow;
        int m_colorId;
        int m_gridId;
        bool m_checkedAsAdjecent;
        bool m_moveGridSpriteRotation;
        int m_destroyRotationCounter;
        int mFallStepCounter;
        int mDestroyRotationSpeed;
        void DestroyAnimation(float frameDeltaTime);
        //
    };
}

#endif /* Sprite_hpp */
