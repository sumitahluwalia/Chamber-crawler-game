#ifndef __DRAGON_H__
#define __DRAGON_H__

#include <string>

#include "enemy.h"

class DungeonGrid;
class Player;
class DragonHoard;

class Dragon: public Enemy {
    int hoardR, hoardC;
    DragonHoard* dragonHoard;
    
public:
    Dragon(int r, int c, int hoardR, int hoardC, std::string objectID, DragonHoard* dragonHoard);
    ~Dragon();
    std::string move(DungeonGrid* dungeonGrid);
    bool isDead();
		DragonHoard* getHoard();
		void setHoard(DragonHoard* dragonHoard, int hoardR, int hoardC);
};

#endif
