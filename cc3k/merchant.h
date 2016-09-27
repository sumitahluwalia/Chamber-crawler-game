#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include <string>

#include "enemy.h"

class DungeonGrid;
class Player;

class Merchant: public Enemy {
    static bool hostile;
public:
    static void becomeHostile();
    static void becomeNeutral();
    static bool getHostility();
    Merchant(int r, int c, std::string objectID);
    ~Merchant();
    std::string move(DungeonGrid* dungeonGrid);
    std::string attacked(int incomingATK, Player* player);
};

#endif