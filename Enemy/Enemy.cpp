//
// Created by MICHAEL_DOVE on 27. 12. 2019.
//

#include "Enemy.h"

Enemy::Enemy(int x, int y, float scale, int speed, int moveDelay, string textureSource, Window &window) {
    this->x = x;
    this->y = y;
    this->w = 0;
    this->h = 0;
    this->scale = scale;
    this->window = window;
    this->textureSource = textureSource;
    this->moveDelay = moveDelay;
    this->speed = speed;

    speedY = 0;
    speedX = 0;

    destX = x;
    destY = y;

    radius = 20;

    loadTexture("front");
    lastTime = SDL_GetTicks();
}

void Enemy::draw() {
    movement();
    changeTexture();
    renderTexture();
}

bool Enemy::collision(Tree t) {
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

void Enemy::kill() {
    if(!enemiesClose()){
        // destroy this enemy and remove it from array of enemies
        // TODO actually destroy the enemy!
        for (int i = 0; i < enemies.size(); i++) {
            if(enemies[i].x == x && enemies[i].y == y) {
                enemies.erase(enemies.begin()+i);
                break;
            }
        }
    }
    else{
        //TODO if enemies are close kill the player
        cout << "ANOTHER ENEMY WAS CLOSE, YOU ARE DEAD!" << endl;
    }
}

// GETTERS:

int Enemy::getX() {
    return x;
}

int Enemy::getY() {
    return y;
}

int Enemy::getW(){
    return w;
}

int Enemy::getH(){
    return h;
}

// PRIVATE METHODS:

void Enemy::loadTexture(string side) {
    // load the png image to a texture
    string source = textureSource + side + ".png";
    texture = IMG_LoadTexture(window.Renderer, source.c_str());
    if(texture == nullptr)
        window.logError("TEXTURE");

    // if the object was created without width and height, get them from the image
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    w *= scale;
    h *= scale;
}

void Enemy::changeTexture() {
    //cout << destY << " : " << y << "   " << destX << " : " << x << endl;
    if (destX > x) {
        loadTexture("side");
        flip = SDL_FLIP_NONE;
    } else if (destX < x) {
        loadTexture("side");
        flip = SDL_FLIP_HORIZONTAL;
    } else if(destY > y) {
        loadTexture("front");
        flip = SDL_FLIP_NONE;
    } else if (destY < y) {
        loadTexture("back");
        flip = SDL_FLIP_NONE;
    } else {
        loadTexture("front");
        flip = SDL_FLIP_NONE;
    }

}

void Enemy::renderTexture() {
    // draw the square which you are killed in (DEBUG ONLY)
    /*SDL_Rect r;
    r.x = x - radius;
    r.y = y - radius;
    r.w = 2*radius + w;
    r.h = 2*radius + h;

    SDL_RenderDrawRect(window.Renderer, &r);*/

    // draw texture
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopyEx(window.Renderer, texture, nullptr, &rect, 0, nullptr, flip);
}

void Enemy::movement() {
    unsigned int curr = SDL_GetTicks();
    if(readyToMove && curr - lastTime > moveDelay){
        destX = rand()%(window.width - w);
        destY = rand()%(window.height - h);
        readyToMove = false;

        float dx = abs(destX - x);
        float dy = abs(destY - y);
        double mag = sqrt(pow(dx, 2) + pow(dy, 2));

        speedX = (speed * dx) / mag;
        speedY = (speed * dy) / mag;
    }
    move();
}

void Enemy::move(){
    if (destX > x && destY < y) {
        x += speedX;
        y -= speedY;
    } else if (destX < x && destY < y) {
        x -= speedX;
        y -= speedY;
    } else if (destX < x && destY > y) {
        x -= speedX;
        y += speedY;
    } else if (destX > x && destY > y) {
        x += speedX;
        y += speedY;
    } else if (destX > x) {
        x += speed;
    } else if (destX < x) {
        x -= speed;
    } else if (destY < y) {
        y -= speed;
    } else if (destY > y) {
        y += speed;
    }

    if(x > destX - speed && x < destX + speed){
        if (y > destY - speed && y < destY + speed) {
            x = destX;
            y = destY;
//            cout << "readyToMove: " << readyToMove << endl;
            if(!readyToMove){
                lastTime = SDL_GetTicks();
                startFire();
            }
            readyToMove = true;
        }
    }
}

bool Enemy::enemiesClose() {
    for (auto &e : enemies) {
        // check for enemies in the radius
        if(e.x == x && e.y == y)
            continue; // ignore itself

        if (e.x <= x + w + radius && e.x + e.w >= x - radius) {
            if (e.y <= y + h + radius && e.y + e.h >= y - radius) {
                return true;
            }
        }
    }

    return false;
}

void Enemy::startFire() {
    int random = rand()%3;
    if(random == 0){
        for(auto &t : allTrees){
            if(collision(t)){
                t.setOnFire();
                break;
            }
        }
    }
}