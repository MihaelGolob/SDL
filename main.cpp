#include <iostream>
#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

using namespace std;

int main(int argc, char *argv[]) {
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        cout << "SDL could not be initialized!" << endl;
    else{
        //create window
        window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == nullptr)
            cout << "SDL window could not be created!" << endl;
        else{
            //get window surface
            surface = SDL_GetWindowSurface(window);
            //fill the surface
            SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
            //update the surface
            SDL_UpdateWindowSurface(window);
            //delay
            SDL_Delay(2000);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
/*
 * #include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int SDL_main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("first Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 100, 150, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);
    cout << "hello" << endl;

    return EXIT_SUCCESS;
}
 */