//
// Created by MICHAEL_DOVE on 26. 12. 2019.
//

#include "Tree.h"

Tree::Tree(int x, int y, int width, int height, string textureSource, Window window) {
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->textureSource = textureSource;
    this->window = window;

    timeToBurn = 10000;
    dead = false;
    onFire = false;

    normal = nullptr;
    fire = nullptr;
    choped = nullptr;
    loadTexture("tree", &normal);
    loadTexture("treeFire", &fire);
    loadTexture("treeDead", &choped);
}

void Tree::draw() {
    if(onFire && !dead)
        checkFire();
    renderTexture();
}

void Tree::setOnFire() {
    if(!onFire){
        onFire = true;
        timeOnFire = SDL_GetTicks();
        //loadTexture("treeFire");
    }
}

void Tree::extinguishFire() {
    if(onFire && !dead){
        onFire = false;
        //loadTexture("tree");
    }
}

int Tree::getX() {
    return x;
}

int Tree::getY(){
    return y;
}

int Tree::getW(){
    return w;
}

int Tree::getH() {
    return h;
}

bool Tree::isDead() {
    return dead;
}

// PRIVATE METHODS:

void Tree::loadTexture(string name, SDL_Texture **texture) {
    // load the png image to a texture
    string tx = textureSource + name + ".png";
    *texture = IMG_LoadTexture(window.Renderer, tx.c_str());

    if(*texture == nullptr)
        window.logError("TEXTURE");
}

void Tree::checkFire(){
    unsigned int curr = SDL_GetTicks();
    if(curr - timeOnFire >= timeToBurn){
        //loadTexture("treeDead");
        dead = true;
        numDeadTrees++;
    }
}

void Tree::renderTexture() {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if(onFire && !dead)
        SDL_RenderCopy(window.Renderer, fire, nullptr, &rect);
    else if(dead)
        SDL_RenderCopy(window.Renderer, choped, nullptr, &rect);
    else
        SDL_RenderCopy(window.Renderer, normal, nullptr, &rect);
}
