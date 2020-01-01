#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.h"
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Text/Text.h"
#include "Tree/Tree.h"

using namespace std;

const int HEIGHT = 600;
const int WIDTH = 1000;

// global variables
vector<Tree> allTrees = {};
vector<Enemy> enemies = {};
int level;

void drawBackground(Window, SDL_Texture *);
void createTrees(Window &, string);
void createEnemies(int, Window &, string);

int main(int argc, char *argv[]) {
    srand(time(0)); // set seed for random

    Window window; // initialize new Window class
    window.InitWindow("SDL", WIDTH, HEIGHT); // create new Window (more details in Window.cpp)
    window.InitRenderer(); // initialize renderer (more details in Window.cpp)
    window.InitImage();
    window.InitText();
    SDL_Event event; // new event
    bool quit = false;

    // open background texture:
    SDL_Texture *background = IMG_LoadTexture(window.Renderer, "../Assets/environment/grass1.png");
    if(background == nullptr)
        window.logError("TEXTURE");

    // create all objects:
    createTrees(window, "../Assets/environment/");
    createEnemies(3, window, "../Assets/enemy/idle/");
    Player player(WIDTH/2,HEIGHT/2,2,"../Assets/hero/idle/",window); // create player

    // make a color for text
    SDL_Color color = {255,255,255,255};
    Text text("HELLO WORLD", "../Assets/fonts/raleway/Raleway-Light.ttf", 100,100,50,color,window);

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

        drawBackground(window, background);
        for(auto &e : enemies){
            e.draw();
        }
        for(auto &t : allTrees) {
            t.draw();
        }

        player.draw(); // drawn at the end so the player is always on top
        text.draw();

        //update frame
        SDL_SetRenderDrawColor(window.Renderer, 0, 0, 0, 255); // set color for background
        SDL_RenderPresent(window.Renderer); // update frame
    }

    SDL_Quit();
    window.Close(); // close window

    return 0;
}

void drawBackground(Window window, SDL_Texture *background){
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

void createTrees(Window &window, string source){
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

void createEnemies(int amount, Window &window, string source){
    for (int i = 0; i < amount; i++) {
        int x = rand()%(WIDTH - 100);
        int y = rand()%(HEIGHT - 100);
        int speed = rand()%6 + 3;
        int delay = rand()%8000 + 2000;
        Enemy enemy(x, y, 2, speed, delay, source, window);
        enemies.push_back(enemy);
    }
}
