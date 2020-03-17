#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.h"
#include "Player/Player.h"
#include "UI/Button.h"
#include "Managers/SceneManager/SceneManager.h"
#include "Managers/SaveManager/SaveManager.h"

using namespace std;

const int HEIGHT = 600;
const int WIDTH = 1000;

// global variables
vector<Tree> allTrees = {};
vector<Enemy> enemies = {};
vector<Ally> allies = {};

int level = 1;
int numDeadTrees = 0;

int Score = 0;
string playerName = "";

double deltaTime;

Text levelText;
Text clearanceText;

LevelManager levelManager;
SoundManager soundManager;
SaveManager saveManager;

bool playerDead;

enum Scene;

// function prototypes
void createTrees(Window &, Texture *);

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

    // create textures for sprites
    auto *allyTexture = new Texture("../Assets/ally/",4,window);
    auto *enemyTexture = new Texture("../Assets/enemy/", 4, window);

    // create all trees:
    auto *treeTexture = new Texture("../Assets/environment/", 4, true, window);
    createTrees(window, treeTexture);

    // create player
    auto *playerTexture = new Texture("../Assets/hero/", 4, window);
    Player player(window.width/2,window.height/2,1,200, playerTexture,window,&levelManager); // create player
    playerDead = false;

    // make a color for text
    SDL_Color color = {255, 255, 255,255};
    Text treePercentage("100%", "../Assets/fonts/Seagram tfb.ttf", window.width-120,window.height-60,50,color,window);

    // initialize text class for printing out level
    levelText.init("level " + to_string(level), "../Assets/fonts/Seagram tfb.ttf", 10, 10, 40, color, window);
    // text for printing if level is cleared or failed, leave it empty for now
    color = {179, 24, 16, 255};
    clearanceText.init(" ", "../Assets/fonts/Seagram tfb.ttf", 50, window.height / 2 - 50, 70, color, window);

    // create Level Manager
    LevelManager tmp(allyTexture, enemyTexture, &window);
    levelManager = tmp;
    levelManager.startLevel();

    // create Scene Manager
    SceneManager sceneManager(window, background, &player, &treePercentage);
    // sceneManager.changeScene(Scene::highscores);

    // initialize save manager
    saveManager.init("data.save");

    // play music
    soundManager.addMusic("../Assets/sounds/Celestial.wav");
    soundManager.addSound("../Assets/sounds/punch.wav", "punch");
    soundManager.playMusic(-1);
    soundManager.mute(false);

    unsigned long oldTime = SDL_GetTicks();

    while(!quit){
        //calculate deltaTime:
        unsigned long delta = SDL_GetTicks() - oldTime;
        deltaTime = delta/1000.0;
        oldTime = SDL_GetTicks();

        // poll events:
        while(SDL_PollEvent(&event)){ // go through all events
            if(event.type == SDL_QUIT) { // if the X button is pressed - quit
                if(playerName != "")
                    saveManager.saveScore();
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    // save and exit if escape key is pressed
                    if(playerName != "")
                        saveManager.saveScore();
                    quit = true;
                }
            }
            if(event.type == SDL_WINDOWEVENT) { // change window width, and height if resized
                SDL_GetWindowSize(window.Window, &window.width, &window.height);
            }

            player.input(event);
            sceneManager.input(event);
        }
        // loop functions:

        SDL_RenderClear(window.Renderer); // clear surface
        levelManager.checkLevel(); // check if the level is cleared

        // draw all objects
        sceneManager.loop();

        //printText(treePercentage);
        clearanceText.draw();
        //update frame
        SDL_SetRenderDrawColor(window.Renderer, 0, 0, 0, 255); // set color for background
        SDL_RenderPresent(window.Renderer); // update frame
    }

    SDL_Quit();
    window.Close(); // close window

    delete enemyTexture;
    delete allyTexture;
    delete treeTexture;

    return 0;
}

void createTrees(Window &window, Texture *texture){
    int x = 5, y = 5;
    int treeWidth = 50;
    int treeHeight = 50;
    int id = 0;
    while(y <= window.height - treeHeight){
        Tree tree(x,y,treeWidth,treeHeight, id, texture, window);
        allTrees.push_back(tree);
        x += treeWidth + 5;
        id++;
        if(x > window.width-treeWidth){
            x = 5;
            y += treeHeight + 3;
        }
    }
}
