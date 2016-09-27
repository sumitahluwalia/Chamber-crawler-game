#ifndef __PASSAGE_H__
#define __PASSAGE_H__

#include <string>

#include "gameobject.h"

class Passage: public GameObject {
public:
    Passage(int r, int c, std::string objectID);
    ~Passage();
};

#endif