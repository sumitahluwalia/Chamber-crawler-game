#include <string>
#include <cstdlib>
#include <math.h>
#include <sstream>
using namespace std;

#include "merchant.h"
#include "enemy.h"
#include "dungeongrid.h"
#include "player.h"

bool Merchant::hostile = false;

/*********** becomeHostile ***********
 Purpose: this function turns all the merchants to be hostile towards the player by changing the static field to true
 
 Returns: void
 
 Errors: none
 *********************************/
void Merchant::becomeHostile() {
	hostile = true;
}

/*********** becomeNeutreal ***********
 Purpose:this function turns all the merchants to be non-hostile towards the player by changing the static field to false
 
 Returns: void
 
 Errors: none
 *********************************/
void Merchant::becomeNeutral() {
	hostile = false;
}

/*********** Merchant ***********
 Purpose: constructor of a Merchant that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
Merchant::Merchant(int r, int c, string objectID) :
		Enemy(r, c, objectID, 70, 5, 30) {
	this->gold = 0;
}

/*********** ~Merchant ***********
 Purpose: destructor of a Merchant
 
 Returns: N/A
 
 Errors: none
 *********************************/
Merchant::~Merchant() {

}

/*********** move ***********
 Purpose: this function is used to attack the player when the merchants are hostile towards player
 
 Returns:string
 
 Errors: none
 *********************************/
string Merchant::move(DungeonGrid* dungeonGrid) {
	if (hostile) {
		if (dungeonGrid->getGameObject(r - 1, c)->getSuperObjectID()
				== "player") {
			return attack((Player*) dungeonGrid->getGameObject(r - 1, c));
		} else if (dungeonGrid->getGameObject(r - 1, c + 1)->getSuperObjectID()
				== "player") {
			return attack((Player*) dungeonGrid->getGameObject(r - 1, c + 1));
		} else if (dungeonGrid->getGameObject(r, c + 1)->getSuperObjectID()
				== "player") {
			return attack((Player*) dungeonGrid->getGameObject(r, c + 1));
		} else if (dungeonGrid->getGameObject(r + 1, c + 1)->getSuperObjectID()
				== "player") {
			return attack((Player*) dungeonGrid->getGameObject(r + 1, c + 1));
		} else if (dungeonGrid->getGameObject(r + 1, c)->getSuperObjectID()
				== "player") {
			return attack((Player*) dungeonGrid->getGameObject(r + 1, c));
		} else if (dungeonGrid->getGameObject(r + 1, c - 1)->getSuperObjectID()
				== "player") {
			return attack((Player*) dungeonGrid->getGameObject(r + 1, c - 1));
		} else if (dungeonGrid->getGameObject(r, c - 1)->getSuperObjectID()
				== "player") {
			return attack((Player*) dungeonGrid->getGameObject(r, c - 1));
		} else if (dungeonGrid->getGameObject(r - 1, c - 1)->getSuperObjectID()
				== "player") {
			return attack((Player*) dungeonGrid->getGameObject(r - 1, c - 1));
		}
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

/*********** attacked ***********
 Purpose: this function deals with the attacks from the player on the merchant
 
 Returns: string
 
 Errors: none
 *********************************/
string Merchant::attacked(int incomingATK, Player* player) {
	Merchant::becomeHostile();

	string enemyInitial = "M";

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
		return "PC deals " + s + " damage to " + enemyInitial + " (0 HP). "
				+ enemyInitial + " is dead. ";
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
		return "PC deals " + s + " damage to " + enemyInitial
				+ " (" + d + " HP). ";
	}
}

/*********** getHostility ***********
 Purpose: this is a getter function for the static variable hostility
 
 Returns: bool
 
 Errors: none
 *********************************/
bool Merchant::getHostility() {
    return hostile;
}