//
// Created by MICHAEL_DOVE on 31. 12. 2019.
//

#ifndef SDL_TEXT_H
#define SDL_TEXT_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../Window.h"

class Text {
public:
    Text();
    Text(string text, string fontSource, int x, int y, int size, SDL_Color color, Window &window);
    void init(string text, string fontSource, int x, int y, int size, SDL_Color color, Window &window);
    void draw();
    void changeText(string text);
    void changePos(int x, int y);
private:
    void renderTexture();
    void loadNewTexture();

    int x, y;
    int w, h;
    int size;
    string text, fontSource;
    SDL_Texture *texture;
    SDL_Color color;
    TTF_Font *font;
    Window window;
};


#endif //SDL_TEXT_H
