//
//  Level.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef Level_h
#define Level_h

#include "GameEngine.h"
#include "Sprite.h"
#include "LevelData.h"
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using namespace engine;

namespace game {
    class Level : Updater
    {
    public:
        Level();
        virtual ~Level();
        
        void LoadLevel();
        void UnloadLevel();
        void Update() override;
        void PushGridLeft();
        bool IsGameOver();
        bool GameStarted();
        bool GetUpdateScoreStatus();
        bool AreNewPairOfCubesDestroyed();
        void SetNewCubesAreDestroyedFlag(bool flag);
        void SetUpdateScoreStatus(bool scoreUpdateStatus);
        int GetLastDestroyedCubesCount();
        LevelData *GetLevelData();
        float GetCurrentLevelTick();
    private:
        //
        bool firstAdjecent;
        //
        float mLevelThickCounter;
        bool mUpdateScore;
        bool mCubesDestroyCountUpdated;
        bool mGameStarted;
        bool mlevelIsResetting;
        bool mMoveGridLeft;
        bool mCubesMoving;
        bool mCubesMovingRight;
        int mlastDestroyedCubesCount;
        int m_gridInitialStartX;
        int m_cubeStackCounter;
        //
        int mTotalGridColumns;
        int mTotalMoveCounter;
        int mLevelCubesPushLeftBorder;
        //
        unique_ptr<GameObject> mLevelBackground;
        unique_ptr<GameObject> mCubesPlatform;
        unique_ptr<Sprite> mBorderSprite;
        unique_ptr<LevelData> mLevelData;
        unique_ptr<Sprite> m_cubeSelection;
        unique_ptr<Sprite> m_initialStartXSprite;
        //
        map <pair<int,int> , unique_ptr<Sprite>> m_cubes;
        vector<int> deletedColumns;
        vector<pair<int,int>> m_adjacentListCache;
        //
        int m_showGridRowsCounter;
        //
        void InitLevel();
        void LevelThick();
        void ResetCubes();
        void RenderLevel();
        void UpdateCubes();
        void DetectAdjecentCubes(int i, int j);
        void ManipulateAdjecentArray(int currentRow, int currentColumn);
        pair<int,int> GetCubeByRowAndColumn(int row, int column);
        void UpdateInitialCubesPosition();
        void MoveGridLeft();
        void MoveColumnsRight(vector<int> columns);
        //
        // use this for debug
        void PrintGrid();
        //
        void UpdateGameProgress();
        void CheckCubeMoveingRight();
        void GenerateNewStack();
        void GenerateNewColumn();
        //
        bool mGameOver;
        //
    };
}

#endif /* Level_h */
