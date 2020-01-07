//
// Created by MICHAEL_DOVE on 7. 01. 2020.
//

#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.h"

class Sprite{
public:
    Sprite(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window);
    void draw();

protected:
    void loadTexture(string path);
    void renderTexture();
    void changeTexture();
    void movement();
    void move();

    virtual void collision() = 0;


    int x, y, w, h;
    float scale;

    Window window;

    string texturePath;
    SDL_Texture *texture = nullptr;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    float speed;
    double speedX, speedY;
    int destX, destY;

    bool readyToMove = false;
    unsigned int lastTime;
    int moveDelay;
};