#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

#include "gameobject.h"

class Potion;
class Enemy;
class GameObject;

class Player: public GameObject {
    int prevStepObject; // 0 = floortile, 1 = doorway, 2 = passage
protected:
    float multiplier;
    float currentATK;
    float currentDEF;
    float currentHP;
    float gold;
    float maximumHP;
    float defaultATK;
    float defaultDEF;
    
#if GAMETYPE == 1
    
#elif GAMETYPE == 2
    
protected:
    Potion * inventory[10];
    int numPotions;
public:
    // inventory ralated
    std::string addPotion(Potion * potion);
    std::string usePotion(int n);
    void displayPotions();
    std::string buyPotions(int index);
    
#endif
    
public:
    Player(float atk,float def,float HP,float mul);
    bool isDead();
    
    // movement related
    void setPrevStepObject(int prevStepObject);
    int getPrevStepObject();
    
    // stats related
    void displayStats(int floor);
    void resetStats();
    
    // race related
    virtual void hpRegen();
    
    // potion related
    void adjustAtk(float n);
    void adjustDef(float n);
    virtual void adjustHP(float n);
    
    // gold related
    virtual void adjustGold(int gold);
    float getGold();
    
    // enemy related
    virtual std::string attack(Enemy* enemy);
    virtual std::string attacked(int incomingATK, std::string enemyInitial);
    
    ~Player();
};



#endif
