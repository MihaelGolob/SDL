//
// Created by MICHAEL_DOVE on 25. 01. 2020.
//

#pragma once

#include <vector>
#include <string>

#include "../../Tree/Tree.h"
#include "../../Window.h"
#include "../../global.h"
#include "../../Enemy/Enemy.h"
#include "../../Ally/Ally.h"
#include "../../Text/Text.h"

class LevelManager {
public:
    LevelManager() = default;
    LevelManager(Texture *allyTexture, Texture *enemyTexture, Window *window);
    void checkLevel();
    void startLevel();
    void failLevel(string msg);
    void newLevel();
private:
    void clearLevel();
    void spawnAllies(int amount);
    void spawnEnemies(int amount);

    unsigned int timer;
    int delay;
    bool waiting;

    Window *window;

    Texture *enemyTextures;
    Texture *allyTexture;
};


