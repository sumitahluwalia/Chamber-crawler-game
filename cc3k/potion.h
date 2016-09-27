#ifndef __POTION_H__
#define __POTION_H__

#include <string>

#include "gameobject.h"

class Player;

class Potion: public GameObject {
public:
    Potion(int r, int c, std::string objectID, bool showId);
    virtual void usePotion(Player* player) = 0;
    ~Potion();
    
#if GAMETYPE == 1
    
#elif GAMETYPE == 2
    
public:
    bool checkPermission();
    void setSource(bool fromMerchant);
    
protected:
    bool unknown;
    
#endif
    
};

#endif