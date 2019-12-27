//
// Created by MICHAEL_DOVE on 9. 12. 2019.
//

#ifndef SDL_PLAYER_H
#define SDL_PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Window.h"

class Player {
public:
    Player(int x, int y, int width, int height, string texture, Window window);
    Player(int x, int y, float scale, string texture, Window window);
    void movement();
    void input(SDL_Event event);
    void draw();
private:
    void loadTexture(string side);
    void changeTexture();
    void renderTexture();
    void windowCollision();

    Window window;
    SDL_Texture *texture = nullptr;
    string texturePath;
    int x, y, w, h;
    float scale;
    bool up = false,down = false,left = false,right = false;
    int speed;
    bool flipHorizontal = false;
};


#endif //SDL_PLAYER_H
