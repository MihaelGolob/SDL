//
// Created by MICHAEL_DOVE on 25. 01. 2020.
//

#pragma once

#include <vector>
#include <string>

#include "Tree/Tree.h"
#include "Window.h"
#include "global.h"
#include "Enemy/Enemy.h"
#include "Ally/Ally.h"
#include "Text/Text.h"

class LevelManager {
public:
    LevelManager(string allySource, string enemySource, Window *window);
    void nextLevel();
    void spawnEnemies(int amount);
    void spawnAllies(int amount);
private:
    Window *window;
    string enemySource;
    string allySource;
};


