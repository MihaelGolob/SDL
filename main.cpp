#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "Window.h"

using namespace std;

void drawGrid(Window window, int rows, int columns);

int main(int argc, char *argv[]) {
    Window window;
    window.InitWindow("SDL window!", 800, 800);
    window.InitRenderer();
    SDL_Event event;
    bool quit = false;

    while(!quit){
        // poll events:
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                quit = true;
        }

        // loop functions:
        //clear surface
        SDL_RenderClear(window.Renderer);

        //draw

        SDL_SetRenderDrawColor(window.Renderer, 255, 255, 255, 255);
        drawGrid(window, 10,10);

        //update frame
        SDL_SetRenderDrawColor(window.Renderer, 13, 95, 110, 255);
        SDL_RenderPresent(window.Renderer);
    }

    window.Close();

    return 0;
}

void drawGrid(Window window, int rows, int columns){
    int x1 = 0, y1 = 0;
    int x2 = window.width, y2 = 0;
    for(int i = 0; i < rows; i++){
        y1 += window.height/rows;
        y2 = y1;
        SDL_RenderDrawLine(window.Renderer, x1, y1, x2, y2);
    }
    y1 = 0;
    y2 = window.height;
    x1 = 0;
    for(int i = 0; i < columns; i++){
        x1 += window.width/columns;
        x2 = x1;
        SDL_RenderDrawLine(window.Renderer, x1, y1, x2, y2);
    }
}
