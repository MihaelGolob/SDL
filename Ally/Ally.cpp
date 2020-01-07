//
// Created by MICHAEL_DOVE on 6. 01. 2020.
//

#include "Ally.h"

Ally::Ally(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window) : Sprite(x, y, scale, speed, moveDelay, textureSource, window){}

void Ally::collision() {
    extinguishFire();
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
