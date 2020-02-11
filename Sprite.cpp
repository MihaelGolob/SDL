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

    numTex = 4;
    loadTexture("front", front, numTex);
    loadTexture("back", back, numTex);
    loadTexture("side", side, numTex);

    textureIndex = 0;
    textureTime = SDL_GetTicks();

    lastTime = SDL_GetTicks();

    id = counter;
    counter++;
}

Sprite::Sprite(int x, int y, float scale, int speed, string textureSource, Window &window) {
    this->x = x;
    this->y = y;
    this->scale = scale;
    this->speed = speed;
    this->window = window;
    texturePath = textureSource;

    this->h = 0;
    this->w = 0;

    this->speedX = 0;
    this->speedY = 0;

    destX = x;
    destY = y;

    numTex = 6;
    loadTexture("front", front, numTex);
    loadTexture("back", back, numTex);
    loadTexture("side", side, numTex);

    textureIndex = 0;
    textureTime = SDL_GetTicks();

    lastTime = SDL_GetTicks();

    id = counter;
    counter++;
}

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

void Sprite::loadTexture(string side, vector<SDL_Texture*> &textures, int numTex) {
    for(int i = 0; i < numTex; i++){
        string tmp = texturePath + "walk/" + side + "/" + side + to_string(i+1) + ".png";
        SDL_Texture *texture = IMG_LoadTexture(window.Renderer, tmp.c_str());
        if(texture == nullptr)
            window.logError("TEXTURE");

        textures.push_back(texture);

        // if the object was created without width and height, get them from the image
        if(w == 0 && h == 0){
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
            w *= scale;
            h *= scale;
        }
        if(idle == nullptr){
            string tmp = texturePath + "idle/front.png";
            idle = IMG_LoadTexture(window.Renderer, tmp.c_str());
            if(texture == nullptr)
                window.logError("TEXTURE");
        }
    }
}

void Sprite::renderTexture() {
    // draw texture
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if(orientation == 0)
        SDL_RenderCopyEx(window.Renderer, front[textureIndex], nullptr, &rect, 0, nullptr, flip);
    else if(orientation == 1)
        SDL_RenderCopyEx(window.Renderer, back[textureIndex], nullptr, &rect, 0, nullptr, flip);
    else if(orientation == 2)
        SDL_RenderCopyEx(window.Renderer, side[textureIndex], nullptr, &rect, 0, nullptr, flip);
    else
        SDL_RenderCopyEx(window.Renderer, idle, nullptr, &rect, 0, nullptr, flip);

}

void Sprite::changeTexture() {
    if(destY > y) {
        orientation = 0;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(front[0], nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    } else if (destY < y) {
        orientation = 1;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(back[0], nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    } else if (destX > x) {
        orientation = 2;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(side[0], nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    } else if (destX < x) {
        orientation = 2;
        flip = SDL_FLIP_HORIZONTAL;
        SDL_QueryTexture(side[0], nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    } else {
        orientation = 3;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(idle, nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }

    unsigned int curr = SDL_GetTicks();
    int delay = 1000.0/60 * 5;
    if(curr - textureTime > delay){
        textureIndex++;
        if(textureIndex > numTex-1)
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
    // TODO improve this move system!

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