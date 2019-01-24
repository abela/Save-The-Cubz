//
//  GameWindow.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/17/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef GameWindow_h
#define GameWindow_h

#include "SDL.h"
#include <iostream>

using namespace std;

// sdl window
namespace engine
{
    struct SDLWindowDestroyer
    {
        void operator()(SDL_Window* w) const
        {
            SDL_DestroyWindow(w);
        }
    };
    
    struct SDLRendererDestroyer
    {
        void operator()(SDL_Renderer* r) const
        {
            // don't do anything window wll remove renderer itself
        }
    };
    
    class GameWindow
    {
    public:
        GameWindow(const char *gameName,
                   int xPos,
                   int yPos,
                   int width,
                   int height);
        void Show();
        // call before draw something
        void RenderClear();
        // call after draw something
        void RenderPresent();
        //
        SDL_Renderer *GetRenderer();
        //
        ~GameWindow();
    private:
        void Exit();
        unique_ptr<SDL_Renderer, SDLRendererDestroyer> m_Renderer;
        unique_ptr<SDL_Window, SDLWindowDestroyer> m_Window;
    };
}

#endif /* GameWindow_hpp */
