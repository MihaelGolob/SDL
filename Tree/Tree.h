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

using namespace std;

class Tree {
public:
    Tree(int x, int y, int width, int height, int ID, string textureSource, Window window);
    void setOnFire();
    void extinguishFire();
    void draw();
    // getters
    int getX();
    int getY();
    int getW();
    int getH();
    bool isDead();
    bool isOnFire();
private:
    void loadTexture(string name, SDL_Texture **texture);
    void loadTexture(string name, vector<SDL_Texture *> &textures, int num);
    void renderTexture();
    void checkFire();
    void spreadFire();

    int ID;

    int x, y, w, h;
    string textureSource;
    Window window;

    SDL_Texture *normal;
    SDL_Texture *choped;
    vector<SDL_Texture *> fire;

    int timeToBurn;
    bool dead;
    unsigned int timeOnFire;
    bool onFire;

    unsigned int spreadTime;
    int spreadingFreq;

    int textureIndex;
    unsigned int textureTime;
};


#endif //SDL_TREE_H
