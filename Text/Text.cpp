//
// Created by MICHAEL_DOVE on 31. 12. 2019.
//

#include "Text.h"

Text::Text(string text, string fontSource, int x, int y, int size, SDL_Color color, Window &window) {
    this->text = text;
    this->window = window;
    this->x = x;
    this->y = y;
    this->color = color;
    this->fontSource = fontSource;

    TTF_Font *font = TTF_OpenFont(fontSource.c_str(), size);
    if (font == nullptr)
        window.logError("FONT");

    SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surf == nullptr) {
        TTF_CloseFont(font);
        window.logError("FONT SURFACE");
    }

    texture = SDL_CreateTextureFromSurface(window.Renderer, surf);
    if(texture == nullptr)
        window.logError("FONT TEXTURE");

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);

    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
}

void Text::draw() {
    renderTexture();
}

void Text::changeText(string text) {
    this->text = text;
    loadNewTexture();
}

// PRIVATE METHODS:

void Text::renderTexture() {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(window.Renderer, texture, nullptr, &rect);
}

void Text::loadNewTexture() {
    TTF_Font *font = TTF_OpenFont(fontSource.c_str(), size);
    if (font == nullptr)
        window.logError("FONT");

    SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surf == nullptr) {
        TTF_CloseFont(font);
        window.logError("FONT SURFACE");
    }

    texture = SDL_CreateTextureFromSurface(window.Renderer, surf);
    if(texture == nullptr)
        window.logError("FONT TEXTURE");

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);

    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
}
