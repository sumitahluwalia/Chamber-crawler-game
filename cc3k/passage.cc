#include <string>

using namespace std;

#include "passage.h"
#include "gameobject.h"

/*********** Passage ***********
 Purpose: constructor of a Passage that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Passage::Passage(int r, int c, string objectID): GameObject(r, c, objectID) {
    this->superObjectID = "cell";
}

/*********** ~Passage ***********
 Purpose: destructor of a Passage
 
 Returns: N/A
 
 Errors: none
 *********************************/
Passage::~Passage() {}