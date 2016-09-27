#include <string>

using namespace std;

#include "potion.h"

Potion::~Potion() {}

#if GAMETYPE == 1

/*********** Potion ***********
 Purpose: constructor of a Potion that consumes two coordinates , a boolean and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Potion::Potion(int r, int c, string objectID, bool unknown): GameObject(r, c, objectID) {
    this->superObjectID = "potion";
}

#elif GAMETYPE == 2

/*********** Potion ***********
 Purpose: constructor of a Potion that consumes two coordinates , a boolean and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Potion::Potion(int r, int c, string objectID, bool unknown): GameObject(r, c, objectID) {
    this->superObjectID = "potion";
    this->unknown = unknown;
}

/*********** checkPermissions ***********
 Purpose: getter method for unkown which checks if the potion is bought from a merchant or is picked up from the board
 
 Returns: bool
 
 Errors: none
 *********************************/
bool Potion::checkPermission(){
    return unknown;
}

/*********** setSource ***********
 Purpose: setter for unknown which sets if the potion is picked up fron a merchant or from the board
 
 Returns: void
 
 Errors: none
 *********************************/
void Potion::setSource(bool fromMerchant) {
    unknown = fromMerchant;
}

#endif