#include <string>
#include <cstdlib>

using namespace std;

#include "goblin.h"
#include "enemy.h"
#include "merchant.h"

/*********** Goblin ***********
 Purpose: constructor of a Goblin that consumes an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Goblin::Goblin(string objectID): Player(15, 20, 110, 1) {
    this->objectID = objectID;
}

/*********** ~Goblin ***********
 Purpose: destructor of a Goblin
 
 Returns: N/A
 
 Errors: none
 *********************************/
Goblin::~Goblin() {
    //dtor
}

/*********** attack ***********
 Purpose: this functton controls the attacking for Goblin
 
 Returns: string
 
 Errors: none
 *********************************/
string Goblin::attack(Enemy *enemy) {    
    string s = enemy->attacked(currentATK, this);
    
    if (enemy->isDead()) {
        gold += 5;
    }
    
    return s;
}