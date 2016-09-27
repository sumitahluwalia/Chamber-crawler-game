#include <string>

using namespace std;

#include "player.h"
#include "boostdef.h"

/*********** BoostDef ***********
 Purpose: constructor of a BoostDef that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
BoostDef::BoostDef(int r, int c, string objectID): Potion(r, c, objectID, false) {
    //ctor
}

/*********** BoostDef ***********
 Purpose: destructor of a BoostDef
 
 Returns: N/A
 
 Errors: none
 *********************************/
BoostDef::~BoostDef() {
    //dtor
}

/*********** usePotion ***********
 Purpose: Function that boosts the defence of the the player which is taken in
 
 Returns: void
 
 Errors: none
 *********************************/
void BoostDef::usePotion(Player* player) {
    player->adjustDef(5);
}