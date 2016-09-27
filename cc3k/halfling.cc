#include <string>
#include <math.h>
#include <cstdlib>
#include <sstream>
using namespace std;

#include "halfling.h"
#include "enemy.h"
#include "dungeongrid.h"
#include "player.h"

/*********** Halfling ***********
 Purpose: constructor of a Halfling that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Halfling::Halfling(int r, int c, string objectID): Enemy(r, c, objectID, 15, 20, 100) {
    
}

/*********** ~Halfling ***********
 Purpose: destructor of a Halfling 
 
 Returns: N/A
 
 Errors: none
 *********************************/
Halfling::~Halfling() {
    
}

/*********** attacked ***********
 Purpose: this controls the player attack on a  halfling by consuming an interger and pointer to a player
 
 Returns: string
 
 Errors: none
 *********************************/
string Halfling::attacked(int incomingATK, Player* player) {
    int miss = rand() % 2;
    
    if (miss == 0) {
        return "PC's attack missed L. ";
    } else {
        string enemyInitial = "L";
        
        float damage = ceil(100 / (100 + def) * incomingATK);
        int damage2 = damage;
        
        currentHP -= damage;
        
        int conv = currentHP;
        
        if (conv <= 0) {
            player->adjustGold(gold);
            std::string s;
            std::ostringstream out;
            out << damage2;
            s = out.str();
            return "PC deals " + s + " damage to " + enemyInitial + " (0 HP). " + enemyInitial + " is dead. ";
        } else {
            int hp2 = currentHP;
            std::string s;
            std::ostringstream out;
            out << damage2;
            s = out.str();
            std::string d;
            std::ostringstream out1;
            out1 << hp2;
            d = out1.str();
            return "PC deals " + s + " damage to " + enemyInitial + " (" + d + " HP). ";
        }
    }
}
