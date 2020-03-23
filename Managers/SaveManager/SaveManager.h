//
// Created by MICHAEL_DOVE on 12. 03. 2020.
//

#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "../../global.h"

class SaveManager {
public:
    SaveManager();
    void init(const string &filePath);
    void saveScore();
    vector< pair<string,int> > bestScores(int numScores);
private:
    string filePath;
};


