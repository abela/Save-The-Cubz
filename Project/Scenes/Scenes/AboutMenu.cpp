//
//  AboutMenu.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/30/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "AboutMenu.h"
#include "SceneManager.h"

namespace scenes {

    AboutMenuScene::AboutMenuScene() :
    mLevelBackground(new GameObject(Constants::ASSETS_DIR + "/cubes/Level_bc.png",
                                    Constants::WINDOW_WIDTH / 2,
                                    Constants::WINDOW_HEIGHT /2,0,1)),
    m_AboutMenuLabel(new UiLabel((Constants::ASSETS_DIR + "/fonts/Hesitation.ttf").c_str(),
                                     "This game is made By Giorgi Abelix Abelashvili",
                                     {Constants::WINDOW_WIDTH / 2 - 250,
                                     Constants::WINDOW_HEIGHT / 2 - 50,
                                     500,30},
                                     0,1,30,{255,255,255})),
    m_BackButton(new UiButton((Constants::ASSETS_DIR + "/ui/push.png").c_str(),
                              Constants::MATRIX_STEP * 2,
                              Constants::WINDOW_HEIGHT - Constants::MATRIX_STEP * 2,0,1))
    {
        LoadScene();
    }
    AboutMenuScene::~AboutMenuScene()
    {
        UnloadScene();
    }
    
    void AboutMenuScene::LoadScene()
    {
        
    }
    
    void AboutMenuScene::UnloadScene()
    {
        m_BackButton.reset();
        m_AboutMenuLabel.reset();
        mLevelBackground.reset();
    }

    void AboutMenuScene::DrawUi()
    {
        mLevelBackground->Draw();
        m_AboutMenuLabel->Draw();
        if(m_BackButton->ButtonDown())
        {
            SceneManager::Instance().ReplaceScene(SceneEnum::kMainMenuScene);
        }
    }
    
    void AboutMenuScene::Update()
    {
        DrawUi();
    }
}
