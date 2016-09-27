#ifndef __ORC_H__
#define __ORC_H__

#include <string>

#include "enemy.h"

class DungeonGrid;
class Player;

class Orc: public Enemy {
public:
    Orc(int r, int c, std::string objectID);
    ~Orc();
};

#endif