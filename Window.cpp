//
// Created by MICHAEL_DOVE on 23. 10. 2019.
//

#include "Window.h"

void Window::InitWindow(string title, int width, int height) {
    //save variables:
    Window::title = title;
    Window::width = width;
    Window::height = height;
    // INITIALIZE SDL AND CREATE WINDOW
    if(SDL_Init(SDL_INIT_VIDEO) < 0){ // initialize SDL
        logError("SDL");
    }
    else{
        Window::Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN); // create window if there are no errors
        if (Window::Window == nullptr) {
            logError("WINDOW");
        }
    }

    SDL_SetWindowResizable(Window, SDL_TRUE);
}

void Window::InitRenderer() {
    // INITIALIZE RENDERER
    Window::Renderer = SDL_CreateRenderer(Window::Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // create renderer
    if (Window::Renderer == nullptr) {
        logError("RENDERER");
        Window::Close();
    }
}

void Window::InitImage(){
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        logError("SDL_IMAGE");
        SDL_Quit();
    }
}

void Window::Close() {
    SDL_DestroyWindow(Window::Window); // close window
    SDL_Quit(); // clean up everything
}

void Window::logError(string msg) {
    cout << msg << " ERROR: " << SDL_GetError() << endl;
}