#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <string>

#include "gameobject.h"

class DungeonGrid;
class Player;

class Enemy: public GameObject {
protected:
    DungeonGrid* dungeonGrid;
    float atk;
    float def;
    float currentHP;
    float maximumHP;
    float gold;
    
    Enemy(int r, int c, std::string objectID, float atk, float def, float hp);
    virtual std::string attack(Player* player);
    std::string enemyMove(int targetR, int targetC, DungeonGrid* dungeonGrid);
    
public:
    ~Enemy();
    virtual std::string attacked(int incomingATK, Player* player);
    virtual std::string move(DungeonGrid* dungeonGrid);
    virtual bool isDead();
};

#endif