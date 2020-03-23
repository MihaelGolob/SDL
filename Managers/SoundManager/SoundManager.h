//
// Created by MICHAEL_DOVE on 27. 02. 2020.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

class SoundManager {
public:
    SoundManager();
    void addMusic(string soundPath);
    void addSound(string soundPath, string name);
    void playMusic(int loops);
    void playSound(string name, int loops);
    void pause(int index);
    void mute(bool mute);

private:
    Mix_Music *music;
    vector< pair<string, Mix_Chunk *> > sounds;
};
