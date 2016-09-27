#include <string>

using namespace std;

#include "player.h"
#include "woundatk.h"

/*********** WoundAttack ***********
 Purpose: constructor of a BoostAttack that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
WoundAttack::WoundAttack(int r, int c, string objectID): Potion(r, c, objectID, false) {
    //ctor
}

/*********** ~WoundAttack ***********
 Purpose: Destructor for WoundAttack
 
 Returns: N/A
 
 Errors: none
 *********************************/
WoundAttack::~WoundAttack() {
    //dtor
}

/*********** usePotion ***********
 Purpose: Function that wounds the attacks of the the player which is taken in
 
 Returns: void
 
 Errors: none
 *********************************/
void WoundAttack::usePotion(Player* player) {
    player->adjustAtk(-5);
}