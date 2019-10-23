//
// Created by MICHAEL_DOVE on 23. 10. 2019.
//

#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
using namespace std;

class Window {
public:
    SDL_Window* InitWindow(string title, int width, int height);
    SDL_Renderer* InitRenderer();
    void Close();
    SDL_Window *Window = nullptr;

    SDL_Renderer *Renderer = nullptr;
    int width, height;
    string title;
};


#endif //SDL_WINDOW_H
