#include <string>

using namespace std;

#include "troll.h"

/*********** Trool ***********
 Purpose: constructor of a Troll that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Troll::Troll(string objectID): Player(25, 15, 120, 1) {
    this->objectID = objectID;
}

/*********** ~Trool ***********
 Purpose: destructor of a Troll
 Returns: N/A
 
 Errors: none
 *********************************/
Troll::~Troll() {
    //dtor
}

/*********** hpRegan ***********
 Purpose: increases the health of the player who is an Troll by 5
 
 Returns: void
 
 Errors: none
 *********************************/
void Troll::hpRegen() {
    adjustHP(5);
}