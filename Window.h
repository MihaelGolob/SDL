//
// Created by MICHAEL_DOVE on 23. 10. 2019.
//

#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Window {
public:
    void InitWindow(string title, int width, int height);
    void InitRenderer();
    void InitImage();
    void Close();
    void logError(string msg);
    SDL_Window *Window = nullptr;

    SDL_Renderer *Renderer = nullptr;
    int width, height;
    string title;
};


#endif //SDL_WINDOW_H
