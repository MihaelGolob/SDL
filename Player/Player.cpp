//
// Created by MICHAEL_DOVE on 9. 12. 2019.
//

#include "Player.h"

Player::Player(int x, int y, float scale, float speed, Texture *texture, Window &window, LevelManager *levelManager) : Sprite(x,y,scale,speed,texture, window) {
    up = false;
    down = false;
    left = false;
    right = false;
    space = false;
    enter = false;

    this->levelManager = levelManager;
}

void Player::input(SDL_Event event) {
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
            case SDLK_w:
                up = true;
                break;
            case SDLK_s:
                down = true;
                break;
            case SDLK_a:
                left = true;
                break;
            case SDLK_d:
                right = true;
                break;
            case SDLK_SPACE:
                space = true;
                break;
            case SDLK_f:
                enter = true;
                break;
        }
    }
    if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym){
            case SDLK_w:
                up = false;
                break;
            case SDLK_s:
                down = false;
                break;
            case SDLK_a:
                left = false;
                break;
            case SDLK_d:
                right = false;
                break;
            case SDLK_SPACE:
                space = false;
                break;
            case SDLK_f:
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
    int deltaSpeed = speed*deltaTime;

    if(up){
        y -= deltaSpeed;
    }
    if(down){
        y += deltaSpeed;
    }

    if(left){
        x -= deltaSpeed;
    }
    if(right){
        x += deltaSpeed;
    }

    windowCollision();
}

// PRIVATE METHODS:

void Player::changeTexture() {
    // check which button is pressed and change the texture and flip accordingly
    if(up){
        orientation = 1;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(Sprite::texture->getTexture("back",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }
    else if(down){
        orientation = 0;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(Sprite::texture->getTexture("front",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }
    else if(left){
        orientation = 2;
        flip = SDL_FLIP_HORIZONTAL;
        SDL_QueryTexture(Sprite::texture->getTexture("side",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }
    else if(right){
        orientation = 2;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(Sprite::texture->getTexture("side",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }
    else{
        orientation = 3;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(Sprite::texture->getTexture("idle",0), nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }

    unsigned int curr = SDL_GetTicks();
    int delay = 1000.0/60 * 6;
    if(curr - textureTime > delay){
        textureIndex++;
        if(textureIndex > 3)
            textureIndex = 0;
        textureTime = SDL_GetTicks();
    }
}

void Player::loopMethods() {
    dead = playerDead;
}

void Player::extinguishFire(){
    for(auto &t : allTrees){
        if(treeCollision(t))
            t.extinguishFire();
    }
}

void Player::attackEnemy() {
    for (auto &e : enemies) {
        if(enemyCollision(e)){
            if(!e.kill()){
                playerDead = true;
                levelManager->failLevel("Enemies killed the player!");
            }
        }
    }
}

// collisions:

void Player::collision() {}

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