#ifndef __SMALLHOARD_H__
#define __SMALLHOARD_H__

#include "gold.h"
#include <string.h>

class SmallHoard: public Gold {
public:
    SmallHoard(int r, int c, std::string objectID);
    ~SmallHoard();
};

#endif