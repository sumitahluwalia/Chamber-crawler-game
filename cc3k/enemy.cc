#include <cstdlib>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

#include "enemy.h"
#include "dungeongrid.h"
#include "player.h"
#include "floortile.h"

/*********** Enemy ***********
 Purpose: constructor of a Enemy that consumes two coordinates ,an object id string , attack ,defence and health of the player
 
 Returns: N/A
 
 Errors: none
 *********************************/
Enemy::Enemy(int r, int c, string objectID, float atk, float def, float hp): GameObject(r, c, objectID) {
    this->atk = atk;
    this->def = def;
    this->currentHP = hp;
    this->maximumHP = hp;
    this->superObjectID = "enemy";
    
    int whichGold = rand() % 2;
    if (whichGold == 0) {
        gold = 1;
    } else {
        gold = 2;
    }
}

/*********** ~Enemy ***********
 Purpose: Destructor of the Enemy
 
 Returns: N/A
 
 Errors: none
 *********************************/
Enemy::~Enemy() {
    
}

/*********** attacked ***********
 Purpose: this fuction decreses the health of the enemy whenever it is attacked by player
 
 Returns: string
 
 Errors: none
 *********************************/
string Enemy::attacked(int incomingATK, Player* player) {
    string enemyInitial = ".";
    if (objectID == "dwarf"){
        enemyInitial = "W";
    } else {
        enemyInitial[0] = objectID[0] - 'a' + 'A';
    }
    
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

/*********** isDead ***********
 Purpose: this function tells if the ememy is dead or not by checking its health
 
 Returns: bool
 
 Errors: none
 *********************************/
bool Enemy::isDead() {
    int a = currentHP;
    
    return a <= 0;
}

/*********** enemyMove ***********
 Purpose: this function controls the movement of each of the ememy on the board
 
 Returns: string
 
 Errors: none
 *********************************/
string Enemy::enemyMove(int targetR, int targetC, DungeonGrid* dungeonGrid) {
    // delete target floortile
    delete dungeonGrid->getGameObject(targetR, targetC);
    
    // move this enemy to target location
    dungeonGrid->setGameObject(targetR, targetC, this);
    
    // create floortile
    dungeonGrid->setGameObject(r, c, new FloorTile(r, c, "floortile"));
    
    r = targetR;
    c = targetC;
    
    return "";
}

/*********** move ***********
 Purpose: this controls the attack of the ememy by checking of there is a plyer around him
 
 Returns: string
 
 Errors: none
 *********************************/
string Enemy::move(DungeonGrid *dungeonGrid) {
    if (dungeonGrid->getGameObject(r - 1, c)->getSuperObjectID() == "player") {
        return attack((Player*)dungeonGrid->getGameObject(r - 1, c));
    } else if (dungeonGrid->getGameObject(r - 1, c + 1)->getSuperObjectID() == "player") {
        return attack((Player*)dungeonGrid->getGameObject(r - 1, c + 1));
    } else if (dungeonGrid->getGameObject(r, c + 1)->getSuperObjectID() == "player") {
        return attack((Player*)dungeonGrid->getGameObject(r, c + 1));
    } else if (dungeonGrid->getGameObject(r + 1, c + 1)->getSuperObjectID() == "player") {
        return attack((Player*)dungeonGrid->getGameObject(r + 1, c + 1));
    } else if (dungeonGrid->getGameObject(r + 1, c)->getSuperObjectID() == "player") {
        return attack((Player*)dungeonGrid->getGameObject(r + 1, c));
    } else if (dungeonGrid->getGameObject(r + 1, c - 1)->getSuperObjectID() == "player") {
        return attack((Player*)dungeonGrid->getGameObject(r + 1, c - 1));
    } else if (dungeonGrid->getGameObject(r, c - 1)->getSuperObjectID() == "player") {
        return attack((Player*)dungeonGrid->getGameObject(r, c - 1));
    } else if (dungeonGrid->getGameObject(r - 1, c - 1)->getSuperObjectID() == "player") {
        return attack((Player*)dungeonGrid->getGameObject(r - 1, c - 1));
    }
    
		while (1) {
        if (dungeonGrid->getGameObject(r - 1, c)->getObjectID() != "floortile" && dungeonGrid->getGameObject(r - 1, c + 1)->getObjectID() != "floortile" && dungeonGrid->getGameObject(r, c + 1)->getObjectID() != "floortile" && dungeonGrid->getGameObject(r + 1, c + 1)->getObjectID() != "floortile" && dungeonGrid->getGameObject(r + 1, c)->getObjectID() != "floortile" && dungeonGrid->getGameObject(r + 1, c - 1)->getObjectID() != "floortile" && dungeonGrid->getGameObject(r, c - 1)->getObjectID() != "floortile" && dungeonGrid->getGameObject(r - 1, c - 1)->getObjectID() != "floortile") {
            return "";
        }
        
        int direction = rand() % 8;
        
        if (direction == 0 && dungeonGrid->getGameObject(r - 1, c)->getObjectID() == "floortile") {
            return enemyMove(r - 1, c, dungeonGrid);
        } else if (direction == 1 && dungeonGrid->getGameObject(r - 1, c + 1)->getObjectID() == "floortile") {
            return enemyMove(r - 1, c + 1, dungeonGrid);
        } else if (direction == 2 && dungeonGrid->getGameObject(r, c + 1)->getObjectID() == "floortile") {
            return enemyMove(r, c + 1, dungeonGrid);
        } else if (direction == 3 && dungeonGrid->getGameObject(r + 1, c + 1)->getObjectID() == "floortile") {
            return enemyMove(r + 1, c + 1, dungeonGrid);
        } else if (direction == 4 && dungeonGrid->getGameObject(r + 1, c)->getObjectID() == "floortile") {
            return enemyMove(r + 1, c, dungeonGrid);
        } else if (direction == 5 && dungeonGrid->getGameObject(r + 1, c - 1)->getObjectID() == "floortile") {
            return enemyMove(r + 1, c - 1, dungeonGrid);
        } else if (direction == 6 && dungeonGrid->getGameObject(r, c - 1)->getObjectID() == "floortile") {
            return enemyMove(r, c - 1, dungeonGrid);
        } else if (direction == 7 && dungeonGrid->getGameObject(r - 1, c - 1)->getObjectID() == "floortile") {
            return enemyMove(r - 1, c - 1, dungeonGrid);
        }
    }
}

/*********** attack ***********
 Purpose: this controls the attacing of the ememy by randomly controlling that it attacks 50% of the time
 
 Returns: string
 
 Errors: none
 *********************************/
string Enemy::attack(Player* player) {
    string enemyInitial = ".";
    if (objectID == "dwarf"){
        enemyInitial = "W";
    } else if (objectID == "halfling") {
        enemyInitial = "L";
    } else {
        enemyInitial[0] = objectID[0] - 'a' + 'A';
    }
    
    int miss = rand() % 2;
    if (miss == 0) {
        return enemyInitial + "'s attack missed PC. ";
    }
    
    return player->attacked(atk, enemyInitial);
}
