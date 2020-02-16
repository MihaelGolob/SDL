//
// Created by MICHAEL_DOVE on 7. 01. 2020.
//

#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.h"
#include "Texture/Texture.h"

class Sprite{
public:
    Sprite(int x, int y, float scale, int speed, int moveDelay, Texture *texture, Window &window);
    Sprite(int x, int y, float scale, int speed, Texture *texture, Window &window);
    Sprite();
    void draw();

    int getX();
    int getY();
protected:
    void renderTexture();
    virtual void changeTexture();
    virtual void movement();
    void moveTo(int posX, int posY);
    void move();

    virtual void collision() = 0;
    virtual void loopMethods() = 0;


    int x, y, w, h;
    float scale;

    Window window;

    Texture *texture;

    int orientation = 0;
    int textureIndex;
    int numTex;
    unsigned int textureTime;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    float speed;
    double speedX, speedY;
    int destX, destY;

    bool readyToMove = false;
    unsigned int lastTime;
    int moveDelay;

    int id;
    static int counter;
};