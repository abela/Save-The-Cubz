//
//  GameScene.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/19/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "GameScene.h"
#include "SceneManager.h"
using namespace scenes;
namespace scenes
{
    //
    GameScene::GameScene() :
    m_currentLevel(new Level()),
    mPlayerProgressBar(new UiProgressBar(30,30,150,10,1,{0,255,0,255})),
    mPlayerProgressBarBg(new UiProgressBar(25,25,160,20,1,{128,128,128,255})),
    mLevelTimerProgressBar(new UiProgressBar(230,30,150,10,1,{255,0,0,255})),
    mLevelTimerProgressBarBg(new UiProgressBar(225,25,160,20,1,{128,128,128,255})),
    //
    mLevelProgressLabel(new UiLabel((Constants::ASSETS_DIR + "/fonts/Hesitation.ttf").c_str(),
                                    "Progress",
                                    {200,25,100,20},
                                    0,1,24,{255,255,255})),
    mLevelPushProgressLabel(new UiLabel((Constants::ASSETS_DIR + "/fonts/Hesitation.ttf").c_str(),
                                    "Push",
                                    {600,25,50,20},
                                    0,1,24,{255,255,255})),
    mLevelScoresLabel(new UiLabel((Constants::ASSETS_DIR + "/fonts/Hesitation.ttf").c_str(),
                                        "Score: 0",
                                        {30,Constants::WINDOW_HEIGHT - 50,100,20},
                                        0,1,24,{255,255,255})),
    mPushStackButton(new UiButton((Constants::ASSETS_DIR + "/ui/push.png").c_str(),
                                  Constants::WINDOW_WIDTH - Constants::MATRIX_STEP,
                              Constants::WINDOW_HEIGHT - Constants::MATRIX_STEP ,0,1)),
    mGoToMenuButton(new UiButton((Constants::ASSETS_DIR + "/ui/home.png").c_str(),
                                  Constants::WINDOW_WIDTH - Constants::MATRIX_STEP,
                                  Constants::MATRIX_STEP ,0,1))
    
    {
        //
        mPlayerProgressBar->SetProgress(0);
        mLevelTimerProgressBar->SetProgress(0);
        mLevelTimerProgressBar->SetPosition(430, 30);
        mLevelTimerProgressBarBg->SetPosition(425, 25);
        //
        LoadScene();
    }
    //
    GameScene::~GameScene()
    {
        UnloadScene();
    }
    
    void GameScene::LoadScene()
    {
        // initialize level
        m_currentLevel->LoadLevel();
    }
    void GameScene::UnloadScene()
    {
        m_currentLevel->UnloadLevel();
    }
    
    void GameScene::Update()
    {
        if(m_currentLevel)
        {
            m_currentLevel->Update();
            if(m_currentLevel->IsGameOver())
            {
                SceneManager().Instance().ReplaceScene(SceneEnum::kGameOverScene,m_currentLevel->GetLevelData());
                return;
            }
        }
        DrawUi();
    }
    
    void GameScene::DrawUi()
    {
        // if game isn't started yet, don't draw ui and don't update level score
        //if(m_currentLevel->GameStarted() == false)
        //    return;
        //
        if(mPlayerProgressBarBg)
        {
            mPlayerProgressBarBg->Draw();
        }
        if(mPlayerProgressBar)
            mPlayerProgressBar->Draw();
        //
        if(mLevelTimerProgressBarBg)
            mLevelTimerProgressBarBg->Draw();
        if(mLevelTimerProgressBar)
            mLevelTimerProgressBar->Draw();
        //
        if(mLevelProgressLabel)
            mLevelProgressLabel->Draw();
        if(mLevelPushProgressLabel)
            mLevelPushProgressLabel->Draw();
        if(mLevelScoresLabel)
            mLevelScoresLabel->Draw();
        //
        // update score label
        UpdateScore();
        // update score label bar
        UpdatePushProgressBar();
        // update player progress bar
        UpdateLevelProgressBar();
        //
        // push grid left
        if(mPushStackButton)
        {
            if(mPushStackButton->ButtonDown())
            {
                m_currentLevel->PushGridLeft();
            }
        }
        // go to menu button
        if(mGoToMenuButton)
        {
            if(mGoToMenuButton->ButtonDown())
            {
                SceneManager::Instance().ReplaceScene(SceneEnum::kMainMenuScene);
            }
        }
        //
    }
    //
    void GameScene::UpdateScore()
    {
        // update leve score once we get new score
        if(m_currentLevel->GetUpdateScoreStatus())
        {
            m_currentLevel->SetUpdateScoreStatus(false);
            int levelScore = m_currentLevel->GetLevelData()->GetCurrentLevelScore();
            string finalScore = "Score: " + to_string(levelScore);
            mLevelScoresLabel->SetText(finalScore.c_str());
        }
    }
    //
    void GameScene::UpdatePushProgressBar()
    {
        //
        if(mLevelTimerProgressBar)
        {
            int progressBarInitialWidth = mLevelTimerProgressBar->GetInitialWidth();
            int levelThick = m_currentLevel->GetCurrentLevelTick();
            int levelPushValue = m_currentLevel->GetLevelData()->GetStartLevelPushTime();
            int progressStep = progressBarInitialWidth / levelPushValue;
            //
            int progress = progressStep * levelThick;
            mLevelTimerProgressBar->SetProgress(progress);
        }
        //
    }
    //
    void GameScene::UpdateLevelProgressBar()
    {
        if(m_currentLevel)
        {
            if(m_currentLevel->AreNewPairOfCubesDestroyed())
            {
                int newDestroyedCubesCount = m_currentLevel->GetLastDestroyedCubesCount();
                int nextProgressStep = m_currentLevel->GetLevelData()->GetProgressStartStep();
                int progressInitialWidth = mPlayerProgressBar->GetInitialWidth();
                //
                int progress = (newDestroyedCubesCount == 0) ? newDestroyedCubesCount :
                progressInitialWidth / nextProgressStep * newDestroyedCubesCount;
                if(progress >= mPlayerProgressBar->GetInitialWidth())
                {
                    progress = 0;
                }
                //
                mPlayerProgressBar->SetProgress(progress);
                //
                m_currentLevel->SetNewCubesAreDestroyedFlag(false);
                //
            }
        }
       
    }
}
