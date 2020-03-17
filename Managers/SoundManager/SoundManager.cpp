//
// Created by MICHAEL_DOVE on 27. 02. 2020.
//

#include "SoundManager.h"

SoundManager::SoundManager() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) {
        cout << "SDL_Mixer could not be initialized!" << endl;
    }
}

void SoundManager::addMusic(string soundPath) {
    Mix_Music *sound = Mix_LoadMUS(soundPath.c_str());
    if (sound == nullptr) {
        cout << "failed to load music: '" << soundPath << "'" << endl;
    }
    music = sound;
}

void SoundManager::addSound(string soundPath, string name) {
    Mix_Chunk *sound = Mix_LoadWAV(soundPath.c_str());
    if (sound == nullptr) {
        cout << "failed to load sound: '" << soundPath << "'" << endl;
    }

    pair<string, Mix_Chunk *> tmp = make_pair(name, sound);
    sounds.push_back(tmp);
}

void SoundManager::playSound(string name, int loops) {
    for (int i = 0; i < sounds.size(); i++) {
        if (sounds[i].first == name) {
            if (Mix_Playing(i) == 0) {
                Mix_PlayChannel(i, sounds[i].second, loops);
            }
        }
    }
}

void SoundManager::playMusic(int loops){
    Mix_PlayMusic(music, loops);
}

void SoundManager::pause(int index) {
    if (Mix_PlayingMusic() != 0) {
        Mix_PauseMusic();
    }
}

void SoundManager::mute(bool mute) {
    if (mute) {
        Mix_Volume(-1, 0);
        Mix_VolumeMusic(0);
    } else {
        Mix_Volume(-1, MIX_MAX_VOLUME);
        Mix_VolumeMusic(MIX_MAX_VOLUME);
    }
}
