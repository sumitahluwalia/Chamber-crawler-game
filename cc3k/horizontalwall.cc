#include <string>

using namespace std;

#include "horizontalwall.h"
#include "gameobject.h"

/*********** HorizontalWall ***********
 Purpose: constructor of a BoostAttack that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
HorizontalWall::HorizontalWall(int r, int c, string objectID): GameObject(r, c, objectID) {
    this->superObjectID = "cell";
}

/*********** HorizontalWall ***********
 Purpose: Destructor of a HorizontalWall
 
 Returns: N/A
 
 Errors: none
 *********************************/
HorizontalWall::~HorizontalWall() {}