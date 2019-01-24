//
//  MenuScene.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/19/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef MenuScene_h
#define MenuScene_h

#include "IScene.h"
#include <iostream>
#include "Sprite.h"
#include "UiButton.h"
using namespace std;
using namespace game;
using namespace ui;

namespace scenes {
    class MainMenuScene : public IScene
    {
    public:
        MainMenuScene();
        ~MainMenuScene();
        void Update() override;
    private:
        unique_ptr<GameObject> mLevelBackground;
        unique_ptr<GameObject> mTitle;
        unique_ptr<UiButton> m_playButton;
        unique_ptr<UiButton> m_infoButton;
        unique_ptr<UiButton> m_quitButton;
    protected:
        void LoadScene() override;
        void UnloadScene() override;
        void DrawUi() override;
    };
}

#endif /* MenuScene_hpp */
