//
// Created by MICHAEL_DOVE on 9. 12. 2019.
//

#include "Player.h"

Player::Player(int x, int y, int width, int height, Window window) {
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->window = window;

    speed = 5;
}

void Player::movement() {
    if(up)
        y -= speed;
    if(down)
        y += speed;
    if(left)
        x -= speed;
    if(right)
        x += speed;
}

void Player::input(SDL_Event event) {
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
            case SDLK_UP:
                up = true;
                break;
            case SDLK_DOWN:
                down = true;
                break;
            case SDLK_LEFT:
                left = true;
                break;
            case SDLK_RIGHT:
                right = true;
                break;
        }
    }
    if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym){
            case SDLK_UP:
                up = false;
                break;
            case SDLK_DOWN:
                down = false;
                break;
            case SDLK_LEFT:
                left = false;
                break;
            case SDLK_RIGHT:
                right = false;
                break;
        }
    }
}

void Player::draw() {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;

    SDL_SetRenderDrawBlendMode(window.Renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(window.Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(window.Renderer, &r);

    movement();
}
