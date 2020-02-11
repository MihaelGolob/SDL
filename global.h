//
// Created by MICHAEL_DOVE on 29. 12. 2019.
//

#ifndef SDL_GLOBAL_H
#define SDL_GLOBAL_H

#include <vector>

class Enemy;
class Tree;
class Ally;
class Text;

extern vector<Tree> allTrees;
extern vector<Enemy> enemies;
extern vector<Ally> allies;

extern int level;
extern int numDeadTrees;

extern double deltaTime;

extern Text levelText;
extern Text clearanceText;

#endif //SDL_GLOBAL_H