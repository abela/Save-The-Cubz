//
//  GameObject.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/19/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "GameObject.h"
namespace  game
{
    GameObject::GameObject(const string textureFile,int posX, int posY, float rot, float scale) : mMoving(false),
    mMoveSpeed(0), mNewPosition({0,0}), mDestroyed(false)
    {
        mStartPosition = {posX, posY};
        mCenterPoint = {posX, posY};
        SDL_Surface *surface = IMG_Load(textureFile.c_str());
        mTextureToDraw = SDL_CreateTextureFromSurface(engine::EngineInstance().GetRenderer(), surface);
        SDL_QueryTexture(mTextureToDraw, NULL, NULL, &mTextureWidth, &mTextureHeight);
        SDL_FreeSurface(surface);
        surface = NULL;
        mRotatation = rot;
        mScale = scale;
    }
    
    GameObject::GameObject()
    {
        
    }
    
    GameObject::GameObject(int posX, int posY, float rot, float scale)
    {
        mCenterPoint = {posY, posY};
        mRotatation = rot;
        mScale = scale;
    }
    
    GameObject::~GameObject()
    {
        if(mDestroyed == false)
        {
            mDestroyed = true;
            SDL_DestroyTexture(mTextureToDraw);
            mTextureToDraw = NULL;
        }
        
    }
    
    void GameObject::SetNewStartPosition(int x,int y)
    {
        mStartPosition = {x,y};
    }
    
    SDL_Point GameObject::GetStartPosition()
    {
        return mStartPosition;
    }
    
    void GameObject::SetPosition(int posX,int posY)
    {
        mCenterPoint = {posX, posY};
    }
    
    void GameObject::SetRotation(float rot)
    {
        mRotatation = rot;
    }
    
    void GameObject::SetScale(float scale)
    {
        mScale = scale;
    }
    
    void GameObject::SetTextureToDraw(SDL_Texture *texture)
    {
        mTextureToDraw = texture;
    }
    
    void GameObject::SetMoving(bool move, int dirX, int dirY)
    {
        mMoving = move;
        mNewPosition = {dirX, dirY};
    }
    
    SDL_Point GameObject::GetNewPosition() const
    {
        return mNewPosition;
    }
    
    void GameObject::SetMoveSpeed(int moveSpeed)
    {
        mMoveSpeed = moveSpeed;
    }
    
    int GameObject::GetMoveSpeed()
    {
        return mMoveSpeed;
    }
    
    SDL_Point GameObject::GetPosition()
    {
        return mCenterPoint;
    }
    
    float GameObject::GetRotation()
    {
        return mRotatation;
    }
    
    float GameObject::GetScale()
    {
        return mScale;
    }
    
    bool GameObject::Getmoving()
    {
        return mMoving;
    }
    
    SDL_Texture* GameObject::GetTexture()
    {
        return mTextureToDraw;
    }
    //
    void GameObject::Draw()
    {
        //
        SDL_Rect rect = {mCenterPoint.x - mTextureWidth/2,
                         mCenterPoint.y - mTextureHeight/2,
                        mTextureWidth * mScale,mTextureHeight * mScale};
        //
        SDL_RenderCopyEx(engine::EngineInstance().GetRenderer(),
                         mTextureToDraw,
                         NULL,
                         &rect,
                         mRotatation,
                         NULL,
                         SDL_FLIP_NONE);
        //
    }
    //
    void GameObject::MoveToPosition(float frameDeltaTime)
    {
        if (mMoving)
        {
            // prevent position comparing, adjust position by minimum distance
            int modDelta = 1;
            SDL_Point movePoint = {mNewPosition.x - mCenterPoint.x, mNewPosition.y - mCenterPoint.y};
            int length = sqrt(movePoint.x * movePoint.x + movePoint.y * movePoint.y);
            if(length > 0)
            {
                movePoint = {movePoint.x / length, movePoint.y / length};
                //
                mCenterPoint = {mCenterPoint.x + movePoint.x, mCenterPoint.y + movePoint.y};
                bool stopMove = (abs(mCenterPoint.x - mNewPosition.x) < modDelta &&
                                 abs(mCenterPoint.y - mNewPosition.y) < modDelta) ? true : false;
                if(stopMove)
                {
                    mMoving = !stopMove;
                    mCenterPoint = mNewPosition;
                    SetNewStartPosition(mCenterPoint.x, mCenterPoint.y);
                    mRotatation = 0;
                }
            }
        }
    }
}
