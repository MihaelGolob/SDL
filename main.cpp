#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.h"
#include "Player/Player.h"
#include "Tree/Tree.h"

const int HEIGHT = 600;
const int WIDTH = 1000;

using namespace std;

void drawBackground(Window);
void createTrees(Window &, vector<Tree> &, string);

int main(int argc, char *argv[]) {
    Window window; // initialize new Window class
    window.InitWindow("SDL", WIDTH, HEIGHT); // create new Window (more details in Window.cpp)
    window.InitRenderer(); // initialize renderer (more details in Window.cpp)
    window.InitImage();
    SDL_Event event; // new event
    bool quit = false;

    Player player(WIDTH/2,HEIGHT/2,2,"../Assets/hero/idle/",window); // create player

    vector<Tree> allTrees;
    createTrees(window, allTrees, "../Assets/environment/tree.png");

    while(!quit){
        // poll events:
        while(SDL_PollEvent(&event)){ // go through all events
            if(event.type == SDL_QUIT)  // if the X button is pressed - quit
            {
                quit = true;
            }
            if(event.type == SDL_WINDOWEVENT) {
                SDL_GetWindowSize(window.Window, &window.width, &window.height);
            }

            player.input(event);
        }
        // loop functions:
        SDL_RenderClear(window.Renderer); // clear surface

        //draw

        drawBackground(window);
        for(auto i : allTrees) {
            i.draw();
        }
        player.draw();

        //update frame
        SDL_SetRenderDrawColor(window.Renderer, 0, 0, 0, 255); // set color for background
        SDL_RenderPresent(window.Renderer); // update frame
    }

    window.Close(); // close window

    return 0;
}

void drawBackground(Window window){
    SDL_Texture *background;
    background = IMG_LoadTexture(window.Renderer, "../Assets/environment/grass1.png");

    if(background == nullptr) {
        window.logError("TEXTURE");
    }

    int x = 0, y = 0, w = 0, h = 0;
    SDL_QueryTexture(background, nullptr, nullptr, &w, &h);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    while(rect.y < window.height){
        SDL_RenderCopy(window.Renderer, background, nullptr, &rect);

        rect.x += w;
        if(rect.x >= window.width) {
            rect.x = 0;
            rect.y += h;
        }
    }
}

void createTrees(Window &window, vector<Tree> &allTrees, string source){
    int x = 0, y = 0;
    int treeWidth = 50;
    int treeHeight = 50;
    while(y <= HEIGHT - treeHeight){
        Tree tree(x,y,treeWidth,treeHeight, source, window);
        allTrees.push_back(tree);
        x += treeWidth + 5;
        if(x > WIDTH-treeWidth){
            x = 0;
            y += treeHeight + 3;
        }
    }
}
