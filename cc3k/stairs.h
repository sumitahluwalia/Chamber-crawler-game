#ifndef __STAIRS_H__
#define __STAIRS_H__

#include <string>

#include "gameobject.h"

class Stairs: public GameObject {
    
public:
    Stairs(int r, int c, std::string objectID);
    ~Stairs();
};

#endif