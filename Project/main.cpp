//
//  main.cpp
//  Abelix_Test_C
//
//  Created by Giorgi Abelix Abelashvili on 9/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include <iostream>
#include "SceneManager.h"
using namespace scenes;


int main( int argc, char* args[] )
{
    SceneManager().Instance().RunWithScene(SceneEnum::kMainMenuScene);
    return 0;
}
