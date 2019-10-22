#include <iostream>
#include <string>
#include <SDL2/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;

using namespace std;

SDL_Window* InitWindow();
SDL_Renderer* InitRenderer(SDL_Window *window);
SDL_Surface* LoadImage(string path);
SDL_Texture *loadTexture(string path, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void Close(SDL_Window *window);

int main(int argc, char *argv[]) {
    SDL_Window *window = InitWindow();
    SDL_Renderer *ren = InitRenderer(window);
    SDL_Event event;
    bool quit = false;

    //load media
    SDL_Texture *texture = loadTexture("cat.bmp", ren);

    while(!quit){
        // poll events:
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                quit = true;
        }

        // loop functions:
        //SDL_BlitSurface(image, nullptr, surface, nullptr);
        SDL_RenderClear(ren);
        renderTexture(texture, ren, 0, 0);
        SDL_RenderPresent(ren);
    }

    Close(window);

    return 0;
}

SDL_Window* InitWindow(){
    // INITIALIZE SDL AND CREATE WINDOW
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "ERROR: SDL COULD NOT BE INITIALIZED!" << endl;
    }
    else{
        SDL_Window *window = nullptr;
        window = SDL_CreateWindow("SDL window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            cout << "ERROR: WINDOW COULD NOT BE CREATED!" << endl;
        } else
            return window;
    }
}

SDL_Renderer* InitRenderer(SDL_Window *window){
    // INITIALIZE RENDERER
    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        cout << "ERROR: RENDERER FAILED TO INITIALIZE! ... " << SDL_GetError() << endl;
        Close(window);
        return nullptr;
    }
    else
        return ren;
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

SDL_Surface* LoadImage(string path){
    // LOAD IMAGE
    SDL_Surface *image = SDL_LoadBMP(path.c_str());
    if(image == nullptr)
        cout << "ERROR: IMAGE COULD NOT BE LOADED! ... " << SDL_GetError() << endl;
}

void Close(SDL_Window *window){
    // CLOSE WINDOW AND EXIT
    SDL_DestroyWindow(window);
    SDL_Quit();
}
