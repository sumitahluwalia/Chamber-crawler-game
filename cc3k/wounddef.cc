#include <string>

using namespace std;

#include "wounddef.h"
#include "player.h"

/*********** WoundDef ***********
 Purpose: constructor of a WoundDef that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
WoundDef::WoundDef(int r, int c, string objectID): Potion(r, c, objectID, false) {
    //ctor
}

/*********** ~WoundDef ***********
 Purpose: Destructor of a BoostAttack 
 
 Returns: N/A
 
 Errors: none
 *********************************/

WoundDef::~WoundDef() {
    //dtor
}

/*********** usePotion ***********
 Purpose: Function that wounds the defence of the the player which is taken in
 
 Returns: void
 
 Errors: none
 *********************************/
void WoundDef::usePotion(Player* player){
    player->adjustDef(-5);
}