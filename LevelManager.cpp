//
// Created by MICHAEL_DOVE on 25. 01. 2020.
//

#include "LevelManager.h"

LevelManager::LevelManager(Texture *allyTexture, Texture *enemyTexture, Window *window) {
    this->allyTexture = allyTexture;
    this->enemyTextures = enemyTexture;
    this->window = window;

    delay = 3000;
    waiting = false;
}

void LevelManager::startLevel() {
    clearLevel();
    switch (level) {
        case 1:
            spawnEnemies(10);
            spawnAllies(2);
            break;
        case 2:
            spawnEnemies(5);
            spawnAllies(2);
            break;
        case 3:
            spawnEnemies(7);
            spawnAllies(1);
            break;
        case 4:
            spawnEnemies(9);
            spawnAllies(1);
            break;
    }
}

void LevelManager::clearLevel() {
    enemies.clear();
    allies.clear();
    for (auto &t : allTrees) {
        t.reset();
    }
    numDeadTrees = 0;
}

void LevelManager::checkLevel() {
    bool allClear = true;
    // check if any tree is on fire
    for (auto t : allTrees) {
        if(t.isOnFire() && !t.isDead()){
            allClear = false;
            break;
        }
    }

    //check if any enemies are still alive or if a tree is on fire
    if(!waiting && enemies.empty() && allClear){
        //if yes increase level and make it harder
        cout << "level clear" << endl;
        level++;
        // display level complete text
        levelText.changeText("Level: " + to_string(level));
        clearanceText.changeText("LEVEL COMPLETE!");

        // start timer for new level
        timer = SDL_GetTicks();
        waiting = true;
    }

    if(!waiting && (float)(allTrees.size()-numDeadTrees)/(float)allTrees.size() < 0.7) {
        clearanceText.changeText("LEVEL FAILED!");
        timer = SDL_GetTicks();
        waiting = true;
    }

    if (waiting) {
        if (SDL_GetTicks() - timer >= delay) {
            startLevel();
            waiting = false;
            clearanceText.changeText(" ");
        }
    }

}

void LevelManager::spawnEnemies(int amount) {
    for (int i = 0; i < amount; i++) {
        int x = rand()%(window->width - 100);
        int y = rand()%(window->height - 100);
        int speed = rand()%3 + 1;
        int delay = rand()%2000;
        Enemy enemy(x, y, 2, speed, delay, enemyTextures, *window);
        enemies.push_back(enemy);
    }
}

void LevelManager::spawnAllies(int amount) {
    for (int i = 0; i < amount; i++) {
        int x = rand()%(window->width - 100);
        int y = rand()%(window->height - 100);
        int speed = rand()%3 + 1;
        int delay = rand()%2000;
        Ally ally(x, y, 1.5, speed, delay, allyTexture, *window);
        allies.push_back(ally);
    }
}