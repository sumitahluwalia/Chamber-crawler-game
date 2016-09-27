#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <iostream>

class GameObject {
protected:
    int r, c; // location of the game object on the dungeon grid
    std::string superObjectID;
    std::string objectID;
    
public:
    GameObject(int r, int c, std::string objectID);
    GameObject();
    virtual ~GameObject() = 0;
    std::string getObjectID();
    std::string getSuperObjectID();
};

std::ostream& operator <<(std::ostream& o, GameObject* gameObject);

#endif