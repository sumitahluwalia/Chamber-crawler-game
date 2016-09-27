#ifndef __GOLD_H__
#define __GOLD_H__

#include "gameobject.h"
#include <string.h>

class Player;

class Gold: public GameObject {
    
public:
    void adjustGold(Player* player);
    float getGold();
    ~Gold();
    
protected:
    float gold;
    Gold(int r, int c, std::string objectID);
};

#endif