//
// Created by MICHAEL_DOVE on 12. 03. 2020.
//

#include "SaveManager.h"

SaveManager::SaveManager() {}

void SaveManager::init(const string &filePath) {
    this->filePath = filePath;
}

void SaveManager::saveScore() {
    ofstream out(filePath, ios::app);
    out << playerName << " " << Score << endl;
    out.close();
}

vector< pair<string,int> > SaveManager::bestScores(int numScores) {
    vector< pair<string,int> > result(numScores);
    pair<string,int> max = make_pair("",0);
    int score;
    string name;
    ifstream in(filePath);

    while(in >> name >> score){
        if (result.size() == 0)
            result.push_back(make_pair(name, score));
        for (int i = 0; i < result.size(); i++) {
            if (score > result[i].second && i < numScores){
                result.insert( result.begin() + i, make_pair(name,score) );
                break;
            }
        }
    }

    while (result.size() > numScores)
        result.pop_back();

    in.close();
    return result;
}
