//
//  Sprite.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/20/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "Sprite.h"
#include "GameEngine.h"
using namespace engine;

namespace game {
    Sprite::Sprite(const string textureFile, int posX, int posY, float rot, float scale)
    : GameObject(textureFile, posX,posY,rot, scale) ,
    m_colorId(-1), mColumn(-1), mRow(-1), m_checkedAsAdjecent(false), m_gridId(-1), mFallStepCounter(0), mDestroyRotationSpeed(Constants::SPRITE_DESTROY_ROT_SPEED),m_moveGridSpriteRotation(false),m_destroyRotationCounter(0)
    {
    }
    Sprite::Sprite() : GameObject()
    {
        
    }
    Sprite::Sprite(int posX, int posY, float rot, float scale) : GameObject(posX,posY, rot, scale)
    {
        
    }
    Sprite::~Sprite()
    {
        
    }
    
    int Sprite::GetGridId()
    {
        return m_gridId;
    }
    
    void Sprite::SetGridId(int gridId)
    {
        m_gridId = gridId;
    }
    
    int Sprite::GetColorId()
    {
        return m_colorId;
    }
    void Sprite::SetColorId(int colorId)
    {
        m_colorId = colorId;
    }
    
    void Sprite::SetCheckedAsAdjecent(bool checkedFlag)
    {
        m_checkedAsAdjecent = checkedFlag;
    }
    
    bool Sprite::GetCheckedAsAdjecent()
    {
        return m_checkedAsAdjecent;
    }
    
    void Sprite::SetRow(int row)
    {
        this->mRow = row;
    }
    
    void Sprite::SetColumn(int column)
    {
        this->mColumn = column;
    }
    
    int Sprite::GetRow()
    {
        return mRow;
    }
    
    int Sprite::GetColumn()
    {
        return mColumn;
    }
    
    bool Sprite::IsMouseInSprite(int mouseX, int mouseY)
    {
        return ((mouseX > mCenterPoint.x - mTextureWidth /2) && (mouseX < mCenterPoint.x + mTextureWidth / 2) &&
                (mouseY > mCenterPoint.y - mTextureHeight / 2) && (mouseY < mCenterPoint.y + mTextureHeight / 2));
    }
    
    void Sprite::Draw()
    {
        GameObject::Draw();
        if(mMoving)
            MoveToPosition(EngineInstance().Instance().GetLastFrameTime());
        DestroyAnimation(EngineInstance().Instance().GetLastFrameTime());
    }
    
    int Sprite::GetFallStepCounter()
    {
        return mFallStepCounter;
    }
    
    void Sprite::UpdateStepFallCounter(bool reset)
    {
        mFallStepCounter = (reset == true) ? 0 : mFallStepCounter+1;
    }
    
    void Sprite::SetGridSpriteRotation(bool moveGridSpriteRotation)
    {
        m_moveGridSpriteRotation = moveGridSpriteRotation;
    }
    
    void Sprite::MoveToPosition(float frameDeltaTime)
    {
        GameObject::MoveToPosition(frameDeltaTime);
        if(mMoving)
            mRotatation+=frameDeltaTime * mDestroyRotationSpeed;
        if(mRotatation>90)
        {
            mRotatation = 0;
            m_moveGridSpriteRotation = false;
        }
    }
    void Sprite::DestroyAnimation(float frameDeltaTime)
    {
        if(m_gridId == -2)
        {
            mRotatation+=frameDeltaTime * mDestroyRotationSpeed;
            m_destroyRotationCounter += frameDeltaTime * mDestroyRotationSpeed;
            if(m_destroyRotationCounter>60)
            {
                m_gridId = -1;
            }
        }
    }
}
