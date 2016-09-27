#ifndef __DROW_H__
#define __DROW_H__

#include <string>

#include "player.h"

class Drow: public Player {
public:
    Drow(std::string objectID);
    ~Drow();
};

#endif