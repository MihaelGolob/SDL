//
// Created by MICHAEL_DOVE on 27. 12. 2019.
//

#include "Enemy.h"

Enemy::Enemy(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window) : Sprite(x, y, scale, speed, moveDelay, textureSource, window){
    radius = 20;
}

bool Enemy::treeCollision(Tree t) {
    int tx = t.getX();
    int ty = t.getY();
    int th = t.getH();
    int tw = t.getW();

    if(x + w > tx && x < tx + tw){
        if(y < ty + th && y + h > ty){
            return true;
        }
    }
    return false;
}

void Enemy::kill() {
    if(!enemiesClose()){
        // destroy this enemy and remove it from array of enemies
        // TODO actually destroy the enemy!
        for (int i = 0; i < enemies.size(); i++) {
            if(enemies[i].x == x && enemies[i].y == y) {
                enemies.erase(enemies.begin()+i);
                break;
            }
        }
    }
    else{
        //TODO if enemies are close kill the player
        cout << "ANOTHER ENEMY WAS CLOSE, YOU ARE DEAD!" << endl;
    }
}

// GETTERS:

int Enemy::getX() {
    return x;
}

int Enemy::getY() {
    return y;
}

int Enemy::getW(){
    return w;
}

int Enemy::getH(){
    return h;
}

// PRIVATE METHODS:

void Enemy::collision(){
    startFire();
}

bool Enemy::enemiesClose() {
    for (auto &e : enemies) {
        // check for enemies in the radius
        if(e.x == x && e.y == y)
            continue; // ignore itself

        if (e.x <= x + w + radius && e.x + e.w >= x - radius) {
            if (e.y <= y + h + radius && e.y + e.h >= y - radius) {
                return true;
            }
        }
    }

    return false;
}

void Enemy::startFire() {
    int random = rand()%3;
    if(random == 0){
        for(auto &t : allTrees){
            if(treeCollision(t)){
                t.setOnFire();
                break;
            }
        }
    }
}