#ifndef __DUNGEONGRID_H__
#define __DUNGEONGRID_H__

#include <string>

#include "gameobject.h"

class Chamber;
class Enemy;
class Player;

class DungeonGrid {
private:
    static DungeonGrid* instance; // only one dungeon grid
    GameObject*** grid; // the dungeon grid
    int width, height; // the width and height of the dungeon grid
    
    DungeonGrid(); // private constructor due to singleton
    
    // floor related
    Chamber** chambers; // the chambers in the dungeon grid

    void spawnPlayer(int chamberNumberPlayer, Player* player);
    void spawnStairs(int chamberNumberStairs);
    void spawnPotions();
    void spawnGold(int& numEnemies, int& enemyIndex, Enemy** enemies);
    void spawnEnemies(int numEnemies, int enemyIndex, Enemy** enemies);
    
    // player related
    int playerR, playerC; // location of the player
    std::string playerMoveHelper(int targetR, int targetC, std::string direction);
    std::string usePotionHelper(int targetR, int targetC);
    std::string playerAttackHelper(int targetR, int targetC, Enemy** enemies, int numEnemies);
    
#if GAMETYPE == 1
    
private:
    void createDefaultFloor(std::string filename, Player* player, int& track, Enemy** enemies);
    
public:
    // player movement
    std::string playerMove(std::string direction);
    
    // player use potion
    std::string usePotion(std::string direction);
    
    // player attack
    std::string playerAttack(std::string direction, Enemy** enemies, int numEnemies);
    
#elif GAMETYPE == 2
    
private:
    void createRandomFloor(std::string, Player* player, int& track, Enemy** enemies);
    std::string addPotionHelper(int targetR, int targetC);
    string buyPotionHelper(int, int, Player* player);
    
public:
    // curses.h
    std::string playerMove(int direction);
    std::string addPotion(int direction);
    std::string usePotion(int direction);
    std::string buyPotion(int direction, Player* player);
    std::string playerAttack(int direction, Enemy** enemies, int numEnemies);
    
#endif
    
public:
    static DungeonGrid* getInstance();
    static void cleanup();
    ~DungeonGrid();

    // floor related
    void setupFloor(std::string filename, Player* player, int& track, Enemy** enemies);
    void setupObjects(Player* player, Enemy** enemies);
    void clearDungeon(bool clearPlayer);
    void clearDungeon2(bool clearPlayer);

    // enemies move
    std::string enemiesMove(Enemy** enemies, int numEnemies);
    void setGameObject(int r, int c, GameObject* gameObject);
    GameObject* getGameObject(int r, int c);
    
    friend std::ostream& operator<<(std::ostream& o, DungeonGrid& dungeonGrid);
};

#endif
