//
// Created by MICHAEL_DOVE on 17. 03. 2020.
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <SDL2/SDL.h>

#include "../../global.h"

struct point {
    int x;
    int y;
};

class ReplayManager {
public:
    ReplayManager();

    void setPath(string path);
    void recordMovement(int x, int y);
    void clearFile();

    pair<int, int> getCoords();
private:
    string filePath;
    int delay;
    unsigned int timer;
    int counter;
};
