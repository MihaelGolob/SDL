//
// Created by MICHAEL_DOVE on 26. 12. 2019.
//

#ifndef SDL_TREE_H
#define SDL_TREE_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Window.h"

using namespace std;

class Tree {
public:
    Tree(int x, int y, int width, int height, string textureSource, Window window);
    void draw();
private:
    void loadTexture();
    void renderTexture();

    int x, y, w, h;
    string textureSource;
    Window window;
    SDL_Texture *texture;
};


#endif //SDL_TREE_H
