#include <string>

using namespace std;

#include "verticalwall.h"
#include "gameobject.h"

/*********** VerticalWall ***********
 Purpose: constructor of a VerticalWall that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
VerticalWall::VerticalWall(int r, int c, string objectID): GameObject(r, c, objectID) {
    this->superObjectID = "cell";
}

/*********** VerticalWall ***********
 Purpose: destructor of a VerticalWall
 
 Returns: N/A
 
 Errors: none
 *********************************/
VerticalWall::~VerticalWall() {}