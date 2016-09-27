#include <string>

using namespace std;

#include "player.h"
#include "boostatk.h"

/*********** BoostAttack ***********
Purpose: constructor of a BoostAttack that consumes two coordinates and an object id string

Returns: N/A

Errors: none
*********************************/
BoostAttack::BoostAttack(int r, int c, string objectID): Potion(r, c, objectID, false) {
    
}

/*********** ~BoostAttack ***********
Purpose: Destructor of a BoostAttack

Returns: N/A

Errors: none
*********************************/
BoostAttack::~BoostAttack() {
    
}

/*********** usePotion ***********
Purpose: Function that boosts the attacks of the the player which is taken in

Returns: void

Errors: none
*********************************/
void BoostAttack::usePotion(Player* player) {
    player->adjustAtk(5);
}