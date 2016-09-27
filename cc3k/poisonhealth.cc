#include <string>

using namespace std;

#include "poisonhealth.h"
#include "player.h"

/*********** PoisenHealth ***********
 Purpose: Constructor of a PoisenHealth that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
PoisonHealth::PoisonHealth(int r, int c, string objectID): Potion(r, c, objectID, false) {
    //ctor
}

/*********** ~PoisenHealth ***********
 Purpose: Destructor of a PoisenHealth
 
 Returns: N/A
 
 Errors: none
 *********************************/
PoisonHealth::~PoisonHealth() {
    //dtor
}

/*********** usePotion ***********
 Purpose: Decreases the health of the player which is taken in
 
 Returns: void
 
 Errors: none
 *********************************/
void PoisonHealth::usePotion(Player* player) {
    player->adjustHP(-10);
}