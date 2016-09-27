#include "merchanthoard.h"
#include "gold.h"

#include <string.h>

using namespace std;

/*********** MerchantHoard ***********
 Purpose: constructor of a MerchantHoard that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
MerchantHoard::MerchantHoard(int r, int c, string objectID): Gold(r, c, objectID) {
    this->gold = 4;
}

/*********** ~MerchantHoard ***********
 Purpose: destructor of a MerchantHoard
 
 Returns: N/A
 
 Errors: none
 *********************************/
MerchantHoard::~MerchantHoard() {
    //dtor
}