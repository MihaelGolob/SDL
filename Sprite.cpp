//
// Created by MICHAEL_DOVE on 7. 01. 2020.
//

#include "Sprite.h"

Sprite::Sprite(int x, int y, float scale, int speed, int moveDelay, Texture *texture, Window &window) {
    this->x = x;
    this->y = y;
    this->scale = scale;
    this->speed = speed;
    this->moveDelay = moveDelay;
    this->window = window;
    this->texture = texture;


    this->h = 0;
    this->w = 0;

    this->speedX = 0;
    this->speedY = 0;

    destX = x;
    destY = y;

    if(w == 0 && h == 0){
        SDL_QueryTexture(texture->getTexture("idle",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }

    textureIndex = 0;
    textureTime = SDL_GetTicks();

    lastTime = SDL_GetTicks();

    id = counter;
    counter++;
}

Sprite::Sprite(int x, int y, float scale, int speed, Texture *texture, Window &window) {
    this->x = x;
    this->y = y;
    this->scale = scale;
    this->speed = speed;
    this->window = window;
    this->texture = texture;

    this->h = 0;
    this->w = 0;

    this->speedX = 0;
    this->speedY = 0;

    destX = x;
    destY = y;

    if(w == 0 && h == 0){
        SDL_QueryTexture(texture->getTexture("idle",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }

    textureIndex = 0;
    textureTime = SDL_GetTicks();

    lastTime = SDL_GetTicks();

    id = counter;
    counter++;
}

Sprite::Sprite() = default;

int Sprite::counter = 0;

void Sprite::draw() {
    changeTexture();
    renderTexture();
    loopMethods();
    movement();
}

// GETTERS:

int Sprite::getX() {
    return x;
}

int Sprite::getY(){
    return y;
}

// PRIVATE METHODS:

void Sprite::renderTexture() {
    // draw texture
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if(orientation == 0)
        SDL_RenderCopyEx(window.Renderer, texture->getTexture("front", textureIndex), nullptr, &rect, 0, nullptr, flip);
    else if(orientation == 1)
        SDL_RenderCopyEx(window.Renderer, texture->getTexture("back", textureIndex), nullptr, &rect, 0, nullptr, flip);
    else if(orientation == 2)
        SDL_RenderCopyEx(window.Renderer, texture->getTexture("side", textureIndex), nullptr, &rect, 0, nullptr, flip);
    else
        SDL_RenderCopyEx(window.Renderer, texture->getTexture("idle", textureIndex), nullptr, &rect, 0, nullptr, flip);

}

void Sprite::changeTexture() {
    if(destY > y) {
        orientation = 0;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(Sprite::texture->getTexture("front",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    } else if (destY < y) {
        orientation = 1;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(Sprite::texture->getTexture("back",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    } else if (destX > x) {
        orientation = 2;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(Sprite::texture->getTexture("side",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    } else if (destX < x) {
        orientation = 2;
        flip = SDL_FLIP_HORIZONTAL;
        SDL_QueryTexture(Sprite::texture->getTexture("side",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    } else {
        orientation = 3;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(Sprite::texture->getTexture("front",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }

    unsigned int curr = SDL_GetTicks();
    int delay = 1000.0/60 * 5;
    if(curr - textureTime > delay){
        textureIndex++;
        if(textureIndex > texture->getNumTex()-1)
            textureIndex = 0;
        textureTime = SDL_GetTicks();
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
        if(speedX < 1)
            speedX = 1;
        if(speedY < 1)
            speedY = 1;
    }
    move();
}

void Sprite::moveTo(int posX, int posY){
    destX = posX;
    destY = posY;
    readyToMove = false;

    float dx = abs(destX - x);
    float dy = abs(destY - y);
    double mag = sqrt(pow(dx, 2) + pow(dy, 2));

    speedX = (speed * dx) / mag;
    speedY = (speed * dy) / mag;
    if(speedX < 1)
        speedX = 1;
    if(speedY < 1)
        speedY = 1;
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

    // on position
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