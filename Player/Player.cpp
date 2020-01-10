//
// Created by MICHAEL_DOVE on 9. 12. 2019.
//

#include "Player.h"

Player::Player(int x, int y, float scale, string texture, Window &window) {
    this->x = x;
    this->y = y;
    this->w = 0;
    this->h = 0;
    this->scale = scale;
    this->window = window;
    texturePath = texture;

    loadTexture("front", &front);
    loadTexture("side", &side);
    loadTexture("back", &back);
    extinguishTime = 1000;

    speed = 5;
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
            case SDLK_SPACE:
                space = true;
                break;
            case SDLK_RETURN:
                enter = true;
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
            case SDLK_SPACE:
                space = false;
                break;
            case SDLK_RETURN:
                enter = false;
                break;
        }
    }

    if (space) {
        extinguishFire();
    }
    if (enter) {
        attackEnemy();
    }
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

// PRIVATE METHODS:

void Player::extinguishFire(){
    for(auto &t : allTrees){
        if(treeCollision(t))
            t.extinguishFire();
    }
}

void Player::attackEnemy() {
    for (auto &e : enemies) {
        if(enemyCollision(e))
            e.kill();
    }
}

void Player::loadTexture(string side, SDL_Texture **texture){
    // load the png image to a texture
    string tmp = texturePath + side + ".png";
    *texture = IMG_LoadTexture(window.Renderer, tmp.c_str());
    if(*texture == nullptr)
        window.logError("TEXTURE");

    // if the object was created without width and height, get them from the image
    if(w == 0 && h == 0){
        SDL_QueryTexture(*texture, nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }
}

void Player::changeTexture() {
    // check which button is pressed and change the texture and flip accordingly
    if(up){
        orientation = 1;
        flip = SDL_FLIP_NONE;
    }
    else if(down){
        orientation = 0;
        flip = SDL_FLIP_NONE;
    }
    else if(left){
        orientation = 2;
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if(right){
        orientation = 2;
        flip = SDL_FLIP_NONE;
    }
    else{
        orientation = 0;
        flip = SDL_FLIP_NONE;
    }
}

void Player::renderTexture(){
    // draw the texture and flip it if necessary
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if(orientation == 0)
        SDL_RenderCopyEx(window.Renderer, front, nullptr, &rect, 0, nullptr, flip);
    else if(orientation == 1)
        SDL_RenderCopyEx(window.Renderer, back, nullptr, &rect, 0, nullptr, flip);
    else
        SDL_RenderCopyEx(window.Renderer, side, nullptr, &rect, 0, nullptr, flip);
}

// collisions:

bool Player::enemyCollision(Enemy e){
    int ex = e.getX();
    int ey = e.getY();
    int eh = e.getH();
    int ew = e.getW();

    if(x + w > ex && x < ex + ew){
        if(y < ey + eh && y + h > ey){
            return true;
        }
    }
    return false;
}

bool Player::treeCollision(Tree t) {
    int tx = t.getX();
    int ty = t.getY();
    int th = t.getH();
    int tw = t.getW();

    if(x + w > tx && x < tx + tw){
        if(y < ty + th && y + h > ty){
            return true;
        }
    }
    return false;
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