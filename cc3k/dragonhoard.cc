#include "dragonhoard.h"
#include "gold.h"

#include <string.h>

using namespace std;

/*********** DragonHoard ***********
 Purpose: constructor of a Dragon Hoard that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
DragonHoard::DragonHoard(int r, int c, string objectID): Gold(r, c, objectID) {
    this->gold = 6;
    this->free = false;
		claimed = false;
}

/*********** ~DragonHoard ***********
 Purpose: Destructor of a DragonHoard
 
 Returns: N/A
 
 Errors: none
 *********************************/
DragonHoard::~DragonHoard() {
    
}

/*********** dragonDead ***********
 Purpose: this function is a getter which gets the field free
 
 Returns: Bool
 
 Errors: none
 *********************************/
bool DragonHoard::dragonDead() {
    return free;
}

/*********** freed ***********
 Purpose: this sets the free variable to true when the dragon is dead
 
 Returns: void
 
 Errors: none
 *********************************/
void DragonHoard::freed() {
    free = true;
}

/*********** isClaimed ***********
 Purpose: this is getter for the field claimed
 
 Returns: bool
 
 Errors: none
 *********************************/
bool DragonHoard::isClaimed() {
		return claimed;
}

/*********** setClaimed ***********
 Purpose: this sets the field claimed to true when ever the dragon Hoard has been claimed
 
 Returns: void
 
 Errors: none
 *********************************/
void DragonHoard::setClaimed() {
		claimed = true;
}
