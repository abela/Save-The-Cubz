//
//  Level.cpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "Level.h"


namespace game {
    
    bool m_entireRowDeletionTest = true;
    
    Level::Level() :
    mCubesPlatform(new GameObject(Constants::ASSETS_DIR + "/cubes/platform.png",
                                  Constants::WINDOW_WIDTH / 2 + Constants::WINDOW_WIDTH / 4 + 105,
                                  Constants::WINDOW_HEIGHT /2 + Constants::WINDOW_HEIGHT /4 + Constants::MATRIX_STEP / 2,0,1)),
    mLevelBackground(new GameObject(Constants::ASSETS_DIR + "/cubes/Level_bc.png",
                                    Constants::WINDOW_WIDTH / 2,
                                    Constants::WINDOW_HEIGHT /2,0,1)),
    m_cubeSelection(new Sprite(Constants::ASSETS_DIR + "/cubes/selection.png",-100,-100,0,1)),
    m_initialStartXSprite(new Sprite(Constants::ASSETS_DIR + "/cubes/selection.png",-100,-100,0,1)),
    m_cubeStackCounter(0),
    m_showGridRowsCounter(Constants::ROWS_SHOW_COUNTER),
    m_gridInitialStartX(0),
    mCubesMoving(false),
    mMoveGridLeft(false),
    mTotalGridColumns(0),
    mCubesMovingRight(false),
    mTotalMoveCounter(0),
    mLevelCubesPushLeftBorder(Constants::WINDOW_WIDTH/2 - Constants::MATRIX_WIDTH * Constants::MATRIX_WIDTH - Constants::MATRIX_WIDTH*6),
    mGameOver(false),
    mLevelData(new LevelData()),
    mGameStarted(false),
    mCubesDestroyCountUpdated(false),
    mlevelIsResetting(false),
    mlastDestroyedCubesCount(0),
    firstAdjecent(false),
    mBorderSprite(new Sprite(Constants::ASSETS_DIR + "/cubes/line.png",
                             mLevelCubesPushLeftBorder,
                             Constants::WINDOW_HEIGHT / 2 - 20,0,1))
    {
    }
    Level::~Level()
    {
        UnloadLevel();
    }
    
    // main level thick - update level push progress
    void Level::LevelThick()
    {
        if(mGameStarted == true && mMoveGridLeft == false)
        {
            mLevelThickCounter+=EngineInstance().GetLastFrameTime();
            if(mLevelThickCounter>=mLevelData->GetStartLevelPushTime())
            {
                PushGridLeft();
                mLevelThickCounter = 0;
            }
        }
    }
    
    float Level::GetCurrentLevelTick()
    {
        return mLevelThickCounter;
    }
    
    LevelData * Level::GetLevelData()
    {
        return mLevelData.get();
    }
    
    bool Level::IsGameOver()
    {
        return mGameOver;
    }
    
    bool Level::GameStarted()
    {
        return mGameStarted;
    }
    
    void Level::LoadLevel()
    {
        InitLevel();
    }
    
    void Level::UnloadLevel()
    {
        ResetCubes();
        // reset cube sprite object
        m_cubeSelection.reset();
        mLevelData.reset();
    }
    
    void Level::ResetCubes()
    {
        // reset cubes array
        for(int i = 0;i<Constants::MATRIX_HEIGHT;i++)
        {
            for(int j = 0;j<mTotalGridColumns;j++)
            {
                if(m_cubes[make_pair(i, j)]!=nullptr)
                    m_cubes[make_pair(i, j)].reset();
            }
        }
    }
    
    void Level::Update()
    {
        //
        RenderLevel();
        if(mGameOver == true)
            return;
        LevelThick();
        UpdateGameProgress();
        CheckCubeMoveingRight();
        //
    }
    
    void Level::UpdateGameProgress()
    {
        MoveGridLeft();
    }
    
    void Level::InitLevel()
    {
        // reet level thick counter
        mLevelThickCounter = 0;
        //
        // initialize level, create first grid
        int matrixStep = Constants::MATRIX_STEP;
        //
        m_gridInitialStartX = Constants::WINDOW_WIDTH;
        int cubeX = m_gridInitialStartX;
        int cubeY = Constants::WINDOW_HEIGHT / 2 - 4 * Constants::MATRIX_STEP;//Constants::WINDOW_HEIGHT / 2 - (Constants::MATRIX_HEIGHT / 2)*matrixStep;
        //
        mTotalGridColumns = Constants::MATRIX_WIDTH;
        //
        int idCounter = 0;
        //
        for(int i = 0;i<Constants::MATRIX_HEIGHT;i++)
        {
            for(int j = 0;j<mTotalGridColumns;j++)
            {
                int randomColorIndex = arc4random()%Constants::CUBES_COUNT;
                string cubeFilenameStr = Constants::ASSETS_DIR + "/cubes/cube_"+to_string(randomColorIndex+1) + ".png";
                unique_ptr<Sprite> cube(new Sprite(cubeFilenameStr,cubeX,cubeY,0,1));
                cube->SetGridId(idCounter);
                cube->SetColorId(randomColorIndex);
                cube->SetColumn(j);
                cube->SetRow(i);
                cube->SetMoving(true, cubeX - Constants::WINDOW_WIDTH / 2 + 5*matrixStep, cube->GetStartPosition().y);
                m_cubes[make_pair(i, j)] = move(cube);
                cubeX+=matrixStep;
                idCounter++;
            }
            cubeY+=matrixStep;
            cubeX = m_gridInitialStartX;
        }
        //
        m_gridInitialStartX = Constants::WINDOW_WIDTH - mTotalGridColumns * matrixStep;//Constants::WINDOW_WIDTH - mTotalGridColumns * matrixStep/2+matrixStep/2;
    }
    
    void Level::RenderLevel()
    {
        mLevelBackground->Draw();
        mCubesPlatform->Draw();
        mBorderSprite->Draw();
        UpdateCubes();
    }
    //
    void Level::UpdateCubes()
    {
        // draw diamonds
        bool selectionOutOfCubes = true;
        bool someCubeIsMoving = false;
        //
        for (int i = 0; i < Constants::MATRIX_HEIGHT; i++)
        {
            for (int j = 0; j < mTotalGridColumns; j++)
            {
                Sprite *cube = m_cubes[make_pair(i, j)].get();
                if(cube && mGameOver == false)
                {
                    if(cube->GetGridId() == -1)
                    {
                        m_cubes[make_pair(i, j)].reset();
                        return;
                    }
                    //
                    if(cube->Getmoving() == true)
                        someCubeIsMoving = cube->Getmoving();
                    //
                    cube->Draw();
                    //
                    int mouseX = engine::EngineInstance().GetMouseX();
                    int mouseY = engine::EngineInstance().GetMouseY();
                    //
                    if(cube->IsMouseInSprite(mouseX,mouseY) && cube->Getmoving() == false)
                    {
                        selectionOutOfCubes = false;
                        m_cubeSelection->SetPosition(cube->GetPosition().x,cube->GetPosition().y);
                        //
                        if(engine::EngineInstance().getMouseButtonDown())
                        {
                            if (engine::EngineInstance().GetMouseButtonDownFlag() == false)
                            {
                                engine::EngineInstance().SetMouseButtonDownFlag(true);
                                if(cube->IsMouseInSprite(mouseX,mouseY) && mCubesMoving == false)
                                {
                                    // manipulate cubes here
                                    int row = cube->GetRow();
                                    int column = cube->GetColumn();
                                    DetectAdjecentCubes(row, column);
                                    // after detecting adjecent array manipulate it
                                    ManipulateAdjecentArray(row,column);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
        // draw cube selection
        if(selectionOutOfCubes == false)
            m_cubeSelection->Draw();
        //
        UpdateInitialCubesPosition();
        //
        // detect if some cubes are moving in grid
        mCubesMoving = someCubeIsMoving;
        if(mGameStarted == false)
        {
            mGameStarted = !mCubesMoving;
        }
        //
    }
    
    void Level::UpdateInitialCubesPosition()
    {
        //m_initialStartXSprite->Draw();
        for(int j =0;j<mTotalGridColumns;j++)
        {
            for(int i = 0;i<Constants::MATRIX_HEIGHT;i++)
            {
                pair <int,int> nextIndice = GetCubeByRowAndColumn(i, j);
                if(m_cubes[nextIndice]!=nullptr)
                {
                    m_initialStartXSprite->SetPosition(m_cubes[nextIndice]->GetPosition().x,
                                                       m_cubes[nextIndice]->GetPosition().y);
                    if(m_initialStartXSprite->GetPosition().x <= mLevelCubesPushLeftBorder)
                    {
                        mGameOver = true;
                    }
                    return;
                }
            }
        }
        
        
    }
    
    pair<int,int> Level::GetCubeByRowAndColumn(int row, int column)
    {
        pair<int, int> cubeIndex = make_pair(-1, -1);
        bool foundIndex = false;
        float startX = m_gridInitialStartX;
        float startY = Constants::WINDOW_HEIGHT / 2 - 4 * Constants::MATRIX_STEP;
        //
        for(int i = 0;i<Constants::MATRIX_HEIGHT;i++)
        {
            for(int j = 0;j<mTotalGridColumns;j++)
            {
                if(m_cubes[make_pair(i, j)]!=nullptr)
                {
                    SDL_Point pnt = m_cubes[make_pair(i, j)]->GetPosition();
                    int newRow = (pnt.y - startY) / Constants::MATRIX_STEP;
                    int newCol = (pnt.x - startX) / Constants::MATRIX_STEP;
                    if(row == newRow && column == newCol && m_cubes[make_pair(i, j)]->GetGridId() !=-1)
                    {
                        cubeIndex = make_pair(i, j);
                        foundIndex = true;
                        break;
                    }
                }
            }
            if(foundIndex)
                break;
        }
        return cubeIndex;
    }
    //
    void Level::DetectAdjecentCubes(int i, int j)
    {
        //
        // testing deleting whole column
        /*if(firstAdjecent == false)
        {
            for(int ind=0;ind<Constants::MATRIX_HEIGHT;ind++)
            {
                m_adjacentListCache.push_back(make_pair(ind, j));
            }
            firstAdjecent = true;
            GenerateNewColumn();
            return;
        }*/
        //
        // get picked cube
        Sprite *pickedCube = m_cubes[GetCubeByRowAndColumn(i, j)].get();
        if(m_adjacentListCache.size() == 0)
            m_adjacentListCache.push_back(make_pair(i, j));
        //
        //int cubeColumnsCountOnScreen = (Constants::WINDOW_WIDTH - m_gridInitialStartX) / Constants::MATRIX_STEP + 1;
        //
        vector<Sprite*> adjacentSprites;
        if(j>0)
            adjacentSprites.push_back(m_cubes[GetCubeByRowAndColumn(i, j-1)].get());
        if(i>0)
            adjacentSprites.push_back(m_cubes[GetCubeByRowAndColumn(i-1, j)].get());
        if(j<mTotalGridColumns-1)
            adjacentSprites.push_back(m_cubes[GetCubeByRowAndColumn(i, j+1)].get());
        if(i<Constants::MATRIX_HEIGHT-1)
            adjacentSprites.push_back(m_cubes[GetCubeByRowAndColumn(i+1, j)].get());
        //
        for (int ind = 0; ind<adjacentSprites.size(); ind++)
        {
            if(pickedCube!=nullptr)
            {
                if(adjacentSprites[ind]!=nullptr)
                {
                    // if we choose same color
                    if(adjacentSprites[ind]->GetColorId() == pickedCube->GetColorId())
                    {
                        if(adjacentSprites[ind]->GetCheckedAsAdjecent() == false)
                        {
                            pickedCube->SetCheckedAsAdjecent(true);
                            m_adjacentListCache.push_back(make_pair(adjacentSprites[ind]->GetRow(), adjacentSprites[ind]->GetColumn()));
                            DetectAdjecentCubes(adjacentSprites[ind]->GetRow(), adjacentSprites[ind]->GetColumn());
                        }
                    }
                }
            }
        }
    }
    //
    void Level::ManipulateAdjecentArray(int currentRow, int currentColumn)
    {
        // if there is not a single same color cube remove cache list
        if(m_adjacentListCache.size() == 1)
        {
            if(m_cubes[GetCubeByRowAndColumn(m_adjacentListCache[0].first,m_adjacentListCache[0].second)]!=nullptr)
            {
                m_cubes[GetCubeByRowAndColumn(m_adjacentListCache[0].first,m_adjacentListCache[0].second)] ->SetCheckedAsAdjecent(false);
            }
            m_adjacentListCache.clear();
            return;
        }
        // 
        // some cubes are falling right now
        mCubesMoving = true;
        //
        // detect vertical gap count
        vector<pair<int, int>> startEndIndices;
        for(int i = 0; i < mTotalGridColumns; i++)
            startEndIndices.push_back(make_pair(numeric_limits<int>::max(), -1));
        //
        // calculate maximum and minimum of vertical gaps
        for(int i = 0; i<m_adjacentListCache.size();i++)
        {
            if(m_cubes[GetCubeByRowAndColumn(m_adjacentListCache[i].first,m_adjacentListCache[i].second)])
            {
                int row = m_adjacentListCache[i].first;
                int column = m_adjacentListCache[i].second;
                if(row < startEndIndices[column].first) startEndIndices[column].first = row;
                if(row > startEndIndices[column].second) startEndIndices[column].second = row;
                // prepare cube for destroy animation
                m_cubes[GetCubeByRowAndColumn(m_adjacentListCache[i].first,m_adjacentListCache[i].second)]->SetGridId(-2);
            }
        }
        //
        // Move every cube above upper vertical gap
        for(int i =0;i<startEndIndices.size();i++)
        {
            if(startEndIndices[i].second == -1)
                continue;
            int moveCount = startEndIndices[i].second - startEndIndices[i].first + 1;
            for(int row = 0; row < startEndIndices[i].first; row++)
            {
                pair <int,int> nextIndice = GetCubeByRowAndColumn(row, i);
                if(m_cubes[nextIndice] && m_cubes[nextIndice]->GetGridId() != -1)
                {
                    m_cubes[nextIndice]->SetMoving(true,
                                                   m_cubes[nextIndice]->GetPosition().x,
                                                   m_cubes[nextIndice]->GetStartPosition().y +
                                                   moveCount * Constants::MATRIX_STEP);
                }
            }
        }
        //
        // after movin all of the above cubes - recalculate new rows indices
        for(int i = 0; i < startEndIndices.size(); i++)
        {
            if(startEndIndices[i].second == -1)
                continue;
            int moveCount = (startEndIndices[i].second - startEndIndices[i].first);
            for(int row = 0; row < startEndIndices[i].first; row++)
            {
                pair <int,int> nextIndice = GetCubeByRowAndColumn(row, i);
                if(nextIndice.first!=-1 && m_cubes[nextIndice] && m_cubes[nextIndice]->GetGridId() != -1)
                {
                    SDL_Point newPnt = m_cubes[nextIndice]->GetNewPosition();
                    int idx  = (newPnt.y - (Constants::WINDOW_HEIGHT/2 - 4 * Constants::MATRIX_STEP)) / Constants::MATRIX_STEP;
                    m_cubes[nextIndice]->SetRow(idx);
                    int newGridId = m_cubes[nextIndice]->GetGridId() + mTotalGridColumns * moveCount;
                    m_cubes[nextIndice]->SetGridId(newGridId);
                }
            }
        }
        // clear adjecent cache
        int adjecentCount = (int)m_adjacentListCache.size();
        //
        // update cubes destroy counter
        for(int i =0;i<m_adjacentListCache.size();i++)
        {
            mLevelData->UpdateCubesCounter(m_cubes[GetCubeByRowAndColumn(m_adjacentListCache[i].first,
                                                                 m_adjacentListCache[i].second)]->GetColorId());
        }
        //
        m_adjacentListCache.clear();
        //
        // calculate level progress
        mCubesDestroyCountUpdated = true;
        mlastDestroyedCubesCount += adjecentCount;
        mUpdateScore = true;
        mLevelData->SetLevelScore(adjecentCount);
        //
        // if we progresed to the next level generate new stack of cubes
        if(mlastDestroyedCubesCount >= mLevelData->GetProgressStartStep())
        {
            GenerateNewStack();
        }
        //
    }
    
    void Level::CheckCubeMoveingRight()
    {
        if(mCubesMovingRight == false && mCubesMoving == false && mMoveGridLeft == false)
        {
            vector<int> columnsToDelete;
            //
            for(int j = 0;j<mTotalGridColumns;j++)
            {
                int deletedCubesCounter = 0;
                for(int i = 0;i<Constants::MATRIX_HEIGHT;i++)
                {
                    pair <int,int> index = GetCubeByRowAndColumn(i, j);
                    if(m_cubes[index] == nullptr)
                    {
                        deletedCubesCounter++;
                        if(deletedCubesCounter == Constants::MATRIX_HEIGHT)
                        {
                            mCubesMovingRight = true;
                            columnsToDelete.push_back(j);
                        }
                    }
                }
            }
            //
            if(mCubesMovingRight)
            {
                MoveColumnsRight(columnsToDelete);
            }
            //
        }
    }
    
    // use for debug only to print array
    void Level::PrintGrid()
    {
        for(int i = 0;i<Constants::MATRIX_HEIGHT;i++)
        {
            for(int j = 0;j<mTotalGridColumns;j++)
            {
                if(m_cubes[make_pair(i, j)]!=nullptr)
                {
                    if(m_cubes[make_pair(i, j)]->GetGridId() < 0)
                        cout<< "0 ";
                    else cout<< "1 ";
                }
                else cout<<"0 "<<endl;
            }
            cout<<endl;
        }
        cout<<endl<<endl<<endl;
    }
    
    void Level::PushGridLeft()
    {
        GenerateNewColumn();
        mMoveGridLeft = true;
    }
    
    void Level::GenerateNewColumn()
    {
        int matrixStep = Constants::MATRIX_STEP;
        int cubeX = Constants::WINDOW_WIDTH + matrixStep/2;
        int cubeY = Constants::WINDOW_HEIGHT / 2 - 4 * Constants::MATRIX_STEP;
        for (int i=0; i<Constants::MATRIX_HEIGHT; i++)
        {
            int randomColorIndex = arc4random()%Constants::CUBES_COUNT;
            string cubeFilenameStr = Constants::ASSETS_DIR + "/cubes/cube_"+to_string(randomColorIndex+1) + ".png";
            unique_ptr<Sprite> cube(new Sprite(cubeFilenameStr,cubeX,cubeY,0,1));
            cube->SetGridId((mTotalGridColumns + 1) * (i+1));
            cube->SetColorId(randomColorIndex + 1);
            cube->SetColumn(mTotalGridColumns);
            cube->SetRow(i);
            m_cubes[make_pair(i, mTotalGridColumns)] = move(cube);
            cubeY+=matrixStep;
        }
        mTotalGridColumns+=1;
    }
    
    bool Level::GetUpdateScoreStatus()
    {
        return mUpdateScore;
    }
    
    bool Level::AreNewPairOfCubesDestroyed()
    {
        return mCubesDestroyCountUpdated;
    }
    
    void Level::SetNewCubesAreDestroyedFlag(bool flag)
    {
        mCubesDestroyCountUpdated = flag;
    }
    
    int Level::GetLastDestroyedCubesCount()
    {
        return mlastDestroyedCubesCount;
    }
    
    void Level::SetUpdateScoreStatus(bool scoreUpdateStatus)
    {
        mUpdateScore = scoreUpdateStatus;
    }
    
    void Level::MoveGridLeft()
    {
        if(mMoveGridLeft)
        {
            if(mCubesMoving == false)
            {
                float step = Constants::MATRIX_STEP;
                mMoveGridLeft = false;
                for(int i = 0;i<Constants::MATRIX_HEIGHT;i++)
                {
                    for(int j = 0;j<mTotalGridColumns;j++)
                    {
                        pair<int, int> nextIndice = GetCubeByRowAndColumn(i,j);
                        if(m_cubes[nextIndice]!=nullptr)
                        {
                            m_cubes[nextIndice]->SetGridSpriteRotation(true);
                            m_cubes[nextIndice]->SetMoving(true,
                                                           m_cubes[nextIndice]->GetPosition().x - step,
                                                           m_cubes[nextIndice]->GetPosition().y);
                        }
                    }
                }
                m_gridInitialStartX-=step;
            }
        }
    }
    
    
    void Level::MoveColumnsRight(vector<int> columns)
    {
        //
        mMoveGridLeft = false;
        mCubesMoving = false;
        //
        float step = Constants::MATRIX_STEP;
        //
        int stepCounter = 1;
        int col_ind_1_counter = 1;
        int col_ind_2_counter = 2;
        int index_1 = columns[(int)columns.size()-col_ind_1_counter], index_2 = columns[(int)columns.size()-col_ind_2_counter];
        for(int in = 0;in<columns.size();in++)
        {
            for(int j = index_1 - 1; j>=index_2; j--)
            {
                for(int i = 0;i<Constants::MATRIX_HEIGHT;i++)
                {
                    pair<int, int> nextIndice = GetCubeByRowAndColumn(i,j);
                    if(m_cubes[nextIndice]!=nullptr)
                    {
                        int column = m_cubes[nextIndice]->GetColumn();
                        column+=stepCounter;
                        m_cubes[nextIndice]->SetColumn(column);
                        m_cubes[nextIndice]->SetGridSpriteRotation(true);
                        m_cubes[nextIndice]->SetMoving(true,
                                                       m_cubes[nextIndice]->GetStartPosition().x + stepCounter * step,
                                                       m_cubes[nextIndice]->GetStartPosition().y);
                    }
                }
            }
            col_ind_1_counter++;
            col_ind_2_counter++;
            index_1 = columns[(int)columns.size()-col_ind_1_counter];
            index_2 = col_ind_2_counter > (int)columns.size() ? 0 : columns[(int)columns.size()-col_ind_2_counter];
            stepCounter++;
        }
        //
        mCubesMovingRight = false;
        //
    }
    
    void Level::GenerateNewStack()
    {
        mGameStarted = false;
        mlevelIsResetting = true;
        mlastDestroyedCubesCount = 0;
        ResetCubes();
        InitLevel();
        mLevelData->UpdateLevelDataAfterLevelProgress();
    }
}
