//
// Created by MICHAEL_DOVE on 26. 02. 2020.
//

#include "SceneManager.h"
SceneManager::SceneManager(Window &window, SDL_Texture *backgroundTexture, Player *player, Text *percentage) {
    this->window = window;
    this->backgroundTexture = backgroundTexture;
    this->player = player;
    this->percentage = percentage;

    scoreText = new Text(to_string(Score), "../Assets/fonts/Seagram tfb.ttf", 5, window.height - 70, 50, {255,255,255,255}, window);
    nameText = new Text(" ", "../Assets/fonts/Seagram tfb.ttf", window.width/2 - 250, window.height/2 - 35, 60, {0,0,0,255}, window);

    int offset = 10;
    for (int i = 0; i < 5; i++) {
        Text tmp(" ", "../Assets/fonts/Seagram tfb.ttf", 400, offset, 50, {255, 255, 255, 255}, window);
        highscoreText.push_back(tmp);
        offset += 80;
    }

    currScene = menu;
    createButtons();
}

void SceneManager::loop() {
    map<string,Button>::iterator it;
    if (!pause) {
        switch (currScene) {
            case Scene::menu:
                drawUIBackground();
                // draw buttons
                for (it = buttons.begin(); it != buttons.end(); it++) {
                    if(it->first[0] == 'u' && it->first[1] == 'i')
                        it->second.draw();
                }
                break;

            case Scene::game:
                // game play
                drawBackground();
                drawObjects();
                player->draw();
                drawText();

                // save players coordinates
                replayManager.recordMovement(player->getX(), player->getY());
                if(!gameStarted)
                    replayManager.clearFile();

                // draw back button
                for (it = buttons.begin(); it != buttons.end(); it++) {
                    if(it->first == "toMenu2")
                        it->second.draw();
                }
                gameStarted = true;
                break;

            case Scene::howTo:
                drawHowTo();
                // draw button
                for (it = buttons.begin(); it != buttons.end(); it++) {
                    if(it->first == "toMenu1")
                        it->second.draw();
                }
                break;

            case Scene::dataInput:
                drawInput();
                nameText->draw();
                // draw button
                for (it = buttons.begin(); it != buttons.end(); it++) {
                    if(it->first == "continue")
                        it->second.draw();
                }
                break;

            case Scene::highScores:
                drawHighscoreBackground();

                if(highscore.empty()) {
                    parseHighScoreString();
                }
                for (auto t : highscoreText)
                    t.draw();
                for (it = buttons.begin(); it != buttons.end(); it++) {
                    if(it->first == "toMenu1")
                        it->second.draw();
                }
                break;

            case Scene::replay:
                movePlayer();
                player->draw();
                for (it = buttons.begin(); it != buttons.end(); it++) {
                    if(it->first == "toMenu2")
                        it->second.draw();
                }
                break;
        }
    } else {
        for (auto &t : allTrees) {
            t.updatePauseTimer();
        }
    }
}

Scene SceneManager::currScene = Scene::menu;
unsigned long SceneManager::moveTimer = 0;

void SceneManager::changeScene(Scene s) {
    currScene = s;
}

Scene SceneManager::getCurrScene() {
    return currScene;
}

void SceneManager::input(SDL_Event e) {
    map<string,Button>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); it++) {
        it->second.changeButtonState(e.type == SDL_MOUSEBUTTONDOWN);
    }
    if(currScene == Scene::dataInput) {
        if (e.type == SDL_KEYDOWN) {
            typeName(getChar(e));
        }
    }
}

// PRIVATE METHODS:

void SceneManager::typeName(char c) {
    if (c != '/') {
        playerName += c;
    } else {
        if(playerName.size() > 0)
            playerName.pop_back();
    }

    if(playerName.size() == 0)
        playerName = " "; // so the texture doesn't cause error

    nameText->changeText(playerName);
}

// buttons
void SceneManager::createButtons() {
    Button ui1(Allign::center, 20, "../Assets/UI/Start.png", "../Assets/UI/StartPress.png", newGame, window);
    Button ui2(Allign::center, 140, "../Assets/UI/howButton.png", "../Assets/UI/howButtonPress.png", howToButton, window);
    Button ui3(Allign::center, 260, "../Assets/UI/highScores.png", "../Assets/UI/highscoresPress.png", highscores, window);
    Button ui4(Allign::center, 380, "../Assets/UI/replay.png", "../Assets/UI/replayPress.png", replayButton, window);
    buttons.insert(make_pair("ui1", ui1));
    buttons.insert(make_pair("ui2", ui2));
    buttons.insert(make_pair("ui3", ui3));
    buttons.insert(make_pair("ui4", ui4));

    Button toMenu1(Allign::center, window.height-100, "../Assets/UI/back.png", "../Assets/UI/backPress.png", backButton, window);
    buttons.insert(make_pair("toMenu1", toMenu1));
    Button toMenu2(Allign::right, 5, "../Assets/UI/menu.png", "../Assets/UI/menuPress.png", backButton, window);
    buttons.insert(make_pair("toMenu2", toMenu2));

    Button conToGame(Allign::center, window.height-100, "../Assets/UI/continue.png", "../Assets/UI/continuePress.png", startButton, window);
    buttons.insert(make_pair("continue", conToGame));
}

void SceneManager::newGame(){
    if(playerName == "")
        currScene = Scene::dataInput;
    else
        currScene = Scene::game;
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

void SceneManager::highscores() {
    currScene = Scene::highScores;
}

void SceneManager::replayButton() {
    currScene = Scene::replay;
    moveTimer = SDL_GetTicks();
}

// highscore
void SceneManager::drawHighscoreBackground() {
    SDL_Texture *texture = IMG_LoadTexture(window.Renderer, "../Assets/UI/highscoreBackground.png");
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

void SceneManager::parseHighScoreString() {
    vector<pair<string, int> > input = saveManager.bestScores(5);

    for (int i = 0; i < 5; i++) {
        string tmp = input[i].first + ": " + to_string(input[i].second);
        highscoreText[i].changeText(tmp);
    }
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

void SceneManager::drawInput() {
    SDL_Texture *texture = IMG_LoadTexture(window.Renderer, "../Assets/UI/input.png");
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

    scoreText->changeText(to_string(Score));
    scoreText->draw();
}

// replay
void SceneManager::movePlayer() {
    unsigned long curr = SDL_GetTicks();
    int delay = 500;
    if (curr - moveTimer >= delay) {
        pair<int,int> coord = replayManager.getCoords();
        player->move(coord.first, coord.second);

        moveTimer = SDL_GetTicks();
    }
}

// other
char SceneManager::getChar(SDL_Event e) {
    switch (e.key.keysym.sym) {
        case SDLK_a:
            return 'a';
        case SDLK_b:
            return 'b';
        case SDLK_c:
            return 'c';
        case SDLK_d:
            return 'd';
        case SDLK_e:
            return 'e';
        case SDLK_f:
            return 'f';
        case SDLK_g:
            return 'g';
        case SDLK_h:
            return 'h';
        case SDLK_i:
            return 'i';
        case SDLK_j:
            return 'j';
        case SDLK_k:
            return 'k';
        case SDLK_l:
            return 'l';
        case SDLK_m:
            return 'm';
        case SDLK_n:
            return 'n';
        case SDLK_o:
            return 'o';
        case SDLK_p:
            return 'p';
        case SDLK_q:
            return 'q';
        case SDLK_r:
            return 'r';
        case SDLK_s:
            return 's';
        case SDLK_t:
            return 't';
        case SDLK_u:
            return 'u';
        case SDLK_v:
            return 'v';
        case SDLK_w:
            return 'w';
        case SDLK_x:
            return 'x';
        case SDLK_y:
            return 'y';
        case SDLK_z:
            return 'z';
        case SDLK_0:
            return '0';
        case SDLK_1:
            return '1';
        case SDLK_2:
            return '2';
        case SDLK_3:
            return '3';
        case SDLK_4:
            return '4';
        case SDLK_5:
            return '5';
        case SDLK_6:
            return '6';
        case SDLK_7:
            return '7';
        case SDLK_8:
            return '8';
        case SDLK_9:
            return '9';
        case SDLK_SPACE:
            return '_';
        case SDLK_BACKSPACE:
            return '/';
        default:
            return '?';
    }
}
