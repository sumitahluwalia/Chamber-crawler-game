#ifndef __WOUNDATTACK_H__
#define __WOUNDATTACK_H__

#include <string>

#include "potion.h"

class Player;

class WoundAttack: public Potion {
public:
    WoundAttack(int r, int c, std::string objectID);
    void usePotion(Player* player);
    ~WoundAttack();
};

#endif