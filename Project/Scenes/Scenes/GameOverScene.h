//
//  GameOverScene.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/28/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//
//
#ifndef GameOverScene_h
#define GameOverScene_h
#include <vector>
#include "IScene.h"
#include "LevelData.h"
#include "UiButton.h"
#include "UiLabel.h"
#include "Sprite.h"
using namespace std;
using namespace game;
using namespace ui;

namespace scenes {
    class GameOverScene : public IScene
    {
    public:
        GameOverScene(void *data);
        ~GameOverScene();
        
        void Update() override;
    protected:
        void LoadScene() override;
        void UnloadScene() override;
        void DrawUi() override;
        
    private:
        //
        struct CubeItem
        {
            unique_ptr<Sprite> mSprite;
            unique_ptr<UiLabel> mLabel;
            ~CubeItem()
            {
                mSprite.reset();
                mLabel.reset();
            }
        };
        vector<unique_ptr<CubeItem>> mCubes;
        //
        unique_ptr<GameObject> mLevelBackground;
        unique_ptr<UiButton> m_restartButton;
        unique_ptr<UiButton> m_goToMenuButton;
        unique_ptr <UiLabel> m_AboutMenuLabel;
        //
        unique_ptr<UiLabel> mScoresLabel;
        //
        void DrawFinalResultCubes();
    };
}

#endif /* GameOverScene_h */
