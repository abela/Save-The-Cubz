//
//  SceneManager.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/19/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//


#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "AboutMenu.h"

namespace scenes
{
    unique_ptr<SceneManager> SceneManager::m_sceneManagerInstance;
    once_flag SceneManager::onceFlag;
    
    SceneManager::SceneManager() : m_currentScene(nullptr)
    {
        
    }
    SceneManager::~SceneManager()
    {
        // destroy current scene
        m_currentScene.reset();
    }
    
    // singleton initializer callback
    void SceneManager::InitSingleton()
    {
        cout<<"SceneManager singleton initialization"<<endl;
    }
    
    //singleton instance
    SceneManager &SceneManager::Instance()
    {
        call_once(SceneManager::onceFlag, [](){
            InitSingleton();
            m_sceneManagerInstance.reset(new SceneManager());// = unique_ptr<SceneManager>(new SceneManager());
        });
        return *(m_sceneManagerInstance.get());
    }
    
    void SceneManager::Quit()
    {
        m_currentScene.reset();
        EngineInstance().EndEngine();
    }
    
    // start game, start engine
    void SceneManager::RunWithScene(SceneEnum sceneTypeToLoad)
    {
        // start Engine
        EngineInstance().StartEngine(*this);
        // run first scene
        ReplaceScene(sceneTypeToLoad);
        //
        // run engine with game loop
        EngineInstance().RunEngine();
    }
    
    // update scene manager, update current active scene
    void SceneManager::Update()
    {
        if(m_currentScene)
            m_currentScene->Update();
    }
    
    // load scene
    void SceneManager::ReplaceScene(SceneEnum sceneTypeToLoad, void *data)
    {
        //
        // crete next scene object to load it
        switch (sceneTypeToLoad)
        {
                // menu scene
            case kMainMenuScene:
                m_currentScene.reset(new MainMenuScene());
                break;
                // game scene
            case kGameScene:
                m_currentScene.reset(new GameScene());
                break;
            case kGameOverScene:
                m_currentScene.reset(new GameOverScene(data));
                break;
            case kAboutMenuScene:
                m_currentScene.reset(new AboutMenuScene());
                break;
            default:
                break;
        }
    }
}
