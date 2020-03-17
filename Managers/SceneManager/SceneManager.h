//
// Created by MICHAEL_DOVE on 26. 02. 2020.
//

#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <sstream>

#include "../../Window.h"
#include "../../Text/Text.h"
#include "../../Player/Player.h"
#include "../../UI/Button.h"
#include "../../global.h"

class SceneManager {
public:
    SceneManager() = default;
    SceneManager(Window &window, SDL_Texture *backgroundTexture, Player *player, Text *percentage);

    void loop();
    void changeScene(Scene);
    void input(SDL_Event e);
private:
    void createButtons();
    void drawUIBackground();
    // callback methods:
    static void newGame();
    static void startButton();
    static void howToButton();
    static void backButton();
    static void highscores();

    void typeName(char c);
    char getChar(SDL_Event e);
    void parseHighScoreString();

    // draw methods
    void drawHowTo();
    void drawInput();
    void drawHighscoreBackground();

    void drawBackground();
    void drawObjects();
    void drawText();

    static Scene currScene;

    Window window;
    SDL_Texture *backgroundTexture;
    Player *player;
    Text *percentage;
    Text *scoreText;
    int oldNum;

    Text *nameText;

    vector<Text> highscoreText;
    string highscore = "";

    map<string, Button> buttons;
};

