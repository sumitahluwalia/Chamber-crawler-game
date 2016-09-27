#include <string>

using namespace std;

#include "stairs.h"
#include "gameobject.h"

/*********** Stairs ***********
 Purpose: constructor of a Stairs that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Stairs::Stairs(int r, int c, string objectID): GameObject(r, c, objectID) {}

/*********** ~Stairs ***********
 Purpose: Destructor of a Stairs
 
 Returns: N/A
 
 Errors: none
 *********************************/
Stairs::~Stairs() {}