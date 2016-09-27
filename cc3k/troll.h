#ifndef __TROLL_H__
#define __TROLL_H__

#include <string>

#include "player.h"

class Troll: public Player {
public:
    Troll(std::string objectID);
    ~Troll();
    void hpRegen();
};

#endif