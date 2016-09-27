#include <string>
#include <cstdlib>

using namespace std;

#include "vampire.h"
#include "player.h"
#include "enemy.h"
#include "merchant.h"

/*********** Vampire ***********
 Purpose: constructor of a Vampire that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Vampire::Vampire(string objectID): Player(25, 25, 50, 1) {
    this->objectID = objectID;
}

/*********** ~Vampire ***********
 Purpose: destructor of a Vampire
 
 Returns: N/A
 
 Errors: none
 *********************************/
Vampire::~Vampire() {
    //dtor
}

/*********** adjustHP ***********
 Purpose: this fuction adjusts the health of a Vampire which has no cap
 
 Returns: void
 
 Errors: none
 *********************************/
void Vampire::adjustHP(float n) {
    if((this->currentHP + (this->multiplier * n))<0) {
        currentHP=0;
    } else {
        currentHP=(this->currentHP + (this->multiplier * n));
    }
}

/*********** attack ***********
 Purpose: this controls the attack of an enemy on a vampire and changes the health of the player accordingly
 
 Returns: string
 
 Errors: none
 *********************************/
string Vampire::attack(Enemy* enemy) {
    if (enemy->getObjectID() == "dwarf") {
        currentHP -= 5;
    } else {
        currentHP += 5;
    }
    
    return enemy->attacked(currentATK, this);
}