#ifndef __MERCHANTHOARD_H__
#define __MERCHANTHOARD_H__

#include "gold.h"

#include <string.h>

class MerchantHoard: public Gold {
public:
    ~MerchantHoard();
    MerchantHoard(int r, int c, std::string objectID);
};

#endif