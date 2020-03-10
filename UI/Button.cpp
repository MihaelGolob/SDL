//
// Created by MICHAEL_DOVE on 2. 03. 2020.
//

#include "Button.h"

Button::Button(int x, int y, string source, string sourcePress, void (*callback)(), Window &window) {
    this->x = x;
    this->y = y;
    this->allign = none;

    this->callback = callback;

    this->source = source;
    this->sourcePress = sourcePress;
    this->window = window;

    mouseButtonState = false;

    coolDown = 100;

    loadTexture();
}

Button::Button(Allign allign, int y, string source, string sourcePress, void (*callback)(), Window &window) {
    this->x = 0;
    this->y = y;
    this->allign = allign;

    this->callback = callback;

    this->source = source;
    this->sourcePress = sourcePress;
    this->window = window;

    mouseButtonState = false;

    coolDown = 100;
    timer = SDL_GetTicks();

    loadTexture();
}

void Button::draw(){
    checkMouse();
    renderTexture();
}

void Button::changeButtonState(bool state) {
    mouseButtonState = state;
}

// PRIVATE METHODS:

void Button::loadTexture() {
    norm = IMG_LoadTexture(window.Renderer, source.c_str());
    if (norm == nullptr)
        window.logError("TEXTURE");

    press = IMG_LoadTexture(window.Renderer, sourcePress.c_str());
    if (press == nullptr)
        window.logError("TEXTURE");

    SDL_QueryTexture(norm, nullptr, nullptr, &w, &h);

    if (allign == center) {
        x = window.width/2 - w/2;
    } else if (allign == Allign::left) {
        x = 5;
    } else if (allign == Allign::right) {
        x = window.width - w - 5;
    }
}

void Button::renderTexture() {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;

    if(!hover)
        SDL_RenderCopyEx(window.Renderer, norm, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
    else
        SDL_RenderCopyEx(window.Renderer, press, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
}

void Button::checkMouse() {
    int mx, my;
    SDL_GetMouseState(&mx, &my);

    hover = mx >= x && mx <= x + w && my >= y && my <= y + h;
    if (mouseButtonState) {
        if(hover){
            // pressed = true;
            if (SDL_GetTicks() - timer >= coolDown) {
                callback();
                timer = SDL_GetTicks();
            }
        }
    }
}

