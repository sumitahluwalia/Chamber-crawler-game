#ifndef __BOOSTATTACK_H__
#define __BOOSTATTACK_H__

#include <string>

#include "potion.h"

class Player;

class BoostAttack: public Potion {
public:
    BoostAttack(int r, int c, std::string objectID);
    void usePotion(Player* player);
    ~BoostAttack();
};

#endif