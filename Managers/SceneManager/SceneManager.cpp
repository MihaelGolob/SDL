//
// Created by MICHAEL_DOVE on 26. 02. 2020.
//

#include "SceneManager.h"
SceneManager::SceneManager(Window &window, SDL_Texture *backgroundTexture, Player *player, Text *percentage) {
    this->window = window;
    this->backgroundTexture = backgroundTexture;
    this->player = player;
    this->percentage = percentage;

    currScene = menu;
    createButtons();
}

void SceneManager::loop() {
    map<string,Button>::iterator it;
    if (currScene == Scene::menu) {
        drawUIBackground();
        // draw buttons
        for (it = buttons.begin(); it != buttons.end(); it++) {
            if(it->first[0] == 'u' && it->first[1] == 'i')
                it->second.draw();
        }
    } else if (currScene == Scene::game) {
        // game play
        drawBackground();
        drawObjects();
        player->draw();
        drawText();

        // draw back button
        for (it = buttons.begin(); it != buttons.end(); it++) {
            if(it->first == "toMenu2")
                it->second.draw();
        }
    } else if (currScene == Scene::pause) {
        // TODO pause
    } else if (currScene == Scene::howTo) {
        drawHowTo();
        // draw button
        for (it = buttons.begin(); it != buttons.end(); it++) {
            if(it->first == "toMenu1")
                it->second.draw();
        }
    }
}

Scene SceneManager::currScene = Scene::menu;

void SceneManager::changeScene(Scene s) {
    currScene = s;
}

void SceneManager::mouseButtonState(bool state) {
    map<string,Button>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); it++) {
        it->second.changeButtonState(state);
    }
}

// PRIVATE METHODS:

// buttons
void SceneManager::createButtons() {
    Button ui1(Allign::center, 50, "../Assets/UI/Start.png", "../Assets/UI/StartPress.png", startButton, window);
    Button ui2(Allign::center, 200, "../Assets/UI/howButton.png", "../Assets/UI/howButtonPress.png", howToButton, window);
    buttons.insert(make_pair("ui1", ui1));
    buttons.insert(make_pair("ui2", ui2));

    Button toMenu1(Allign::center, window.height-100, "../Assets/UI/back.png", "../Assets/UI/backPress.png", backButton, window);
    buttons.insert(make_pair("toMenu1", toMenu1));
    Button toMenu2(Allign::right, 5, "../Assets/UI/menu.png", "../Assets/UI/menuPress.png", backButton, window);
    buttons.insert(make_pair("toMenu2", toMenu2));
}

void SceneManager::startButton(){
    currScene = Scene::game;
}

void SceneManager::howToButton() {
    currScene = Scene::howTo;
}

void SceneManager::backButton() {
    currScene = Scene::menu;
}

// main menu
void SceneManager::drawUIBackground() {
    SDL_Texture *texture = IMG_LoadTexture(window.Renderer, "../Assets/UI/background.png");
    if (texture == nullptr)
        window.logError("TEXTURE");

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = window.width;
    rect.h = window.height;

    SDL_RenderCopy(window.Renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

// how to play
void SceneManager::drawHowTo() {
    SDL_Texture *texture = IMG_LoadTexture(window.Renderer, "../Assets/UI/howToPlay.png");
    if (texture == nullptr)
        window.logError("TEXTURE");

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = window.width;
    rect.h = window.height;

    SDL_RenderCopy(window.Renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

// game
void SceneManager::drawBackground() {
    int x = 0, y = 0, w = 0, h = 0;
    SDL_QueryTexture(backgroundTexture, nullptr, nullptr, &w, &h);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    while(rect.y < window.height){
        SDL_RenderCopy(window.Renderer, backgroundTexture, nullptr, &rect);

        rect.x += w;
        if(rect.x >= window.width) {
            rect.x = 0;
            rect.y += h;
        }
    }
}

void SceneManager::drawObjects() {
    for(auto &t : allTrees) {
        t.draw();
    }
    for(auto &e : enemies){
        e.draw();
    }
    for (auto &a : allies) {
        a.draw();
    }
}

void SceneManager::drawText() {
    if(oldNum != numDeadTrees){
        oldNum = numDeadTrees;
        float perc = (float)(allTrees.size()-numDeadTrees)/(float)allTrees.size();
        int per = perc*100;
        string text = to_string(per);
        text += "%";
        percentage->changeText(text);
    }
    percentage->draw();
    levelText.draw();
}
