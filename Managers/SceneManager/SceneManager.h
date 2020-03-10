//
// Created by MICHAEL_DOVE on 26. 02. 2020.
//

#pragma once

#include <SDL2/SDL.h>
#include <map>

#include "../../Window.h"
#include "../../Text/Text.h"
#include "../../Player/Player.h"
#include "../../UI/Button.h"

class SceneManager {
public:
    SceneManager() = default;
    SceneManager(Window &window, SDL_Texture *backgroundTexture, Player *player, Text *percentage);

    void loop();
    void changeScene(Scene);
    void mouseButtonState(bool state);
private:
    void createButtons();
    void drawUIBackground();
    // callback methods:
    static void startButton();
    static void howToButton();
    static void backButton();

    void drawHowTo();

    void drawBackground();
    void drawObjects();
    void drawText();

    static Scene currScene;

    Window window;
    SDL_Texture *backgroundTexture;
    Player *player;
    Text *percentage;
    int oldNum;

    map<string, Button> buttons;
};

