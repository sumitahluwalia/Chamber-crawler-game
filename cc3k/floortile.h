#ifndef __FLOORTILE_H__
#define __FLOORTILE_H__

#include <string>

#include "gameobject.h"

class FloorTile: public GameObject {
public:
    FloorTile(int r, int c, std::string objectID);
    ~FloorTile();
};

#endif