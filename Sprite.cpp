//
// Created by MICHAEL_DOVE on 7. 01. 2020.
//

#include "Sprite.h"

Sprite::Sprite(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window) {
    this->x = x;
    this->y = y;
    this->scale = scale;
    this->speed = speed;
    this->moveDelay = moveDelay;
    this->window = window;
    texturePath = textureSource;

    this->h = 0;
    this->w = 0;

    this->speedX = 0;
    this->speedY = 0;

    destX = x;
    destY = y;

    loadTexture("front");
    lastTime = SDL_GetTicks();
}

void Sprite::draw() {
    changeTexture();
    renderTexture();
    movement();
}

// PRIVATE METHODS:

void Sprite::loadTexture(string side) {
    // load the png image to a texture
    string source = texturePath + side + ".png";
    texture = IMG_LoadTexture(window.Renderer, source.c_str());
    if(texture == nullptr)
        window.logError("TEXTURE");

    // if the object was created without width and height, get them from the image
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    w *= scale;
    h *= scale;
}

void Sprite::renderTexture() {
    // draw texture
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopyEx(window.Renderer, texture, nullptr, &rect, 0, nullptr, flip);
}

void Sprite::changeTexture() {
    if (destX > x) {
        loadTexture("side");
        flip = SDL_FLIP_NONE;
    } else if (destX < x) {
        loadTexture("side");
        flip = SDL_FLIP_HORIZONTAL;
    } else if(destY > y) {
        loadTexture("front");
        flip = SDL_FLIP_NONE;
    } else if (destY < y) {
        loadTexture("back");
        flip = SDL_FLIP_NONE;
    } else {
        loadTexture("front");
        flip = SDL_FLIP_NONE;
    }

}

void Sprite::movement() {
    unsigned int curr = SDL_GetTicks();
    if(readyToMove && curr - lastTime > moveDelay){
        destX = rand()%(window.width - w);
        destY = rand()%(window.height - h);
        readyToMove = false;

        float dx = abs(destX - x);
        float dy = abs(destY - y);
        double mag = sqrt(pow(dx, 2) + pow(dy, 2));

        speedX = (speed * dx) / mag;
        speedY = (speed * dy) / mag;
    }
    move();
}

void Sprite::move(){
    if (destX > x && destY < y) {
        x += speedX;
        y -= speedY;
    } else if (destX < x && destY < y) {
        x -= speedX;
        y -= speedY;
    } else if (destX < x && destY > y) {
        x -= speedX;
        y += speedY;
    } else if (destX > x && destY > y) {
        x += speedX;
        y += speedY;
    } else if (destX > x) {
        x += speed;
    } else if (destX < x) {
        x -= speed;
    } else if (destY < y) {
        y -= speed;
    } else if (destY > y) {
        y += speed;
    }

    if(x > destX - speed && x < destX + speed){
        if (y > destY - speed && y < destY + speed) {
            x = destX;
            y = destY;
            if(!readyToMove){
                lastTime = SDL_GetTicks();
                // collision
                collision();
            }
            readyToMove = true;
        }
    }
}