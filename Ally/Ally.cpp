//
// Created by MICHAEL_DOVE on 6. 01. 2020.
//

#include "Ally.h"

Ally::Ally(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window) : Sprite(x, y, scale, speed, moveDelay, textureSource, window){
    visionDist = 50;
}

// PRIVATE METHODS:

void Ally::collision() {
    extinguishFire();
}

void Ally::loopMethods() {
    changeTarget();
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
    Enemy *e = &findEnemyClose();
    if(e != nullptr)
        moveTo(e->getX(), e->getY());
}

Enemy& Ally::findEnemyClose() {
    for (auto &e : enemies) {
        float distance = calculateDist(e.getX(), e.getY());
        if(distance < 5)
            e.kill();
        else if(distance < visionDist)
            return e;
    }
}

float Ally::calculateDist(int posX, int posY) {
    float dx = abs(x - posX);
    float dy = abs(y - posY);
    float d = sqrt(pow(dx, 2) + pow(dy, 2));
    return d;
}
