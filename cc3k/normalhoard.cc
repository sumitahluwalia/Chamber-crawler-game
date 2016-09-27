#include "normalhoard.h"
#include "gold.h"

#include <string.h>

using namespace std;

/*********** NormalHoard ***********
 Purpose: constructor of a NormalHoard that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
NormalHoard::NormalHoard(int r, int c, string objectID): Gold(r, c, objectID) {
    this->gold = 2;
}

/*********** ~NormalHoard ***********
 Purpose: destructor of a NormalHoard
 
 Returns: N/A
 
 Errors: none
 *********************************/
NormalHoard::~NormalHoard() {
    //dtor
}