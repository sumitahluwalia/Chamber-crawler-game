#include <string>
#include <cstdlib>

using namespace std;

#include "elf.h"
#include "enemy.h"
#include "dungeongrid.h"
#include "player.h"

/*********** Elf ***********
 Purpose: constructor of a Elf that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Elf::Elf(int r, int c, string objectID): Enemy(r, c, objectID, 30, 10, 140) {
    
}

/*********** ~Elf ***********
 Purpose: destructor of a Elf
 
 Returns: N/A
 
 Errors: none
 *********************************/
Elf::~Elf() {
    
}

/*********** attack ***********
 Purpose: this functions controls the attacking of the Elf by consuming a pointer to the player
 
 Returns: string
 
 Errors: none
 *********************************/
string Elf::attack(Player *player) {
    string enemyInitial = "E";
    
    string s;
    
    if (player->getObjectID() == "drow") {
        int miss = rand() % 2;
        if (miss == 0) {
            s.append(enemyInitial + "'s attack missed PC. ");
        } else {
            s.append(player->attacked(atk, enemyInitial));
        }
    } else {
        for (int i = 0; i < 2; i++) {
            int miss = rand() % 2;
            if (miss == 0) {
                s.append(enemyInitial + "'s attack missed PC. ");
            } else {
                s.append(player->attacked(atk, enemyInitial));
                
                if (player->isDead()) {
                    break;
                }
            }
        }
    }
    
    return s;
}