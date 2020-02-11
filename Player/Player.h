//
// Created by MICHAEL_DOVE on 9. 12. 2019.
//

#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Tree/Tree.h"
#include "../Enemy/Enemy.h"
#include "../Window.h"
#include "../global.h"

class Player : public Sprite{
public:
    Player(int x, int y, float scale, float speed, string texture, Window &window);
    void movement() override;
    void input(SDL_Event event);
private:
    void changeTexture() override;
    void collision() override;

    void extinguishFire();
    void attackEnemy();
    bool treeCollision(Tree);
    bool enemyCollision(Enemy);
    void windowCollision();

    // input variables:
    bool up, down, left, right, space, enter;
};
