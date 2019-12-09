#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "Window.h"
#include "Player/Player.h"

using namespace std;

int main(int argc, char *argv[]) {
    Window window; // initialize new Window class
    window.InitWindow("SDL", 1000, 600); // create new Window (more details in Window.cpp)
    window.InitRenderer(); // initialize renderer (more details in Window.cpp)
    SDL_Event event; // new event
    bool quit = false;

    Player player(0,0,200,200,window);

    while(!quit){
        // poll events:
        while(SDL_PollEvent(&event)){ // go through all events
            if(event.type == SDL_QUIT)  // if the X button is pressed - quit
                quit = true;

            player.input(event);
        }
        // loop functions:
        SDL_RenderClear(window.Renderer); // clear surface

        //draw

        player.draw();

        //update frame
        SDL_SetRenderDrawColor(window.Renderer, 0, 0, 0, 255); // set color for background
        SDL_RenderPresent(window.Renderer); // update frame
    }

    window.Close(); // close window

    return 0;
}
