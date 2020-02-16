//
// Created by MICHAEL_DOVE on 15. 02. 2020.
//

#include "Texture.h"

Texture::Texture(string source, int numTextures, Window &window) {
    this->source = source;
    this->numTextures = numTextures;
    this->window = window;

    idle = nullptr;
    normal = nullptr;
    chopped = nullptr;

    loadTexture("front", front);
    loadTexture("back", back);
    loadTexture("side", side);
}

Texture::Texture(string source, int numTextures, bool tree, Window &window) {
    this->source = source;
    this->numTextures = numTextures;
    this->window = window;

    idle = nullptr;
    normal = nullptr;
    chopped = nullptr;

    loadTreeTexture("fire", fire);
}

SDL_Texture* Texture::getTexture(string side, int index) {
    if (side == "front") {
        return front[index];
    } else if (side == "back") {
        return back[index];
    } else if (side == "side") {
        return this->side[index];
    } else if (side == "chopped") {
        return chopped;
    } else if (side == "normal") {
        return normal;
    } else if (side == "fire") {
        return fire[index];
    }
    else {
        return idle;
    }
}

void Texture::loadTexture(string side, vector<SDL_Texture*> &textures) {
    for(int i = 0; i < numTextures; i++){
        string tmp = source + "walk/" + side + "/" + side + to_string(i+1) + ".png";
        SDL_Texture *texture = IMG_LoadTexture(window.Renderer, tmp.c_str());
        if(texture == nullptr)
            window.logError("TEXTURE");

        textures.push_back(texture);

        if(idle == nullptr){
            string tmp = source + "idle/front.png";
            idle = IMG_LoadTexture(window.Renderer, tmp.c_str());
            if(texture == nullptr)
                window.logError("TEXTURE");
        }
    }
}

void Texture::loadTreeTexture(string name, vector<SDL_Texture *> &textures) {
    // load the png image to a texture
    for (int i = 0; i < numTextures; i++) {
        string tx = source + name + to_string(i) + ".png";
        SDL_Texture *texture = IMG_LoadTexture(window.Renderer, tx.c_str());

        if(texture == nullptr)
            window.logError("TEXTURE");

        textures.push_back(texture);
    }

    if (chopped == nullptr && normal == nullptr) {
        string tx = source + "tree" + ".png";
        normal = IMG_LoadTexture(window.Renderer, tx.c_str());
        tx = source + "treeDead" + ".png";
        chopped = IMG_LoadTexture(window.Renderer, tx.c_str());
    }
}