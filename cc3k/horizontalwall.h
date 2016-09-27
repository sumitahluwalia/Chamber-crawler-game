#ifndef __HORIZONTALWALL_H__
#define __HORIZONTALWALL_H__

#include <string>

#include "gameobject.h"

class HorizontalWall: public GameObject {
public:
    HorizontalWall(int r, int c, std::string objectID);
    ~HorizontalWall();
};

#endif