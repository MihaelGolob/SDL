//
// Created by MICHAEL_DOVE on 26. 12. 2019.
//

#include "Tree.h"

Tree::Tree(int x, int y, int width, int height, int ID, string textureSource, Window window) {
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->ID = ID;
    this->textureSource = textureSource;
    this->window = window;

    spreadingFreq = rand()%3000 + 3000;

    timeToBurn = rand()%3000 + 9000;
    dead = false;
    onFire = false;

    normal = nullptr;
    choped = nullptr;

    textureIndex = 0;
    textureTime = SDL_GetTicks();

    loadTexture("tree", &normal);
    loadTexture("treeDead", &choped);
    loadTexture("fire", fire, 4);
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

bool Tree::isOnFire(){
    return onFire;
};

// PRIVATE METHODS:

void Tree::loadTexture(string name, SDL_Texture **texture) {
    // load the png image to a texture
    string tx = textureSource + name + ".png";
    *texture = IMG_LoadTexture(window.Renderer, tx.c_str());

    if(*texture == nullptr)
        window.logError("TEXTURE");
}

void Tree::loadTexture(string name, vector<SDL_Texture *> &textures, int num) {
    // load the png image to a texture
    for (int i = 0; i < num; i++) {
        string tx = textureSource + name + to_string(i) + ".png";
        SDL_Texture *texture = IMG_LoadTexture(window.Renderer, tx.c_str());

        if(texture == nullptr)
            window.logError("TEXTURE");

        textures.push_back(texture);
    }
}

void Tree::renderTexture() {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if(onFire && !dead)
        SDL_RenderCopy(window.Renderer, fire[textureIndex], nullptr, &rect);
    else if(dead)
        SDL_RenderCopy(window.Renderer, choped, nullptr, &rect);
    else
        SDL_RenderCopy(window.Renderer, normal, nullptr, &rect);

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
