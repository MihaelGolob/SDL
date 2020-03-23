//
// Created by MICHAEL_DOVE on 26. 12. 2019.
//

#ifndef SDL_TREE_H
#define SDL_TREE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Window.h"
#include "../global.h"
#include "../Texture/Texture.h"

using namespace std;

class Tree {
public:
    Tree(int x, int y, int width, int height, int ID, Texture *texture, Window window);
    void setOnFire();
    void extinguishFire();
    void plant();
    void draw();
    void reset();

    void onPause();
    void updatePauseTimer();

    // getters
    int getX();
    int getY();
    int getW();
    int getH();
    bool isDead();
    bool isOnFire();
private:
    void renderTexture();
    void checkFire();
    void spreadFire();

    int ID;

    int x, y, w, h;
    Window window;

    Texture *texture;

    int timeToBurn;
    bool dead;
    unsigned int timeOnFire;
    bool onFire;
    int fireDifference;

    unsigned int spreadTime;
    int spreadingFreq;
    int spreadDifference;

    int textureIndex;
    unsigned int textureTime;
};


#endif //SDL_TREE_H
