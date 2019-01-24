//
//  GameOverScene.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/28/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "GameOverScene.h"
#include "LevelData.h"
#include "SceneManager.h"
using namespace game;

namespace scenes {
    GameOverScene::GameOverScene(void *data) :
    mLevelBackground(new GameObject(Constants::ASSETS_DIR + "/cubes/Level_bc.png",
                                    Constants::WINDOW_WIDTH / 2,
                                    Constants::WINDOW_HEIGHT /2,0,1)),
    m_AboutMenuLabel(new UiLabel((Constants::ASSETS_DIR + "/fonts/Hesitation.ttf").c_str(),
                                 "Game Over",
                                 {Constants::WINDOW_WIDTH / 2 - 250,
                                     Constants::WINDOW_HEIGHT/2 - 250,
                                     500,100},
                                 0,1,30,{255,255,255})),
    m_restartButton(new UiButton((Constants::ASSETS_DIR + "/ui/restart.png").c_str(),
                              Constants::MATRIX_STEP * 2,
                              Constants::WINDOW_HEIGHT - Constants::MATRIX_STEP * 2,0,1)),
    m_goToMenuButton(new UiButton((Constants::ASSETS_DIR + "/ui/home.png").c_str(),
                                  Constants::WINDOW_WIDTH - Constants::MATRIX_STEP * 2,
                                 Constants::WINDOW_HEIGHT - Constants::MATRIX_STEP * 2,0,1)),
    mScoresLabel(new UiLabel((Constants::ASSETS_DIR + "/fonts/Hesitation.ttf").c_str(),
                             "Score : 0",
                                 {Constants::WINDOW_WIDTH / 2 - 100,
                                     Constants::WINDOW_HEIGHT/2 - 100,
                                     200,30},
                                 0,1,30,{255,255,255}))
    {
        //
        LevelData *levelData = (LevelData*)data;
        //
        // update final scores
        if(levelData!=nullptr)
        {
            //
            mScoresLabel->SetText(("Score : " + to_string(levelData->GetCurrentLevelScore())).c_str());
            //
            int startCubeX = Constants::WINDOW_WIDTH/2 - Constants::CUBES_COUNT/2 * Constants::MATRIX_STEP * Constants::CUBES_COUNT;
            int startCubeY = Constants::WINDOW_HEIGHT/2;
            int cubesStep = Constants::MATRIX_STEP * 5;
            map <int,int> cubesMap = levelData->GetCubesCounter();
            for (int i =0;i<Constants::CUBES_COUNT;i++)
            {
                unique_ptr<CubeItem> nextCubeItem(new CubeItem());
                string cubeFilenameStr = Constants::ASSETS_DIR + "/cubes/cube_" + to_string(i+1) + ".png";
                int cubeScore = cubesMap[i];
                unique_ptr<Sprite> cube(new Sprite(cubeFilenameStr,startCubeX,startCubeY,0,1));
                cube->SetPosition(startCubeX, startCubeY);
                unique_ptr<UiLabel> label(new UiLabel((Constants::ASSETS_DIR + "/fonts/Hesitation.ttf").c_str(),
                                          "Score : 0",
                                                      {startCubeX-25,
                                          startCubeY + 25,
                                          40,20},
                                          0,1,30,{255,255,255}));
                label->SetText(("x" + to_string(cubeScore)).c_str());
                nextCubeItem->mLabel = move(label);
                nextCubeItem->mSprite = move(cube);
                startCubeX+=cubesStep;
                mCubes.push_back(move(nextCubeItem));
            }
        }
    }
    
    GameOverScene::~GameOverScene()
    {
        UnloadScene();
    }
    
    void GameOverScene::LoadScene()
    {
        for (int i =0;i<mCubes.size();i++)
        {
            mCubes[i].reset();
        }
    }
    
    void GameOverScene::UnloadScene()
    {
        m_goToMenuButton.reset();
        mLevelBackground.reset();
        m_restartButton.reset();
        m_AboutMenuLabel.reset();
    }
    
    void GameOverScene::DrawUi()
    {
        if(mLevelBackground)
            mLevelBackground->Draw();
        if(m_AboutMenuLabel)
            m_AboutMenuLabel->Draw();
        if(mScoresLabel)
            mScoresLabel->Draw();
        // restart game after game over
        if(m_restartButton)
        {
            if(m_restartButton->ButtonDown())
            {
                SceneManager::Instance().ReplaceScene(SceneEnum::kGameScene);
            }
        }
        // go to main menu screen
        if(m_goToMenuButton)
        {
            if(m_goToMenuButton->ButtonDown())
            {
                SceneManager::Instance().ReplaceScene(SceneEnum::kMainMenuScene);
            }
        }
        DrawFinalResultCubes();
    }
    
    void GameOverScene::DrawFinalResultCubes()
    {
        for (int i =0;i<mCubes.size();i++)
        {
            if(mCubes[i])
            {
                mCubes[i]->mSprite->Draw();
                mCubes[i]->mLabel->Draw();
            }
        }
    }
    
    void GameOverScene::Update()
    {
        DrawUi();
        DrawFinalResultCubes();
    }
}
