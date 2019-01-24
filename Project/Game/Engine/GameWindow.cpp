//
//  GameWindow.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/17/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "GameWindow.h"
#include "SDL_image.h"

// implement sdl window
namespace engine {
    
    SDL_Texture *texture;
    
    GameWindow::GameWindow(const char *gameName,
                           int xPos,
                           int yPos,
                           int width,
                           int height)
    {
        // initialize SDL
        if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
        {
            m_Window = unique_ptr<SDL_Window, SDLWindowDestroyer>(
                                                SDL_CreateWindow(gameName, xPos, yPos, width, height, SDL_WINDOW_SHOWN),
                                                SDLWindowDestroyer());
            if(m_Window)
            {
                // create renderer
                m_Renderer = unique_ptr<SDL_Renderer, SDLRendererDestroyer>(
                                                                            SDL_CreateRenderer(m_Window.get(), -1, SDL_RENDERER_SOFTWARE),
                                                                            SDLRendererDestroyer());
                if(!m_Renderer)
                    throw runtime_error(SDL_GetError());
                else {
                    SDL_SetRenderDrawColor(m_Renderer.get(), 0, 0, 0, 0);
                    //
                }
            }
        }
        else throw runtime_error(SDL_GetError());
    }
    
    SDL_Renderer *GameWindow::GetRenderer()
    {
        if(m_Renderer)
        {
            return m_Renderer.get();
        }
        return nullptr;
    }
    
    void GameWindow::RenderClear()
    {
        if(m_Renderer)
        {
            SDL_RenderClear(m_Renderer.get());
        }
    }
    
    void GameWindow::RenderPresent()
    {
        if(m_Renderer)
        {
            SDL_RenderPresent(m_Renderer.get());
        }
    }
    
    void GameWindow::Show()
    {
        SDL_ShowWindow(m_Window.get());
    }
    
    void GameWindow::Exit()
    {
        m_Renderer.reset();
        m_Window.reset();
    }
    
    GameWindow::~GameWindow()
    {
        Exit();
    }
}
