//
// Created by MICHAEL_DOVE on 6. 01. 2020.
//

#include "Ally.h"

Ally::Ally(int x, int y, float scale, int speed, int moveDelay, Texture *texture, Window &window) : Sprite(x, y, scale, speed, moveDelay, texture, window){
    visionDist = 40;
}

// PRIVATE METHODS:

void Ally::collision() {
    extinguishFire();
}

void Ally::loopMethods() {
    changeTarget();
    //findEnemyClose();
}

bool Ally::treeCollision(Tree t) {
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

void Ally::extinguishFire(){
    for(auto &t : allTrees){
        if(treeCollision(t))
            t.extinguishFire();
    }
}

// ENEMY TRACING:

void Ally::changeTarget() {
    Enemy e;
    if( findEnemyClose(e) ){
        moveTo(e.getX(), e.getY());
    }
}

bool Ally::findEnemyClose(Enemy &enemy) {
    for (auto &e : enemies) {
        float distance = calculateDist(e.getX(), e.getY());
        if(distance < 5) {
            if(!e.kill())
                die();
            return false;
        }
        else if(distance < visionDist){
            enemy = e;
            return true;
        }
    }
    return false;
}

float Ally::calculateDist(int posX, int posY) {
    float dx = abs(x - posX);
    float dy = abs(y - posY);
    float d = sqrt(pow(dx, 2) + pow(dy, 2));
    return d;
}

void Ally::die() {
    for (int i = 0; i < allies.size(); i++) {
        if(allies[i].id == id){
            allies.erase(allies.begin()+i);
            break;
        }
    }
}
