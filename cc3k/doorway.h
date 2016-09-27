#ifndef __DOORWAY_H__
#define __DOORWAY_H__

#include <string>

#include "gameobject.h"

class Doorway: public GameObject {
public:
    Doorway(int r, int c, std::string objectID);
    ~Doorway();
};

#endif