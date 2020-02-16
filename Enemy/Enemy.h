//
// Created by MICHAEL_DOVE on 27. 12. 2019.
//

#ifndef SDL_ENEMY_H
#define SDL_ENEMY_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <vector>
#include <math.h>

#include "../Window.h"
#include "../Tree/Tree.h"
#include "../global.h"
#include "../Sprite.h"
#include "../Player/Player.h"

class Enemy : public Sprite{
public:
    Enemy(int x, int y, float scale, int speed, int moveDelay, Texture *texture, Window &window);
    Enemy();
    bool kill();
    bool treeCollision(Tree);

    int getX();
    int getY();
    int getW();
    int getH();
private:
    void collision() override;
    void loopMethods() override;

    bool enemiesClose();
    void startFire();

    int radius;
};


#endif //SDL_ENEMY_H
