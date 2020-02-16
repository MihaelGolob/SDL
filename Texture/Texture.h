//
// Created by MICHAEL_DOVE on 15. 02. 2020.
//

#pragma once

#include <vector>
#include <string>

#include <SDL2/SDL.h>

#include "../Window.h"

using namespace std;

class Texture {
public:
    Texture(string source, int numTextures, Window &window);
    Texture(string source, int numTextures, bool tree, Window &window);
    Texture() = default;

    SDL_Texture *getTexture(string side, int index);
private:
    void loadTexture(string side, vector<SDL_Texture*> &textures);
    void loadTreeTexture(string name, vector<SDL_Texture *> &textures);

    vector<SDL_Texture *> front;
    vector<SDL_Texture *> back;
    vector<SDL_Texture *> side;
    SDL_Texture *idle;

    vector<SDL_Texture *> fire;
    SDL_Texture *normal;
    SDL_Texture *chopped;

    Window window;

    string source;
    int numTextures;
};



