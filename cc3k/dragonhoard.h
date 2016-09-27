#ifndef __DRAGONHOARD_H__
#define __DRAGONHOARD_H__

#include "gold.h"

#include <string.h>

class DragonHoard: public Gold {
    bool free;
		bool claimed;
public:
    ~DragonHoard();
    DragonHoard(int r, int c, std::string objectID);
    bool dragonDead();
    void freed();
		bool isClaimed();
		void setClaimed();
};

#endif
