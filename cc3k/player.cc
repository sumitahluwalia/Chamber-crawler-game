#include <string>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <curses.h>

using namespace std;

#include "dungeongrid.h"
#include "player.h"
#include "potion.h"
#include "enemy.h"
#include "merchant.h"
#include "gameobject.h"
#include "restorehealth.h"
#include "boostatk.h"
#include "boostdef.h"


/*********** adjustAtk ***********
 Purpose: this function adjusts the attack of a player by an amount of float n
 
 Returns: void
 
 Errors: none
 *********************************/
void Player::adjustAtk(float n) {
    if ((this->currentATK + (this->multiplier * n)) >= 0) {
        currentATK = (this->currentATK + (this->multiplier * n));
    } else {
        currentATK = 0;
    }
}

/*********** adjustDef ***********
 Purpose: this fuction adjusts the defence of a player by an amount of float n
 
 Returns: void
 
 Errors: none
 *********************************/
void Player::adjustDef(float n) {
    if ((this->currentDEF + (this->multiplier * n)) >= 0) {
        currentDEF = (this->currentDEF + (this->multiplier * n));
    } else {
        currentDEF = 0;
    }
}

/*********** adjustHP ***********
 Purpose: this fucntion adjust the health of a player by an amount of float n
 
 Returns: void
 
 Errors: none
 *********************************/
void Player::adjustHP(float n) {
    if ((this->currentHP + (this->multiplier * n)) < 0) {
        currentHP = 0;
    } else if ((this->currentHP + (this->multiplier * n)) > this->maximumHP) {
        currentHP = this->maximumHP;
    } else {
        currentHP = (this->currentHP + (this->multiplier * n));
    }
}

/*********** adjustGold ***********
 Purpose: this fuction adjust the amount amount of gold held by a player by an integer gold
 
 Returns: void
 
 Errors: none
 *********************************/
void Player::adjustGold(int gold) {
    this->gold += gold;
}

/*********** attack ***********
 Purpose: this controls the player  attacking an enemy by taking in a pointer to the enemy
 
 Returns: string
 
 Errors: none
 *********************************/
string Player::attack(Enemy* enemy) {
    return enemy->attacked(currentATK, this);
}

/*********** attacked ***********
 Purpose: this controls the  player being attacked by an enemy by taking in a pointer to the enemy
 
 Returns: string
 
 Errors: none
 *********************************/

string Player::attacked(int incomingATK, string enemyInitial) {
    float damage = ceil(100 / (100 + currentDEF) * incomingATK);
    int damage2 = damage;
    
    adjustHP(-damage);
    
    int conv = currentHP;
    
    if (conv <= 0) {
        std::string s;
        std::ostringstream out;
        out << damage2;
        s = out.str();
        return enemyInitial + " deals " + s + " to PC. PC is dead. ";
    } else {
        std::string s;
        std::ostringstream out;
        out << damage2;
        s = out.str();
        
        return enemyInitial + " deals " + s + " to PC. ";
    }
}

/*********** is =Dead ***********
 Purpose: this fuction check if the player is dead or not
 
 Returns: bool
 
 Errors: none
 *********************************/

bool Player::isDead() {
    return static_cast<int>(currentHP) <= 0;
}

/*********** hpRegen ***********
 Purpose: this function is to regain hp if needed to
 
 Returns: void
 
 Errors: none
 *********************************/
void Player::hpRegen() {
    
}

#if GAMETYPE == 1

/*********** player ***********
 Purpose: constructor of a player that consumes player attack ,defence , health and multipler
 
 Returns: N/A
 
 Errors: none
 *********************************/
Player::Player(float atk, float def, float HP, float multiplier): currentATK(atk), currentDEF(def), currentHP(HP), maximumHP(HP), defaultATK(atk), defaultDEF(def), multiplier(multiplier) {
    this->superObjectID = "player";
    this->objectID = "shade";
    this->gold = 0;
    this->prevStepObject = 0;
}

/*********** displayStats ***********
 Purpose: this fuction displays the stats of the player at the end of each board
 
 Returns: void
 
 Errors: none
 *********************************/
void Player::displayStats(int floor) {
    string s = this->getObjectID();
    s[0] = s[0] - 'a' + 'A';
    string ss = "";
    ss.append("Race: ");
    ss.append(s);
    ss.append(" Gold: ");
    std::string s1;
    std::ostringstream out;
    out << (static_cast<int>(this->gold));
    s1 = out.str();
    ss.append(s1);
    cout << left << setw(69) << ss;
    cout << right << "Floor " << floor;
    cout << left;
    cout << endl;
    cout << "HP: " << static_cast<int>(this->currentHP) << endl;
    cout << "Atk: " << static_cast<int>(this->currentATK) << endl;
    cout << "Def: " << static_cast<int>(this->currentDEF) << endl;
}

/*********** ~player ***********
 Purpose: destructor of a player
 
 Returns: N/A
 
 Errors: none
 *********************************/
Player::~Player() {}

#elif GAMETYPE == 2

/*********** player ***********
 Purpose: constructor of a player that consumes player attack ,defence , health and multipler
 
 Returns: N/A
 
 Errors: none
 *********************************/
Player::Player(float atk, float def, float HP, float multiplier): currentATK(atk), currentDEF(def), currentHP(HP), maximumHP(HP), defaultATK(atk), defaultDEF(def), multiplier(multiplier) {
    this->superObjectID = "player";
    this->objectID = "shade";
    this->gold = 0;
    this->numPotions = 0;
    this->prevStepObject = 0;
    
    for (int i = 0; i < 10; i++) {
        inventory[i] = 0;
    }
}

/*********** usePotion ***********
 Purpose: this fuction uses the potion from the array of potion in the player
 
 Returns: string
 
 Errors: none
 *********************************/
string Player::usePotion(int n) {
    if (n == 0) {
        n = 10;
    }
    
    if (n > numPotions || n < 1) {
        return "No potion at that slot. ";
    }
    
    int i = n - 1;
    string s = "PC uses " + inventory[i]->getObjectID() + ". ";
    (this->inventory[i])->usePotion(this);
    delete inventory[i];
    for (int k = i; k < (this->numPotions - 1); k++) {
        inventory[k] = inventory[k + 1];
    }
    inventory[(this->numPotions - 1)] = 0;
    this->numPotions--;
    return s;
}

/*********** displayPotion ***********
 Purpose: this fuction displays the inventery of potion as a list
 
 Returns: void
 
 Errors: none
 *********************************/
void Player::displayPotions() {
    addstr("Inventory (max 10): ");
    for (int i = 0; i < this->numPotions; i++) {
        if (inventory[i]->checkPermission()) {
            ostringstream oss;
            oss << i + 1;
            addstr(oss.str().c_str());
            addstr(") ");
            addstr(inventory[i]->getObjectID().c_str());
            addstr(" ");
        } else {
            ostringstream oss;
            oss << i + 1;
            addstr(oss.str().c_str());
            addstr(") unknown ");
        }
    }
    addstr("\n");
}

/*********** displayStats ***********
 Purpose: this fuction displays the stats of the player at the end of each board
 
 Returns: void
 
 Errors: none
 *********************************/
void Player::displayStats(int floor) {
    string s = this->getObjectID();
    s[0] = s[0] - 'a' + 'A';
    string ss = "";
    ss.append("Race: ");
    ss.append(s);
    ss.append(" Gold: ");
    std::string s1;
    std::ostringstream out;
    out << (static_cast<int>(this->gold));
    s1 = out.str();
    ss.append(s1);
    addstr(ss.c_str());
    addstr("                  ");
    addstr("Floor ");
    ostringstream oss;
    oss << floor;
    addstr(oss.str().c_str());
    addstr("\n");
    addstr("HP: ");
    ostringstream oss2;
    oss2 << static_cast<int>(this->currentHP);
    addstr(oss2.str().c_str());
    addstr("\n");
    addstr("Atk: ");
    ostringstream oss3;
    oss3 << static_cast<int>(this->currentATK);
    addstr(oss3.str().c_str());
    addstr("\n");
    addstr("Def: ");
    ostringstream oss4;
    oss4 << static_cast<int>(this->currentDEF);
    addstr(oss4.str().c_str());
    addstr("\n");
}

/*********** buyPotion ***********
 Purpose: this fucntion buys the potions from the merchants by taking in integer
 
 Returns: string
 
 Errors: none
 *********************************/
string Player::buyPotions(int index) {
    string s = "";
    
    int g = gold - 5;
    if (g < 0) {
        addstr("Not enough gold. ");
        addstr("\n");
        return "";
    }
    
    if (index == 1) {
        Potion* p = new RestoreHealth(0, 0, "RH");
        p->setSource(true);
        s.append(addPotion(p));
        if (s=="Inventory full. "){
            delete p;
        } else {
            gold -= 5;
        }
    } else if (index == 2) {
        Potion* p = new BoostAttack(0, 0, "BA");
        p->setSource(true);
        s.append(addPotion(p));
        if (s=="Inventory full. "){
            delete p;
        } else {
            gold -= 5;
        }
    } else if (index == 3) {
        Potion* p = new BoostDef(0, 0, "BD");
        p->setSource(true);
        s.append(addPotion(p));
        if (s=="Inventory full. "){
            delete p;
        } else {
            gold -= 5;
        }
    }
    
    if (s == "Inventory full. ") {
        addstr("Inventory full.");
        addstr("\n");
        return "";
    } else {
        return s;
    }
}

/*********** addPotion ***********
 Purpose: this function adds potions to the list of potions in the inventory
 
 Returns: string
 
 Errors: none
 *********************************/
string Player::addPotion(Potion * potion) {
    if (numPotions == 10) {
        return "Inventory full. ";
    }
    else{
        inventory[numPotions] = potion;
        numPotions++;
        return "PC picks up a potion. ";
    }
}

/*********** ~player ***********
 Purpose: destructor of a player
 
 Returns: N/A
 
 Errors: none
 *********************************/
Player::~Player() {
    for (int i = 0; i < 10; i++) {
        delete inventory[i];
    }
}

#endif

void Player::setPrevStepObject(int prevStepObject) {
    this->prevStepObject = prevStepObject;
}

int Player::getPrevStepObject() {
    return prevStepObject;
}

float Player::getGold() {
    return gold;
}

void Player::resetStats() {
    currentATK = defaultATK;
    currentDEF = defaultDEF;
}
