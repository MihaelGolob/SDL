#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "Window.h"

using namespace std;

int main(int argc, char *argv[]) {
    Window window; // initialize new Window class
    window.InitWindow("SDL", 1000, 600); // create new Window (more details in Window.cpp)
    window.InitRenderer(); // initialize renderer (more details in Window.cpp)
    SDL_Event event; // new event
    bool quit = false;

    while(!quit){
        // poll events:
        while(SDL_PollEvent(&event)){ // go through all events
            if(event.type == SDL_QUIT)  // if the X button is pressed - quit
                quit = true;
        }

        // loop functions:
        SDL_RenderClear(window.Renderer); // clear surface

        //draw

        SDL_Rect rect; // new rectangle
        // rect coordinates and size
        rect.x = 250;
        rect.y = 150;
        rect.w = 200;
        rect.h = 200;
        SDL_SetRenderDrawColor(window.Renderer, 255, 255, 255, 255); // set color for SDL Draw
        SDL_RenderDrawRect(window.Renderer, &rect); // draw rectangle

        SDL_RenderDrawLine(window.Renderer, 50, 0, 50, window.height); // draw line

        //update frame
        SDL_SetRenderDrawColor(window.Renderer, 0, 0, 0, 255); // set color for background
        SDL_RenderPresent(window.Renderer); // update frame
    }

    window.Close(); // close window

    return 0;
}
