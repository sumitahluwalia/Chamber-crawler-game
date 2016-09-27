#ifndef __BOOSTDEF_H__
#define __BOOSTDEF_H__

#include <string>

#include "potion.h"

class Player;

class BoostDef : public Potion {
public:
    BoostDef(int r, int c, std::string objectID);
    void  usePotion(Player* player);
    ~BoostDef();
};

#endif