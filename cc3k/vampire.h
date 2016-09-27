#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__

#include <string>

#include "player.h"

class Enemy;

class Vampire: public Player {
public:
    Vampire(std::string objectID);
    void adjustHP(float n);
    std::string attack(Enemy* enemy);
    ~Vampire();
};

#endif