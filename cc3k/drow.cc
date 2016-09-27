#include <string>

using namespace std;

#include "drow.h"
#include "player.h"

/*********** Drow ***********
 Purpose: constructor of a Drow that consumes an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Drow::Drow(string objectID): Player(25, 15, 150, 1.5) {
    this->objectID = objectID;
}

/*********** ~Drow ***********
 Purpose: destructor of a Drow
 
 Returns: N/A
 
 Errors: none
 *********************************/
Drow::~Drow() {
    //dtor
}