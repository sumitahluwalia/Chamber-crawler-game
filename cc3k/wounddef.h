#ifndef __WOUNDDEF_H__
#define __WOUNDDEF_H__

#include <string>

#include "potion.h"

class Player;

class WoundDef: public Potion {
public:
    WoundDef(int r, int c, std::string objectID);
    void usePotion(Player* player);
    ~WoundDef();
};

#endif