//
// Created by MICHAEL_DOVE on 29. 12. 2019.
//

#ifndef SDL_GLOBAL_H
#define SDL_GLOBAL_H

#include <vector>

#include "Managers/SoundManager/SoundManager.h"

class Enemy;
class Tree;
class Ally;
class Text;
class SaveManager;

extern SoundManager soundManager;
extern SaveManager saveManager;

extern vector<Tree> allTrees;

extern vector<Enemy> enemies;

extern vector<Ally> allies;
extern int level;
extern int numDeadTrees;
extern int Score;
extern string playerName;

extern double deltaTime;

extern Text levelText;
extern Text clearanceText;

extern bool playerDead;

enum Scene{menu, game, pause, howTo, dataInput, highscores};
enum Allign{left, right, center, none};

#endif //SDL_GLOBAL_H