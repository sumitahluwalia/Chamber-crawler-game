#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include <string>

#include "player.h"

class Enemy;

class Goblin: public Player {
public:
    Goblin(std::string objectID);
    ~Goblin();
    std::string attack(Enemy* enemy);
};

#endif