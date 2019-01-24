//
//  LevelData.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "LevelData.h"

#include "Constants.h"

namespace game
{
    const int LEVEL_START_PUSH_TIME = 10;
    const float LEVEL_NEXT_PUSH_TIME = 1.0f;
    const int PROGRESS_START_STEP = 10;
    const int PROGRESS_NEXT_STEP = 30;
    const int LEVEL_START_PROGRESS = 6;
    const int MINIMUM_LEVEL_PUSH_TIME = 5;
    const int MAXIMUM_LEVEL_PROGRESS = 200;
    
    LevelData::LevelData() :
    m_levelNextProgress(LEVEL_START_PROGRESS),
    m_currentLevelScore(0),
    m_startLevelPushTime(LEVEL_START_PUSH_TIME),
    m_progressStartStep(PROGRESS_START_STEP),
    m_nextLevelPushTime(LEVEL_NEXT_PUSH_TIME)
    {
        for (int i =0; i<Constants::CUBES_COUNT; i++) {
            m_cubesColorCounter[i] = 0;
        }
    }
    //
    LevelData::~LevelData()
    {
        
    }
    //
    void LevelData::UpdateCubesCounter(int cubeIndex)
    {
        m_cubesColorCounter[cubeIndex]++;
    }
    //
    map <int,int> LevelData::GetCubesCounter()
    {
        return m_cubesColorCounter;
    }
    //
    void LevelData::UpdateLevelDataAfterLevelProgress()
    {
        m_progressStartStep = m_progressStartStep < MAXIMUM_LEVEL_PROGRESS ? m_progressStartStep + PROGRESS_NEXT_STEP : m_progressStartStep;
        m_startLevelPushTime = m_nextLevelPushTime < MINIMUM_LEVEL_PUSH_TIME ? MINIMUM_LEVEL_PUSH_TIME : m_startLevelPushTime - m_nextLevelPushTime;
    }
    //
    int LevelData::GetCurrentLevelScore()
    {
        return m_currentLevelScore;
    }
    
    void LevelData::SetLevelScore(int score)
    {
        m_currentLevelScore += score;
    }
    
    float LevelData::GetStartLevelPushTime()
    {
        return m_startLevelPushTime;
    }
    
    int LevelData::GetProgressStartStep()
    {
        return m_progressStartStep;
    }
    
    int LevelData::GetLevelNextProgress()
    {
        return m_levelNextProgress;
    }
    
    float LevelData::GetNextLEvelPushTime()
    {
        return m_nextLevelPushTime;
    }
    //
}
