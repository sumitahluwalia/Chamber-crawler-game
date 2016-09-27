#ifndef __HALFLING_H__
#define __HALFLING_H__

#include <string>

#include "enemy.h"

class DungeonGrid;
class Player;

class Halfling: public Enemy {
    
public:
    Halfling(int r, int c, std::string objectID);
    ~Halfling();
    std::string attacked(int incomingATK, Player* player);
};

#endif