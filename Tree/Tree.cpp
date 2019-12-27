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

    loadTexture();
}

void Tree::draw() {
    renderTexture();
}

void Tree::loadTexture() {
    // load the png image to a texture
    texture = IMG_LoadTexture(window.Renderer, textureSource.c_str());
    if(texture == nullptr)
        window.logError("TEXTURE");
}

void Tree::renderTexture() {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(window.Renderer, texture, nullptr, &rect);
}
