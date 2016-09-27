#include "gold.h"
#include "smallhoard.h"

#include <string.h>
using namespace std;

/*********** SmallHoard ***********
 Purpose: constructor of a smallHoard that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
SmallHoard::SmallHoard(int r, int c, string objectID): Gold(r, c, objectID) {
    this->gold = 1;
}

/*********** ~SmallHoard ***********
 Purpose: destructor of a smallHoard
 
 Returns: N/A
 
 Errors: none
 *********************************/
SmallHoard::~SmallHoard() {
    //dtor
}