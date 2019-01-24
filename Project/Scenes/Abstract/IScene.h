//
//  IScene.h
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/19/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef IScene_h
#define IScene_h


namespace scenes {
    class IScene
    {
    public:
        virtual void Update() = 0;
        virtual ~IScene() {}
    protected:
        virtual void LoadScene() = 0;
        virtual void UnloadScene() = 0;
        virtual void DrawUi() = 0;
    };
}

#endif /* IScene_h */
