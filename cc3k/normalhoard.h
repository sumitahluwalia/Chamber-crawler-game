#ifndef __NORMALHOARD_H__
#define __NORMALHOARD_H__

#include "gold.h"

#include <string.h>

class NormalHoard: public Gold {
public:
    ~NormalHoard();
    NormalHoard(int r, int c, std::string objectID);
};

#endif