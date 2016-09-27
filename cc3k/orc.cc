#include <string>

using namespace std;

#include "orc.h"
#include "enemy.h"
#include "dungeongrid.h"
#include "player.h"

/*********** Orc ***********
 Purpose: constructor of an orc that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Orc::Orc(int r, int c, string objectID): Enemy(r, c, objectID, 30, 25, 180) {
    
}

/*********** ~orc ***********
 Purpose: destructor of an orc
 
 Returns: N/A
 
 Errors: none
 *********************************/
Orc::~Orc() {
    
}