//
// Created by MICHAEL_DOVE on 29. 12. 2019.
//

#pragma once

#include <vector>

#include "Managers/SoundManager/SoundManager.h"

class Enemy;
class Tree;
class Ally;
class Text;
class SaveManager;
class ReplayManager;

extern SoundManager soundManager;
extern SaveManager saveManager;
extern ReplayManager replayManager;

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
extern bool gameStarted;
extern bool pause;

enum Scene{menu, game, howTo, dataInput, highScores, replay};
enum Allign{left, right, center, none};
