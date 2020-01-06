//
// Created by MICHAEL_DOVE on 29. 12. 2019.
//

#ifndef SDL_GLOBAL_H
#define SDL_GLOBAL_H

#include <vector>

class Enemy;
class Tree;

extern vector<Tree> allTrees;
extern vector<Enemy> enemies;
extern int level;
extern int numDeadTrees;

#endif //SDL_GLOBAL_H