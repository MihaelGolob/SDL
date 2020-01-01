//
// Created by MICHAEL_DOVE on 26. 12. 2019.
//

#ifndef SDL_TREE_H
#define SDL_TREE_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Window.h"

using namespace std;

class Tree {
public:
    Tree(int x, int y, int width, int height, string textureSource, Window window);
    void setOnFire();
    void extinguishFire();
    void draw();
    // getters
    int getX();
    int getY();
    int getW();
    int getH();
private:
    void loadTexture(string name);
    void renderTexture();
    void checkFire();

    int x, y, w, h;
    string textureSource;
    Window window;
    SDL_Texture *texture;

    int timeToBurn;
    bool dead;
    unsigned int timeOnFire;
    bool onFire;
};


#endif //SDL_TREE_H
