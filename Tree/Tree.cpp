//
// Created by MICHAEL_DOVE on 26. 12. 2019.
//

#include "Tree.h"

Tree::Tree(int x, int y, int width, int height, int ID, Texture *texture, Window window) {
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->ID = ID;
    this->texture = texture;
    this->window = window;

    spreadingFreq = rand()%3000 + 1500;

    timeToBurn = rand()%3000 + 7000;
    dead = false;
    onFire = false;

    textureIndex = 0;
    textureTime = SDL_GetTicks();
}

void Tree::draw() {
    if(onFire && !dead){
        checkFire();
        spreadFire();
    }
    renderTexture();
}

void Tree::setOnFire() {
    if(!onFire){
        onFire = true;
        timeOnFire = SDL_GetTicks();
        spreadTime = SDL_GetTicks();
        //loadTexture("treeFire");
    }
}

void Tree::extinguishFire() {
    if(onFire && !dead){
        onFire = false;
        Score += 5;
        //loadTexture("tree");
    }
}

void Tree::reset() {
    dead = false;
    onFire = false;
}

// getters

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

bool Tree::isOnFire(){
    return onFire;
};

// PRIVATE METHODS:

void Tree::renderTexture() {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if(onFire && !dead)
        SDL_RenderCopy(window.Renderer, texture->getTexture("fire", textureIndex), nullptr, &rect);
    else if(dead)
        SDL_RenderCopy(window.Renderer, texture->getTexture("chopped",0), nullptr, &rect);
    else
        SDL_RenderCopy(window.Renderer, texture->getTexture("normal", 0), nullptr, &rect);

    unsigned int curr = SDL_GetTicks();
    int delay = 1000.0/60 * 5;
    if(curr - textureTime > delay){
        textureIndex++;
        if(textureIndex > 3)
            textureIndex = 0;
        textureTime = SDL_GetTicks();
    }
}

void Tree::checkFire(){
    unsigned int curr = SDL_GetTicks();
    if(curr - timeOnFire >= timeToBurn){
        //loadTexture("treeDead");
        dead = true;
        Score -= 5;
        numDeadTrees++;
    }
}

void Tree::spreadFire() {
    unsigned int curr = SDL_GetTicks();
    if(curr - spreadTime > spreadingFreq){
        int random = rand()%4;
        // TODO make it more rigid (so it works with a different number of trees in a row)
        if(random == 0)
            allTrees[ID-18].setOnFire();
        else if(random == 1)
            allTrees[ID-1].setOnFire();
        else if(random == 2)
            allTrees[ID+1].setOnFire();
        else
            allTrees[ID+18].setOnFire();

        spreadTime = SDL_GetTicks();
    }
}
