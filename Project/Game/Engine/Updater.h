//
//  Updater.hpp
//  AbelixMiniclip
//
//  Created by Giorgi Abelix Abelashvili on 11/17/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

// updater to create main game loop
// A class which is main game class, which has a main game loop method, should implement this method
namespace engine {
    class Updater
    {
    public:
        virtual void Update() = 0;
        protected :
        ~Updater(){};
    };
}

