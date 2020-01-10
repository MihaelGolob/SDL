//
// Created by MICHAEL_DOVE on 9. 12. 2019.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Tree/Tree.h"
#include "../Enemy/Enemy.h"
#include "../Window.h"
#include "../global.h"

class Player {
public:
    Player(int x, int y, float scale, string texture, Window &window);
    void movement();
    void input(SDL_Event event);
    void draw();
private:
    void extinguishFire();
    void loadTexture(string side, SDL_Texture **texture);
    void changeTexture();
    void renderTexture();
    void attackEnemy();
    bool treeCollision(Tree);
    bool enemyCollision(Enemy);
    void windowCollision();

    Window window;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Texture *front = nullptr;
    SDL_Texture *side = nullptr;
    SDL_Texture *back = nullptr;
    int orientation = 0;
    string texturePath;
    float scale;


    int x, y, w, h;
    int speed;
    // input variables:
    bool up = false, down = false, left = false, right = false, space = false, enter = false;

    int extinguishTime;
    unsigned int startExting;
};
