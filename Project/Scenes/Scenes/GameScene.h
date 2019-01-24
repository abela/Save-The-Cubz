//
//  GameScene.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/19/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef GameScene_h
#define GameScene_h

#include "IScene.h"
#include "Level.h"
#include "Sprite.h"
#include <iostream>
#include <map>
#include <vector>
#include "UiButton.h"
#include "UiProgressBar.h"
#include "UiLabel.h"

using namespace std;
using namespace game;
using namespace ui;

namespace scenes {
    class GameScene : public IScene
    {
    public:
        GameScene();
        ~GameScene();
        
    protected:
        void LoadScene() override;
        void UnloadScene() override;
        void DrawUi() override;
    private:
        //
        unique_ptr <Level> m_currentLevel;
        //
        unique_ptr <UiProgressBar> mPlayerProgressBar;
        unique_ptr <UiProgressBar> mPlayerProgressBarBg;
        //
        unique_ptr <UiProgressBar> mLevelTimerProgressBar;
        unique_ptr <UiProgressBar> mLevelTimerProgressBarBg;
        //
        unique_ptr<UiLabel> mLevelProgressLabel;
        unique_ptr<UiLabel> mLevelPushProgressLabel;
        unique_ptr<UiLabel> mLevelScoresLabel;
        unique_ptr<UiButton> mGoToMenuButton;
        unique_ptr<UiButton> mPushStackButton;
        //
        void Update() override;
        //
        void UpdateScore();
        void UpdatePushProgressBar();
        void UpdateLevelProgressBar();
        //
    };
}

#endif /* GameScene_h */
