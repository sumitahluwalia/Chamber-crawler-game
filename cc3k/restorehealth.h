#ifndef __RESTOREHEALTH_H__
#define __RESTOREHEALTH_H__

#include <string>

#include "potion.h"

class Player;

class RestoreHealth: public Potion {
public:
    RestoreHealth(int r, int c, std::string objectID);
    void usePotion(Player* player);
    ~RestoreHealth();
};

#endif