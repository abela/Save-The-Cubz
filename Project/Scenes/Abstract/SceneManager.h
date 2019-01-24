//
//  SceneManager.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/19/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef SceneManager_h
#define SceneManager_h

#include "GameEngine.h"
#include "IScene.h"
#include <iostream>
#include <memory>
using namespace std;
using namespace engine;


#include "Sprite.h"
using namespace game;

namespace scenes
{
    enum SceneEnum
    {
        kMainMenuScene,
        kGameScene,
        kGameOverScene,
        kAboutMenuScene
    };
    
    class SceneManager : public Updater
    {
        public:
            SceneManager();
            virtual ~SceneManager();
        
            void ReplaceScene(SceneEnum sceneTypeToLoad, void *data = nullptr);
        
            // singleton
            static SceneManager& Instance();
            void RunWithScene(SceneEnum sceneTypeToLoad);
            void Quit();
        private:
            static void InitSingleton();
            void Update();
            // singleton pattern variables
            unique_ptr <IScene> m_currentScene;
            static unique_ptr <SceneManager> m_sceneManagerInstance;
            static once_flag onceFlag;
    };
}

#endif /* SceneManager_h */
