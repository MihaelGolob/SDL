//
// Created by MICHAEL_DOVE on 27. 12. 2019.
//

#ifndef SDL_ENEMY_H
#define SDL_ENEMY_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <vector>
#include <math.h>

#include "../Window.h"
#include "../Tree/Tree.h"
#include "../global.h"

class Enemy {
public:
    Enemy(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window);
    void kill();
    bool collision(Tree);
    void draw();

    int getX();
    int getY();
    int getW();
    int getH();
private:
    void loadTexture(string side);
    void changeTexture();
    void renderTexture();
    void movement();
    void move();

    bool enemiesClose();
    void startFire();

    int x, y, w, h;
    float scale;
    Window window;
    string textureSource;
    SDL_Texture *texture;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    float speed;

    double speedX, speedY;
    int destX = 0, destY = 0;

    bool readyToMove = false;
    unsigned int lastTime;
    int moveDelay;

    int radius;
};


#endif //SDL_ENEMY_H
