//
// Created by MICHAEL_DOVE on 6. 01. 2020.
//

#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Enemy/Enemy.h"

class Ally : public Enemy{
public:
    Ally(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window);

private:
    // TODO add all neccessery methods, and implement constructor
};




