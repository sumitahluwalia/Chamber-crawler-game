#include <string>

using namespace std;

#include "human.h"
#include "enemy.h"
#include "dungeongrid.h"
#include "player.h"

/*********** Human ***********
 Purpose: constructor of a Human that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Human::Human(int r, int c, string objectID): Enemy(r, c, objectID, 20, 20, 140) {
    gold = 4;
}

/*********** ~Human ***********
 Purpose: Destructor of a Human
 
 Returns: N/A
 
 Errors: none
 *********************************/
Human::~Human() {
    
}