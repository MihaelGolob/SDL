//
// Created by MICHAEL_DOVE on 9. 12. 2019.
//

#include "Player.h"

Player::Player(int x, int y, int width, int height, string texture, Window &window) {
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->scale = 1;
    this->window = window;
    texturePath = texture;

    loadTexture("front");

    speed = 5;
}

Player::Player(int x, int y, float scale, string texture, Window &window) {
    this->x = x;
    this->y = y;
    this->w = 0;
    this->h = 0;
    this->scale = scale;
    this->window = window;
    texturePath = texture;

    loadTexture("front");

    speed = 5;
}

void Player::loadTexture(string side){
    // load the png image to a texture
    string tmp = texturePath + side + ".png";
    texture = IMG_LoadTexture(window.Renderer, tmp.c_str());
    if(texture == nullptr)
        window.logError("TEXTURE");

    // if the object was created without width and height, get them from the image
    if(w == 0 && h == 0){
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }
}

void Player::changeTexture() {
    // check which button is pressed and change the texture and flip accordingly
    if(up){
        loadTexture("back");
        flipHorizontal = false;
    }
    else if(down){
        loadTexture("front");
        flipHorizontal = false;
    }
    else if(left){
        loadTexture("side");
        flipHorizontal = true;
    }
    else if(right){
        loadTexture("side");
        flipHorizontal = false;
    }
    else{
        loadTexture("front");
        flipHorizontal = false;
    }
}

void Player::renderTexture(){
    // draw the texture and flip it if necessary
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if(!flipHorizontal)
        SDL_RenderCopy(window.Renderer, texture, nullptr, &rect);
    else
        SDL_RenderCopyEx(window.Renderer, texture, nullptr, &rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

void Player::movement() {
    // move player if button is pressed
    if(up)
        y -= speed;
    if(down)
        y += speed;
    if(left)
        x -= speed;
    if(right)
        x += speed;

    windowCollision();
}

void Player::windowCollision() {
    // stop the player if it is on the edge of the window

    if(x+w > window.width)
        x = window.width-w;
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    if(y+h > window.height)
        y = window.height-h;
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
    // enable to display a square around the object (for collisions)
    /*SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;

    SDL_SetRenderDrawBlendMode(window.Renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(window.Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(window.Renderer, &r);*/

    //draw the object
    changeTexture();
    renderTexture();
    movement();
}
