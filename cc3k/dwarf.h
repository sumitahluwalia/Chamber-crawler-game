#ifndef __DWARF_H__
#define __DWARF_H__

#include <string>

#include "enemy.h"

class DungeonGrid;
class Player;

class Dwarf: public Enemy {
public:
    Dwarf(int r, int c, std::string objectID);
    ~Dwarf();
};

#endif