//
//  AboutMenu.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/30/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef AboutMenu_h
#define AboutMenu_h

#include "IScene.h"
#include "LevelData.h"
#include "UiLabel.h"
#include "UiButton.h"

using namespace ui;

namespace scenes {
    class AboutMenuScene : public IScene
    {
    public:
        AboutMenuScene();
        ~AboutMenuScene();
        
        void Update() override;
    protected:
        void LoadScene() override;
        void UnloadScene() override;
        void DrawUi() override;
        
    private:
        unique_ptr<GameObject> mLevelBackground;
        unique_ptr<UiButton> m_BackButton;
        unique_ptr <UiLabel> m_AboutMenuLabel;
    };
}

#endif /* AboutMenu_h */
