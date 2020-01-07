//
// Created by MICHAEL_DOVE on 6. 01. 2020.
//

#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Enemy/Enemy.h"
#include "../Sprite.h"

class Ally : public Sprite{
public:
    Ally(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window);

private:
    void extinguishFire();
    bool treeCollision(Tree tree);
    void collision();
};




