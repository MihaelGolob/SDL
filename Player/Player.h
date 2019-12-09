//
// Created by MICHAEL_DOVE on 9. 12. 2019.
//

#ifndef SDL_PLAYER_H
#define SDL_PLAYER_H

#include <SDL2/SDL.h>
#include "../Window.h"

class Player {
public:
    Player(int x, int y, int width, int height, Window window);
    void movement();
    void input(SDL_Event event);
    void draw();
private:
    Window window;
    int x, y, w, h;
    bool up,down,left,right;
    int speed;
};


#endif //SDL_PLAYER_H
