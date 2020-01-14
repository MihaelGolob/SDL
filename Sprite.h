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

class Sprite{
public:
    Sprite(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window);
    void draw();

protected:
    void loadTexture(string side, vector<SDL_Texture*> &textures, int numTex);
    void renderTexture();
    void changeTexture();
    void movement();
    void move();

    virtual void collision() = 0;


    int x, y, w, h;
    float scale;

    Window window;

    vector<SDL_Texture *> front;
    vector<SDL_Texture *> back;
    vector<SDL_Texture *> side;
    SDL_Texture *idle = nullptr;

    int orientation = 0;
    string texturePath;
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
};