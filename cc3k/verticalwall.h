#ifndef __VERTICALWALL_H__
#define __VERTICALWALL_H__

#include <string>

#include "gameobject.h"

class VerticalWall: public GameObject {
public:
    VerticalWall(int r, int c, std::string objectID);
    ~VerticalWall();
};

#endif