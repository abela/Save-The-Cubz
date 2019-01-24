//
//  LevelData.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef LevelData_h
#define LevelData_h
#include <map>

using namespace std;

namespace game {
    class LevelData
    {
    public:
        LevelData();
        virtual ~LevelData();
        
        int GetCurrentLevelScore();
        float GetStartLevelPushTime();
        int GetProgressStartStep();
        int GetLevelNextProgress();
        float GetNextLEvelPushTime();
        
        void UpdateLevelDataAfterLevelProgress();
        
        void UpdateCubesCounter(int cubeIndex);
        
        map <int,int> GetCubesCounter();
        
        void SetLevelScore(int score);
        
    private:
        map <int,int> m_cubesColorCounter;
        int m_levelNextProgress;
        int m_currentLevelScore;
        float m_startLevelPushTime;
        float m_nextLevelPushTime;
        int m_progressStartStep;
    };
}

#endif /* LevelData_h */
