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

#include "../Window.h"
#include "../Tree/Tree.h"
#include "../global.h"

class Enemy {
public:
    Enemy(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window);
    bool collision(Tree);
    void draw();
private:
    void loadTexture(string side);
    void changeTexture();
    void renderTexture();
    void movement();
    void move();
    void startFire();

    int x, y, w, h;
    float scale;
    string textureSource;
    Window window;
    SDL_Texture *texture;
    int speed;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    int destX = 0, destY = 0;
    bool readyToMove = false;

    unsigned int lastTime;
    int moveDelay;
};


#endif //SDL_ENEMY_H
