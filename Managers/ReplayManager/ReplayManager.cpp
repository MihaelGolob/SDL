//
// Created by MICHAEL_DOVE on 17. 03. 2020.
//

#include "ReplayManager.h"

ReplayManager::ReplayManager() {
    counter = 0;
    delay = 500;
}

void ReplayManager::setPath(string path) {
    filePath = path;
}

void ReplayManager::recordMovement(int playerX, int playerY) {
    if (timer + delay <= SDL_GetTicks()) {
        ofstream out(filePath.c_str(), ios::app | ios::binary);

        point p;
        p.x = playerX;
        p.y = playerY;

        if (out.is_open()) {
            out.write((char *) &p, sizeof(p));
        }

        out.close();
        timer = SDL_GetTicks();
    }
}

void ReplayManager::clearFile() {
    ofstream out(filePath.c_str(), ofstream::trunc);
    out.close();
}

pair<int, int> ReplayManager::getCoords() {
    point p;

    ifstream in(filePath);
    in.seekg(counter * sizeof(point), ios::beg);
    in.read((char *) &p, sizeof(p));
    counter++;

    return make_pair(p.x, p.y);
}
