#include "gold.h"
#include "gameobject.h"
#include "player.h"

#include <string.h>
using namespace std;

/*********** Gold ***********
 Purpose: constructor of a Gold that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Gold::Gold(int r, int c, string objectID): GameObject(r, c, objectID) {
    this->superObjectID = "gold";
}

/*********** adjustGold ***********
 Purpose: this fuction adds or subtracts gold which the player is holding right now
 
 Returns: void
 
 Errors: none
 *********************************/
void Gold::adjustGold(Player* player) {
    player->adjustGold(this->gold);
}

/*********** getGold ***********
 Purpose: this is a getter fuction for the gold field in Gold
 
 Returns: Float
 
 Errors: none
 *********************************/
float Gold::getGold() {
    return gold;
}

/*********** Gold ***********
 Purpose: destructor of Golf
 
 Returns: N/A
 
 Errors: none
 *********************************/
Gold::~Gold() {
    //dtor
}