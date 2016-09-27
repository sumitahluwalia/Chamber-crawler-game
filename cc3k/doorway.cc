#include <string>

using namespace std;

#include "doorway.h"
#include "gameobject.h"

/*********** Doorway ***********
 Purpose: constructor of a Doorway that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Doorway::Doorway(int r, int c, string objectID): GameObject(r, c, objectID) {
    this->superObjectID = "cell";
}

/*********** ~BoostAttack ***********
 Purpose: destructor of a Doorway
 
 Returns: N/A
 
 Errors: none
 *********************************/
Doorway::~Doorway() {}