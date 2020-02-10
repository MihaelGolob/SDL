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

    loadTexture("front", front, 6);
    loadTexture("side", side, 6);
    loadTexture("back", back, 6);

    textureTime = SDL_GetTicks();
    textureIndex = 1;

    extinguishTime = 1000;

    speed = 4;
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

void Player::loadTexture(string side, vector<SDL_Texture*> &textures, int numTex){
    // load the png image to a texture
    for(int i = 0; i < numTex; i++){
        string tmp = texturePath + "walk/" + side + "/" + side + to_string(i+1) + ".png";
        SDL_Texture *texture = IMG_LoadTexture(window.Renderer, tmp.c_str());
        if(texture == nullptr)
            window.logError("TEXTURE");

        textures.push_back(texture);

        // if the object was created without width and height, get them from the image
        if(w == 0 && h == 0){
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
            w *= scale;
            h *= scale;
        }
        if(idle == nullptr){
            string tmp = texturePath + "idle/front.png";
            idle = IMG_LoadTexture(window.Renderer, tmp.c_str());
            if(texture == nullptr)
                window.logError("TEXTURE");
        }
    }
}

void Player::changeTexture() {
    // check which button is pressed and change the texture and flip accordingly
    if(up){
        orientation = 1;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(back[0], nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }
    else if(down){
        orientation = 0;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(front[0], nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }
    else if(left){
        orientation = 2;
        flip = SDL_FLIP_HORIZONTAL;
        SDL_QueryTexture(side[0], nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }
    else if(right){
        orientation = 2;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(side[0], nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }
    else{
        orientation = 3;
        flip = SDL_FLIP_NONE;
        SDL_QueryTexture(idle, nullptr, nullptr, &w, &h);
        w *= scale;
        h *= scale;
    }

    unsigned int curr = SDL_GetTicks();
    int delay = 1000.0/60 * 5;
    if(curr - textureTime > delay){
        textureIndex++;
        if(textureIndex > 5)
            textureIndex = 0;
        textureTime = SDL_GetTicks();
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
        SDL_RenderCopyEx(window.Renderer, front[textureIndex], nullptr, &rect, 0, nullptr, flip);
    else if(orientation == 1)
        SDL_RenderCopyEx(window.Renderer, back[textureIndex], nullptr, &rect, 0, nullptr, flip);
    else if(orientation == 2)
        SDL_RenderCopyEx(window.Renderer, side[textureIndex], nullptr, &rect, 0, nullptr, flip);
    else
        SDL_RenderCopyEx(window.Renderer, idle, nullptr, &rect, 0, nullptr, flip);
}

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