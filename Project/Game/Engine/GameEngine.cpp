//
//  Engine.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/17/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "GameEngine.h"
#include "Constants.h"
#include "SDL_ttf.h"

namespace engine {
    
    unique_ptr<GameEngine> GameEngine::m_engineInstance;
    once_flag GameEngine::onceFlag;
    
    static const int WindowWidth = Constants::WINDOW_WIDTH;
    static const int WindowHeight = Constants::WINDOW_HEIGHT;
    
    // constructor to create main game window
    GameEngine::GameEngine(string assetsDirectory) :
    m_gameWindow(new GameWindow(Constants::GAME_NAME.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WindowWidth,
                                WindowHeight)),
    m_lastFrameTick(1 / 60),
    m_elapsedTimeTicks(static_cast<float>(SDL_GetTicks())),
    m_mouseButton(false),
    m_mouseButtonDown(false),
    m_mouseButtonUp(false),
    m_mouseX(WindowWidth * 0.5f),
    m_mouseY(WindowHeight * 0.5f),
    m_MouseButtonDownFlag(false)
    {
        // initialize ttf engine
        if(TTF_Init() < 0)
            cout<<TTF_GetError()<<endl;
    }
    
    GameEngine::~GameEngine()
    {
        Exit();
    }
    
    SDL_Renderer *GameEngine::GetRenderer()
    {
        if(m_gameWindow)
        {
            return m_gameWindow->GetRenderer();
        }
        return nullptr;
    }
    
    // singleton initializer callback
    void GameEngine::InitSingleton()
    {
        cout<<"Engine Singleton inctance initialize"<<endl;
    }
    //
    //singleton instance
    GameEngine &GameEngine::Instance()
    {
        call_once(GameEngine::onceFlag, [](){
            InitSingleton();
            m_engineInstance = unique_ptr<GameEngine>(new GameEngine(Constants::ASSETS_DIR));
        });
        return *(m_engineInstance.get());
    }
    
    // start and end engine
    void GameEngine::StartEngine(Updater &updater)
    {
        // assign updater
        this->m_updater = &updater;
        // show window
        m_gameWindow->Show();
    }
    
    void GameEngine::RunEngine()
    {
        GameRenderLoop();
    }
    
    void GameEngine::GameRenderLoop()
    {
        while(m_quitGame == false && m_updater!=NULL)
        {
            m_gameWindow->RenderClear();
            
            // calculate last frame in secnd
            CalculateLastFrameTime();
            
            // update game loop on each frame
            m_updater->Update();
            
            m_gameWindow->RenderPresent();
            
            GameInputEventListener();
        }
    }
    
    void GameEngine::Exit()
    {
        m_quitGame = true;
        m_gameWindow.reset();
        m_updater = NULL;
    }
    
    void GameEngine::CalculateLastFrameTime()
    {
        float maxFrameTick = 500;
        float currentTicks = static_cast<float>(SDL_GetTicks());
        float lastFrameTicks = currentTicks - m_elapsedTimeTicks;
        m_elapsedTimeTicks = currentTicks;
        
        lastFrameTicks = min(lastFrameTicks,maxFrameTick);
        // calculate latest frame seconds
        m_lastFrameTick = lastFrameTicks * 0.001f;

    }
    
    void GameEngine::GameInputEventListener()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    m_quitGame = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    m_mouseButton = true;
                    if (event.button.state == SDL_PRESSED)
                    {
                        if(event.button.clicks == 1)
                        {
                            m_mouseButtonUp = false;
                            m_mouseButtonDown = true;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.clicks == 1)
                    {
                        m_mouseButton = false;
                        m_mouseButtonUp = true;
                        m_mouseButtonDown = false;
                        m_MouseButtonDownFlag = false;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    m_mouseX = static_cast<float>(event.motion.x);
                    m_mouseY = static_cast<float>(event.motion.y);
                    //
                    //printf("%d\n", mMouseRelativeX);
                    //
                    break;
                default:
                    break;
            }
        }

    }
    // get last frame second  - game thick time
    float GameEngine::GetLastFrameTime()
    {
        return m_lastFrameTick;
    }
    
    // terminate application
    void GameEngine::EndEngine()
    {
        m_quitGame = true;
    }
    // mouse event methods for 
    bool GameEngine::getMouseButton() const
    {
        return m_mouseButton;
    }
    //
    bool GameEngine::getMouseButtonDown() const
    {
        return m_mouseButtonDown;
    }
    //
    bool GameEngine::getMouseButtonUp() const
    {
        return m_mouseButtonUp;
    }
    //
    void GameEngine::SetMouseButtonDownFlag(bool mouseButtnDownFlag)
    {
        m_MouseButtonDownFlag = mouseButtnDownFlag;
    }
    bool GameEngine::GetMouseButtonDownFlag()
    {
        return m_MouseButtonDownFlag;
    }
    //
    float GameEngine::GetMouseX()
    {
        return m_mouseX;
    }
    //
    float GameEngine::GetMouseY()
    {
        return m_mouseY;
    }
    //
}


