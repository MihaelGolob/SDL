//
// Created by MICHAEL_DOVE on 25. 01. 2020.
//

#include "LevelManager.h"

LevelManager::LevelManager(string allySource, string enemySource, Window *window) {
    this->allySource = allySource;
    this->enemySource = enemySource;
    this->window = window;
}

void LevelManager::nextLevel() {
    bool allClear = true;
    // check if any tree is on fire
    for (auto t : allTrees) {
        if(t.isOnFire() && !t.isDead()){
            allClear = false;
            break;
        }
    }

    //check if any enemies are still alive or if a tree is on fire
    if(enemies.empty() && allClear){
        //if yes increase level and make it harder
        cout << "level clear" << endl;
        // TODO make it harder
        level++;
        levelText.changeText("Level: " + to_string(level));
        clearanceText.changeText("LEVEL COMPLETE!");

        // TODO spawn new enemies
        spawnEnemies(10);
    }

}

void LevelManager::spawnEnemies(int amount) {
    for (int i = 0; i < amount; i++) {
        int x = rand()%(window->width - 100);
        int y = rand()%(window->height - 100);
        int speed = rand()%3;
        int delay = rand()%2000;
        Enemy enemy(x, y, 2, speed, delay, enemySource, *window);
        enemies.push_back(enemy);
    }
}

void LevelManager::spawnAllies(int amount) {
    for (int i = 0; i < amount; i++) {
        int x = rand()%(window->width - 100);
        int y = rand()%(window->height - 100);
        int speed = rand()%3;
        int delay = rand()%2000;
        Ally ally(x, y, 1.5, speed, delay, allySource, *window);
        allies.push_back(ally);
    }
}