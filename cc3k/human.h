#ifndef __HUMAN_H__
#define __HUMAN_H__

#include <string>

#include "enemy.h"

class DungeonGrid;
class Player;

class Human: public Enemy {
public:
    Human(int r, int c, std::string objectID);
    ~Human();
};

#endif