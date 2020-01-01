//
// Created by MICHAEL_DOVE on 27. 12. 2019.
//

#include "Enemy.h"

Enemy::Enemy(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window) {
    this->x = x;
    this->y = y;
    this->w = 0;
    this->h = 0;
    this->scale = scale;
    this->window = window;
    this->textureSource = textureSource;
    this->moveDelay = moveDelay;
    this->speed = speed;

    destX = x;
    destY = y;

    loadTexture("front");
    lastTime = SDL_GetTicks();
}

void Enemy::draw() {
    movement();
    changeTexture();
    renderTexture();
}

bool Enemy::collision(Tree t) {
    int tx = t.getX();
    int ty = t.getY();
    int th = t.getH();
    int tw = t.getW();

    if(x + w > tx && x < tx + tw){
        if(y < ty + th && y + h > ty){
            return true;
        }
    }
    return false;
}

// PRIVATE METHODS:

void Enemy::loadTexture(string side) {
    // load the png image to a texture
    string source = textureSource + side + ".png";
    texture = IMG_LoadTexture(window.Renderer, source.c_str());
    if(texture == nullptr)
        window.logError("TEXTURE");

    // if the object was created without width and height, get them from the image
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    w *= scale;
    h *= scale;
}

void Enemy::changeTexture() {

}

void Enemy::renderTexture() {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopyEx(window.Renderer, texture, nullptr, &rect, 0, nullptr, flip);
}

void Enemy::movement() {
    unsigned int curr = SDL_GetTicks();
    if(readyToMove && curr - lastTime > moveDelay){
        destX = rand()%(window.width - w);
        destY = rand()%(window.height - h);
        readyToMove = false;
    }
    move();
}

void Enemy::move(){
    if(x < destX)
        x += speed;
    else if (x > destX)
        x -= speed;

    if(y < destY)
        y += speed;
    else if(y > destY)
        y -= speed;

    if(x > destX-speed && x < destX+speed){
        if (y > destY - speed && y < destY + speed) {
            x = destX;
            y = destY;
            if(!readyToMove){
                lastTime = SDL_GetTicks();
                startFire();
            }
            readyToMove = true;
        }
    }
}

void Enemy::startFire() {
    int random = rand()%3;
    if(random == 0){
        for(auto &t : allTrees){
            if(collision(t)){
                t.setOnFire();
                break;
            }
        }
    }
}