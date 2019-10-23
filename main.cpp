#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "Window.h"

using namespace std;

SDL_Texture *loadTexture(string path, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

int main(int argc, char *argv[]) {
    Window window;
    window.InitWindow("SDL", 1000, 600);
    window.InitRenderer();
    SDL_Event event;
    bool quit = false;

    //load media
    SDL_Texture *texture = loadTexture("cat.bmp", window.Renderer);

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

SDL_Texture *loadTexture(string path, SDL_Renderer *ren){
    SDL_Texture *tex = nullptr;
    SDL_Surface *image = SDL_LoadBMP(path.c_str());
    if(image == nullptr){
        cout << "ERROR: IMAGE COULD NOT BE LOADED! ... " << SDL_GetError() << endl;
        return nullptr;
    }

    tex = SDL_CreateTextureFromSurface(ren, image);
    SDL_FreeSurface(image);
    return tex;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    // setup destination rectangle
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    // query the texture to get its width and height to use
    SDL_QueryTexture(tex, nullptr, nullptr, &dest.w, &dest.h);
    // render
    SDL_RenderCopy(ren, tex, nullptr, &dest);
}
