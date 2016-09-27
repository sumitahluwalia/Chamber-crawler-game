#ifndef __ELF_H__
#define __ELF_H__

#include <string>

#include "enemy.h"

class DungeonGrid;
class Player;

class Elf: public Enemy {
    std::string attack(Player* player);
    
public:
    Elf(int r, int c, std::string objectID);
    ~Elf();
};

#endif