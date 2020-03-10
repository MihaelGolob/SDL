//
// Created by MICHAEL_DOVE on 2. 03. 2020.
//

#ifndef SDL_BUTTON_H
#define SDL_BUTTON_H

#include <SDL2/SDL.h>
#include <string>

#include "../Window.h"
#include "../global.h"

using namespace std;

class Button {
public:
    Button(int x, int y, string source, string sourcePress, void (*callback)(), Window &window);
    Button(Allign allign, int y, string source, string sourcePress, void (*callback)(), Window &window);
    void draw();
    void changeButtonState(bool state);
private:
    void checkMouse();
    void renderTexture();
    void loadTexture();

    void (*callback)();

    int x, y, w, h;
    bool hover;
    bool mouseButtonState;

    unsigned int timer;
    int coolDown;

    string source, sourcePress;
    SDL_Texture *norm, *press;
    Allign allign;
    Window window;
};


#endif //SDL_BUTTON_H
