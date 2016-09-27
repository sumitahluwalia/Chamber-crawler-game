#ifndef __POISENHEALTH_H__
#define __POISENHEALTH_H__

#include <string>

#include "potion.h"

class Player;

class PoisonHealth: public Potion {
public:
    PoisonHealth(int r, int c, std::string objectID);
    void usePotion(Player* player);
    ~PoisonHealth();
};

#endif