#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "Window.h"

using namespace std;

int main(int argc, char *argv[]) {
    Window window;
    window.InitWindow("SDL", 1000, 600);
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
        //renderTexture(texture, ren, 0, 0); //image

        SDL_Rect rect; //rectangle
        rect.x = 250;
        rect.y = 150;
        rect.w = 200;
        rect.h = 200;
        SDL_SetRenderDrawColor(window.Renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(window.Renderer, &rect);

        SDL_RenderDrawLine(window.Renderer, 50, 0, 50, window.height); //line

        //update frame
        SDL_SetRenderDrawColor(window.Renderer, 0, 0, 0, 255);
        SDL_RenderPresent(window.Renderer);
    }

    window.Close();

    return 0;
}
