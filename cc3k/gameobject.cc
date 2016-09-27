#include <string>
#include <iostream>
#include <curses.h>

using namespace std;

#include "gameobject.h"

/*********** GameObject ***********
 Purpose: constructor of a Gameobject
 
 Returns: N/A
 
 Errors: none
 *********************************/
GameObject::GameObject() {
    
}

/*********** GameObject ***********
 Purpose: constructor of a GameObject that consumes two coordinates and an object id string
 
 Returns: N/A
 
 Errors: none
 *********************************/
GameObject::GameObject(int r, int c, string objectID) {
    this->r = r;
    this->c = c;
    this->objectID = objectID;
}

/*********** ~GameObject ***********
 Purpose: destructor of a GameObject
 
 Returns: N/A
 
 Errors: none
 *********************************/
GameObject::~GameObject() {}


/*********** getObjectID ***********
 Purpose: this function is a getter for the object ID
 
 Returns: String
 
 Errors: none
 *********************************/
string GameObject::getObjectID() {
    return objectID;
}

/*********** getSuperObjectID ***********
 Purpose: this is a getter for the SuperObjectID
 
 Returns: String
 
 Errors: none
 *********************************/
string GameObject::getSuperObjectID() {
    return superObjectID;
}

#if GAMETYPE == 1

/*********** operator << ***********
 Purpose: this is an overloaded output operator for print out GameObject
 
 Returns: ostream&
 
 Errors: none
 *********************************/
ostream& operator <<(std::ostream& o, GameObject* gameObject) {
    if (gameObject->getSuperObjectID() == "enemy") {
        if (gameObject->getObjectID() == "elf") {
            o << "E";
        } else if (gameObject->getObjectID() == "human") {
            o << "H";
        } else if (gameObject->getObjectID() == "dwarf") {
            o << "W";
        } else if (gameObject->getObjectID() == "merchant") {
            o << "M";
        } else if (gameObject->getObjectID() == "orc") {
            o << "O";
        } else if (gameObject->getObjectID() == "dragon") {
            o << "D";
        } else if (gameObject->getObjectID() == "halfling") {
            o << "L";
        }
        
    } else if (gameObject->getSuperObjectID() == "potion") {
        o << "P";
    } else if (gameObject->getSuperObjectID() == "player") {
        o << "@";
    } else if (gameObject->getSuperObjectID() == "gold") {
        o << "G";
    } else if (gameObject->getObjectID() == "stairs") {
        o << "\\";
    } else if (gameObject->getObjectID() == "doorway") {
        o << "+";
    } else if (gameObject->getObjectID() == "passage") {
        o << "#";
    } else if (gameObject->getObjectID() == "floortile") {
        o << ".";
    } else if (gameObject->getObjectID() == "verticalwall") {
        o << "|";
    } else if (gameObject->getObjectID() == "horizontalwall") {
        o << "-";
    }
    
    return o;
}

#elif GAMETYPE == 2


/*********** operator << ***********
 Purpose: this is an overloaded output operator for print out GameObject
 
 Returns: ostream&
 
 Errors: none
 *********************************/
ostream& operator <<(std::ostream& o, GameObject* gameObject) {
    if (gameObject->getSuperObjectID() == "enemy") {
        if (gameObject->getObjectID() == "elf") {
            addstr("E");
        } else if (gameObject->getObjectID() == "human") {
            addstr("H");
        } else if (gameObject->getObjectID() == "dwarf") {
            addstr("W");
        } else if (gameObject->getObjectID() == "merchant") {
            addstr("M");
        } else if (gameObject->getObjectID() == "orc") {
            addstr("O");
        } else if (gameObject->getObjectID() == "dragon") {
            addstr("D");
        } else if (gameObject->getObjectID() == "halfling") {
            addstr("L");
        }
        
    } else if (gameObject->getSuperObjectID() == "potion") {
        addstr("P");
    } else if (gameObject->getSuperObjectID() == "player") {
        addstr("@");
    } else if (gameObject->getSuperObjectID() == "gold") {
        addstr("G");
    } else if (gameObject->getObjectID() == "stairs") {
        addstr("\\");
    } else if (gameObject->getObjectID() == "doorway") {
        addstr("+");
    } else if (gameObject->getObjectID() == "passage") {
        addstr("#");
    } else if (gameObject->getObjectID() == "floortile") {
        addstr(".");
    } else if (gameObject->getObjectID() == "verticalwall") {
        addstr("|");
    } else if (gameObject->getObjectID() == "horizontalwall") {
        addstr("-");
    }
    
    return o;
}

#endif
