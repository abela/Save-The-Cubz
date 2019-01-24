//
//  MenuScene.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/19/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "MenuScene.h"
#include "Constants.h"
#include "GameEngine.h"
#include "SceneManager.h"
using namespace scenes;
using namespace engine;

namespace scenes {
    MainMenuScene::MainMenuScene() : mLevelBackground(new GameObject(Constants::ASSETS_DIR + "/cubes/Level_bc.png",
                                                                 Constants::WINDOW_WIDTH / 2,
                                                                 Constants::WINDOW_HEIGHT /2,0,1)),
    mTitle(new GameObject(Constants::ASSETS_DIR + "/ui/Title_Spr.png",
                                    Constants::WINDOW_WIDTH / 2,
                                    Constants::WINDOW_HEIGHT /4,0,1)),
    m_playButton(new UiButton((Constants::ASSETS_DIR + "/ui/Play.png").c_str(),
                              Constants::WINDOW_WIDTH / 2,
                              Constants::WINDOW_HEIGHT / 2 + Constants::WINDOW_HEIGHT / 10,0,1)),
    m_infoButton(new UiButton((Constants::ASSETS_DIR + "/ui/info.png").c_str(),
                              Constants::WINDOW_WIDTH/2 - Constants::MATRIX_STEP * 2,
                              Constants::WINDOW_HEIGHT - Constants::MATRIX_STEP * 2,0,1)),
    m_quitButton(new UiButton((Constants::ASSETS_DIR + "/ui/home.png").c_str(),
                              Constants::WINDOW_WIDTH/2 + Constants::MATRIX_STEP * 2,
                              Constants::WINDOW_HEIGHT - Constants::MATRIX_STEP * 2,0,1))
    
    
    {
        
    }
    MainMenuScene::~MainMenuScene()
    {
        UnloadScene();
    }
    
    void MainMenuScene::LoadScene()
    {
        
    }
    void MainMenuScene::UnloadScene()
    {
        m_quitButton.reset();
        m_playButton.reset();
        m_infoButton.reset();
        mTitle.reset();
        mLevelBackground.reset();
    }
    void MainMenuScene::DrawUi()
    {
        if(mTitle!=nullptr)
            mTitle->Draw();
        // start game butto
        if(m_playButton!=nullptr)
        {
            if(m_playButton->ButtonDown())
            {
                SceneManager::Instance().RunWithScene(SceneEnum::kGameScene);
            }
        }
        // go to info screen
        if(m_infoButton!=nullptr)
        {
            if(m_infoButton->ButtonDown())
            {
                SceneManager::Instance().ReplaceScene(SceneEnum::kAboutMenuScene);
            }
        }
        // quit game button
        if(m_quitButton!=nullptr)
        {
            if(m_quitButton->ButtonDown())
            {
                SceneManager().Instance().Quit();
            }
        }
    }
    
    void MainMenuScene::Update()
    {
        if(mLevelBackground)
            mLevelBackground->Draw();
        DrawUi();
    }
}
