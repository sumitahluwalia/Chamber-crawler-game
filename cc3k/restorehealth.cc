#include <string>

using namespace std;

#include "restorehealth.h"
#include "player.h"

/*********** RestoreHealth ***********
 Purpose: Constructor of a RestoreHealth that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
RestoreHealth::RestoreHealth(int r, int c, string objectID): Potion(r, c, objectID, false) {
    //ctor
}


/*********** ~RestoreHealth ***********
 Purpose: Destructor of a RestoreHealth
 
 Returns: N/A
 
 Errors: none
 *********************************/
RestoreHealth::~RestoreHealth() {
    //dtor
}

/*********** usePotion ***********
 Purpose: Increases the health of the player which is taken in
 
 Returns: void
 
 Errors: none
 *********************************/
void RestoreHealth::usePotion(Player* player) {
    player->adjustHP(10);
}