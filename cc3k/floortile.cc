#include <string>

using namespace std;

#include "floortile.h"
#include "gameobject.h"

/*********** FloorTile ***********
 Purpose: constructor of a FloorTile that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
FloorTile::FloorTile(int r, int c, string objectID): GameObject(r, c, objectID) {
    this->superObjectID = "cell";
}

/*********** ~FloorTile ***********
 Purpose: destructor of a FloorTile
 
 Returns: N/A
 
 Errors: none
 *********************************/
FloorTile::~FloorTile() {}