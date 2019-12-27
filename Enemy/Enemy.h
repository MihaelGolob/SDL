//
// Created by MICHAEL_DOVE on 27. 12. 2019.
//

#ifndef SDL_ENEMY_H
#define SDL_ENEMY_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Window.h"

class Enemy {
public:
    Enemy(int x, int y, float scale, string textureSource, Window window);
    void draw();
private:
    void loadTexture(string side);
    void changeTexture();
    void renderTexture();

    int x, y, w, h;
    float scale;
    string textureSource;
    Window window;
    int speed;
};


#endif //SDL_ENEMY_H
