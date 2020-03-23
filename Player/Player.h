//
// Created by MICHAEL_DOVE on 9. 12. 2019.
//

#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Managers/LevelManager/LevelManager.h"
#include "../Tree/Tree.h"
#include "../Enemy/Enemy.h"
#include "../Window.h"
#include "../global.h"

class Player : public Sprite{
public:
    Player(int x, int y, float scale, float speed, Texture *texture, Window &window, LevelManager *levelManager);
    void movement() override;
    void input(SDL_Event event);
    void move(int x, int y);
private:
    void changeTexture() override;
    void collision() override;
    void loopMethods() override;

    void extinguishFire();
    void attackEnemy();
    void plantTree();
    bool treeCollision(Tree);
    bool enemyCollision(Enemy);
    void windowCollision();

    // input variables:
    bool up, down, left, right, space, enter, l;
    LevelManager *levelManager;
};
