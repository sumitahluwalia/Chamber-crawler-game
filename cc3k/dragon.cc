#include <string>

using namespace std;

#include "dragon.h"
#include "enemy.h"
#include "dungeongrid.h"
#include "player.h"
#include "dragonhoard.h"

/*********** Dragon ***********
 Purpose: constructor of a Dragon that consumes two coordinates of its location ,two coordianates of Dragon Hoards location ,an object id string and a pointer to dragonHoard
 
 Returns: N/A
 
 Errors: none
 *********************************/
Dragon::Dragon(int r, int c, int hoardR, int hoardC, string objectID, DragonHoard* dragonHoard): Enemy(r, c, objectID, 20, 20, 150) {
    this->hoardR = hoardR;
    this->hoardC = hoardC;
    this->dragonHoard = dragonHoard;
    this->gold = 0;
}

/*********** ~Dragon ***********
 Purpose: Destructor of a Dragon
 
 Returns: N/A
 
 Errors: none
 *********************************/
Dragon::~Dragon() {
    
}

/*********** move ***********
 Purpose: function contols the attacking of the Dragon if a Player is around by consuming a dungeonGrid Pointer
 
 Returns: String
 
 Errors: none
 *********************************/
string Dragon::move(DungeonGrid* dungeonGrid) {
    if (hoardR == r - 1 && hoardC == c) {
        if (dungeonGrid->getGameObject(hoardR - 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, c));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(r - 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c + 1));
        } else if (dungeonGrid->getGameObject(r, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r, c + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c));
        } else if (dungeonGrid->getGameObject(r + 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c - 1));
        } else if (dungeonGrid->getGameObject(r, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r, c - 1));
        } else if (dungeonGrid->getGameObject(r - 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c - 1));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC - 1));
        }
    } else if (hoardR == r - 1 && hoardC == c + 1) {
        if (dungeonGrid->getGameObject(hoardR - 1, hoardC)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(r, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r, c + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c));
        } else if (dungeonGrid->getGameObject(r + 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c - 1));
        } else if (dungeonGrid->getGameObject(r, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r, c - 1));
        } else if (dungeonGrid->getGameObject(r - 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c - 1));
        } else if (dungeonGrid->getGameObject(r - 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC - 1));
        }
    } else if (hoardR == r && hoardC == c + 1) {
        if (dungeonGrid->getGameObject(hoardR - 1, hoardC)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c));
        } else if (dungeonGrid->getGameObject(r + 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c - 1));
        } else if (dungeonGrid->getGameObject(r, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r, c - 1));
        } else if (dungeonGrid->getGameObject(r - 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c - 1));
        } else if (dungeonGrid->getGameObject(r - 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c));
        }
    } else if (hoardR == r + 1 && hoardC == c + 1) {
        if (dungeonGrid->getGameObject(hoardR - 1, hoardC)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC - 1));
        } else if (dungeonGrid->getGameObject(r + 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c));
        } else if (dungeonGrid->getGameObject(r + 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c - 1));
        } else if (dungeonGrid->getGameObject(r, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r, c - 1));
        } else if (dungeonGrid->getGameObject(r - 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c - 1));
        } else if (dungeonGrid->getGameObject(r - 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c));
        } else if (dungeonGrid->getGameObject(r - 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c + 1));
        }
    } else if (hoardR == r + 1 && hoardC == c) {
        if (dungeonGrid->getGameObject(hoardR - 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC - 1));
        } else if (dungeonGrid->getGameObject(hoardR, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR, hoardC - 1));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC - 1));
        } else if (dungeonGrid->getGameObject(r - 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c - 1));
        } else if (dungeonGrid->getGameObject(r - 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c));
        } else if (dungeonGrid->getGameObject(r - 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c + 1));
        }
    } else if (hoardR == r + 1 && hoardC == c - 1) {
        if (dungeonGrid->getGameObject(r - 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c));
        } else if (dungeonGrid->getGameObject(r - 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c + 1));
        } else if (dungeonGrid->getGameObject(r, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r, c + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC - 1));
        } else if (dungeonGrid->getGameObject(hoardR, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR, hoardC - 1));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC - 1));
        } else if (dungeonGrid->getGameObject(r, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r, c - 1));
        } else if (dungeonGrid->getGameObject(r - 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c - 1));
        }
    } else if (hoardR == r && hoardC == c - 1) {
        if (dungeonGrid->getGameObject(hoardR - 1, hoardC)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC));
        } else if (dungeonGrid->getGameObject(r - 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c));
        } else if (dungeonGrid->getGameObject(r - 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c + 1));
        } else if (dungeonGrid->getGameObject(r, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r, c + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c + 1));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC - 1));
        } else if (dungeonGrid->getGameObject(hoardR, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR, hoardC - 1));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC - 1));
        }
    } else {
        if (dungeonGrid->getGameObject(hoardR - 1, hoardC)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC + 1));
        } else if (dungeonGrid->getGameObject(r - 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c));
        } else if (dungeonGrid->getGameObject(r - 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r - 1, c + 1));
        } else if (dungeonGrid->getGameObject(r, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r, c + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c + 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c + 1));
        } else if (dungeonGrid->getGameObject(r + 1, c)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c));
        } else if (dungeonGrid->getGameObject(r + 1, c - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(r + 1, c - 1));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC));
        } else if (dungeonGrid->getGameObject(hoardR + 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR + 1, hoardC - 1));
        } else if (dungeonGrid->getGameObject(hoardR, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR, hoardC - 1));
        } else if (dungeonGrid->getGameObject(hoardR - 1, hoardC - 1)->getSuperObjectID() == "player") {
            return attack((Player*)dungeonGrid->getGameObject(hoardR - 1, hoardC - 1));
        }
    }
    
    return "";
}

/*********** isDead ***********
 Purpose: functions checks if the Dragon is dead or not so that player can take its gold or not
 
 Returns: Bool
 
 Errors: none
 *********************************/
bool Dragon::isDead() {
    int a = currentHP;
    
    if (a <= 0) {
        dragonHoard->freed();
    }
    
    return a <= 0;
}

/*********** getHoard ***********
 Purpose: Function produces the pointer to the DragonHoard
 
 Returns: DragonHoard*
 
 Errors: none
 *********************************/
DragonHoard* Dragon::getHoard() {
	return dragonHoard;
}

/*********** setHoard ***********
 Purpose: function set the dragon hoard related with the dragon and also sets the coordinates of the dragon Hoard
 
 Returns: void
 
 Errors: none
 *********************************/
void Dragon::setHoard(DragonHoard* dragonHoard, int hoardR, int hoardC) {
	this->dragonHoard = dragonHoard;
	this->hoardR = hoardR;
	this->hoardC = hoardC;
}
