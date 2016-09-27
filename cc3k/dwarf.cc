#include <string>

using namespace std;

#include "dwarf.h"
#include "enemy.h"
#include "dungeongrid.h"
#include "player.h"

/*********** Dwarf ***********
 Purpose: constructor of a Dwarf that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Dwarf::Dwarf(int r, int c, string objectID): Enemy(r, c, objectID, 20, 30, 100) {
    
}

/*********** ~Dwarf ***********
 Purpose: destructor of a Dwarf
 
 Returns: N/A
 
 Errors: none
 *********************************/
Dwarf::~Dwarf() {
    
}