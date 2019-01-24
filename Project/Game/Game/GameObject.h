//
//  GameObject.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/19/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef GameObject_h
#define GameObject_h
#include <stdio.h>
#include "GameEngine.h"
#include "Constants.h"
#include "SDL_image.h"

namespace game {
    // abstract class of all gameobjects
    class IGameObject
    {
    public:
        // main drawing function
        virtual void Draw() = 0;
        
        virtual void SetPosition(int posX, int posY) = 0;
        virtual void SetRotation(float rot) = 0;
        virtual void SetScale(float scale) = 0;
        
        virtual SDL_Point GetPosition() = 0;
        virtual float GetRotation() = 0;
        virtual float GetScale() = 0;
        
    protected:
        // current draw texture Id
        SDL_Texture *mTextureToDraw;
        // positions and rotation
        SDL_Point mCenterPoint;
        SDL_Point mStartPosition;
        float mRotatation;
        int mScale;
        int mTextureWidth;
        int mTextureHeight;
    };
    
    class GameObject : public IGameObject
    {
    public:
        // assign draw engine with dependence injection
        GameObject(const string textureFile, int posX, int posY, float rot, float scale);
        GameObject();
        GameObject(int posX, int posY, float rot, float scale);
        virtual ~GameObject();
        
        // Setters
        void SetPosition(int posX, int posY) override;
        void SetRotation(float rot) override;
        void SetScale(float scale) override;
        //
        void SetTextureToDraw(SDL_Texture *texture);
        void SetMoving(bool move, int dirX, int dirY);
        void SetMoveSpeed(int moveSpeed);
        int GetMoveSpeed();
        
        SDL_Point GetStartPosition();
        
        // getters
        SDL_Point GetPosition() override;
        float GetRotation() override;
        float GetScale() override;
        bool Getmoving();
        SDL_Texture *GetTexture();
        
        // main drawing function
        void Draw() override;
        
        SDL_Point GetNewPosition() const;
        
    protected:
        bool mDestroyed;
        bool mMoving;
        int mMoveSpeed;
        //
        SDL_Point mNewPosition;
        //
        // move To Position
        virtual void MoveToPosition(float frameDeltaTime);
        void SetNewStartPosition(int x,int y);
    };
}


#endif /* GameObject_h */
