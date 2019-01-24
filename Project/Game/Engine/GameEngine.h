//
//  Engine.h
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/17/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef Engine_h
#define Engine_h

#include "Updater.h"
#include "GameWindow.h"
using namespace std;

#define EngineInstance GameEngine::Instance

// main game negine class, implement this class for game core - drawing, input.
namespace engine {
    class Updater;
    class GameEngine
    {
    public:
        // default constructor
        GameEngine() = default;
        virtual ~GameEngine();
        // constructor to create main game window
        GameEngine(string assetsDirectory);
        
        // get renderer
        SDL_Renderer *GetRenderer();
        
        // singleton
        static void InitSingleton();
        static GameEngine& Instance();
        
        // start and end engine
        void StartEngine(Updater &updater);
        void RunEngine();
        void EndEngine();
        
        // mouse input methods
        bool getMouseButton() const;
        bool getMouseButtonDown() const;
        bool getMouseButtonUp() const;
        void SetMouseButtonDownFlag(bool mouseButtnDownFlag);
        bool GetMouseButtonDownFlag();
        //
        float GetMouseX();
        float GetMouseY();
        //
        float GetLastFrameTime();
        //
    private:
        //
        // game window
        unique_ptr <GameWindow> m_gameWindow;
        // updater
        Updater *m_updater;
        //
        // singleton variables
        static unique_ptr <GameEngine> m_engineInstance;
        static once_flag onceFlag;
        //
        bool m_MouseButtonDownFlag;
        //
        GameEngine(const GameEngine&) = delete;
        GameEngine & operator=(const GameEngine&) = delete;
        //
        void Exit();
        //
        void GameRenderLoop();
        //
        void GameInputEventListener();
        //
        // we need time between frames
        void CalculateLastFrameTime();
        //
        bool m_quitGame;
        float m_lastFrameTick;
        float m_elapsedTimeTicks;
        // mouse event flags
        bool m_mouseButton;
        bool m_mouseButtonDown;
        bool m_mouseButtonUp;
        //
        float m_mouseX;
        float m_mouseY;
        //
    };
}

#endif /* Engine_h */
