#include <string>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <sstream>
#include <curses.h>
using namespace std;

#include "dungeongrid.h"
#include "chamber.h"
#include "gameobject.h"
#include "verticalwall.h"
#include "horizontalwall.h"
#include "floortile.h"
#include "doorway.h"
#include "passage.h"
#include "player.h"
#include "stairs.h"
#include "potion.h"
#include "enemy.h"
#include "restorehealth.h"
#include "boostatk.h"
#include "boostdef.h"
#include "poisonhealth.h"
#include "woundatk.h"
#include "wounddef.h"
#include "smallhoard.h"
#include "normalhoard.h"
#include "merchanthoard.h"
#include "dragonhoard.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "halfling.h"
#include "dragon.h"

/*********** clearDungeon ***********
 Purpose: this fuction clear the dungeon
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::clearDungeon(bool clearPlayer) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (grid[i][j] != 0 && grid[i][j]->getSuperObjectID() != "player") {
				delete grid[i][j];
				grid[i][j] = 0;
			} else if (grid[i][j] != 0 && grid[i][j]->getSuperObjectID() == "player")  {
				if (clearPlayer) {
					delete grid[i][j];
					grid[i][j] = 0;
				} else {
					grid[i][j] = 0;
				}
			}
		}
		delete [] grid[i];
	}
	delete [] grid;

	for (int i = 0; i < 5; i++) {
		delete chambers[i];
		chambers[i] = 0;
	}
	delete [] chambers;
}

/*********** cleardungeon2 ***********
 Purpose: this fuction clear the objects in the dungeon grid
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::clearDungeon2(bool clearPlayer) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (grid[i][j] != 0 && grid[i][j]->getSuperObjectID() != "player") {
				delete grid[i][j];
				grid[i][j] = 0;
			} else if (grid[i][j] != 0 && grid[i][j]->getSuperObjectID() == "player")  {
				if (clearPlayer) {
					delete grid[i][j];
					grid[i][j] = 0; 
				} else {
					grid[i][j] = 0; 
				}    
			}
		}    
	}

	for (int i = 0; i < 5; i++) {
		delete chambers[i];
		chambers[i] = 0; 
	}
}

/*********** movePlayerHealper ***********
 Purpose: this fuction is helper function to move player
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::playerMoveHelper(int targetR, int targetC, string direction) {
	if (grid[targetR][targetC] == 0) {
		return "Cannot move there. ";
	}

	if (grid[targetR][targetC]->getObjectID() == "stairs") {
		return "next floor";
	}

	if (grid[targetR][targetC]->getObjectID() != "floortile" && grid[targetR][targetC]->getObjectID() != "doorway" && grid[targetR][targetC]->getObjectID() != "passage") {
		if (grid[targetR][targetC]->getSuperObjectID() != "gold") {
			return "Cannot move there. ";
		} else {
			if (grid[targetR][targetC]->getObjectID() == "dragonhoard") {
				if (!static_cast<DragonHoard*>(grid[targetR][targetC])->dragonDead()) {
					return "Cannot pick up the gold because the Dragon protecting it is not dead. ";
				}
			}

			int temp = static_cast<Player*>(grid[playerR][playerC])->getPrevStepObject();

			static_cast<Player*>(grid[playerR][playerC])->setPrevStepObject(0);

			int gold = (static_cast<Gold*>(grid[targetR][targetC]))->getGold();

			static_cast<Gold*>(grid[targetR][targetC])->adjustGold(static_cast<Player*>(grid[playerR][playerC]));

			delete grid[targetR][targetC];
			grid[targetR][targetC] = grid[playerR][playerC];

			if (temp == 0) {
				grid[playerR][playerC] = new FloorTile(playerR, playerC, "floortile");
			} else if (temp == 1) {
				grid[playerR][playerC] = new Doorway(playerR, playerC, "doorway");
			} else {
				grid[playerR][playerC] = new Passage(playerR, playerC, "passage");
			}

			playerR = targetR;
			playerC = targetC;
			std::string s;
			std::ostringstream out;
			out << gold;
			s = out.str();
			return "PC picked up " + s + " gold. ";
		}
	} else {
		int temp = static_cast<Player*>(grid[playerR][playerC])->getPrevStepObject();

		if (grid[targetR][targetC]->getObjectID() == "floortile") {
			static_cast<Player*>(grid[playerR][playerC])->setPrevStepObject(0);
		} else if (grid[targetR][targetC]->getObjectID() == "doorway") {
			static_cast<Player*>(grid[playerR][playerC])->setPrevStepObject(1);
		} else if (grid[targetR][targetC]->getObjectID() == "passage") {
			static_cast<Player*>(grid[playerR][playerC])->setPrevStepObject(2);
		}

		string s = "";

		delete grid[targetR][targetC];
		grid[targetR][targetC] = grid[playerR][playerC];

		if (temp == 0) {
			grid[playerR][playerC] = new FloorTile(playerR, playerC, "floortile");
		} else if (temp == 1) {
			grid[playerR][playerC] = new Doorway(playerR, playerC, "doorway");
		} else {
			grid[playerR][playerC] = new Passage(playerR, playerC, "passage");
		}

		playerR = targetR;
		playerC = targetC;

		string direction2;
		if (direction == "no") {
			direction2 = "North";
		} else if (direction == "so") {
			direction2 = "South";
		} else if (direction == "ea") {
			direction2 = "East";
		} else if (direction == "we") {
			direction2 = "West";
		} else if (direction == "ne") {
			direction2 = "Northeast";
		} else if (direction == "nw") {
			direction2 = "Northwest";
		} else if (direction == "sw") {
			direction2 = "Southwest";
		} else {
			direction2 = "Southeast";
		}
		s.append("PC moves " + direction2);

		if ((grid[playerR - 1][playerC] != 0
					&& grid[playerR - 1][playerC]->getSuperObjectID() == "potion")
				|| (grid[playerR + 1][playerC] != 0
					&& grid[playerR + 1][playerC]->getSuperObjectID()
					== "potion")
				|| (grid[playerR][playerC + 1] != 0
					&& grid[playerR][playerC + 1]->getSuperObjectID()
					== "potion")
				|| (grid[playerR][playerC - 1] != 0
					&& grid[playerR][playerC - 1]->getSuperObjectID()
					== "potion")
				|| (grid[playerR - 1][playerC + 1] != 0
					&& grid[playerR - 1][playerC + 1]->getSuperObjectID()
					== "potion")
				|| (grid[playerR - 1][playerC - 1] != 0
					&& grid[playerR - 1][playerC - 1]->getSuperObjectID()
					== "potion")
				|| (grid[playerR + 1][playerC - 1] != 0
					&& grid[playerR + 1][playerC - 1]->getSuperObjectID()
					== "potion")
				|| (grid[playerR + 1][playerC + 1] != 0
					&& grid[playerR + 1][playerC + 1]->getSuperObjectID()
					== "potion")) {
						s.append(" and sees an unknown potion. ");
					} else {
						s.append(". ");
					}

		return s;
	}
}

/*********** usePotionHelper ***********
 Purpose: this fuction is a helper for use potions
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::usePotionHelper(int targetR, int targetC) {
	if (grid[targetR][targetC] == 0
			|| grid[targetR][targetC]->getSuperObjectID() != "potion") {
		return "No potion there. ";
	} else {
		string s = "PC uses " + grid[targetR][targetC]->getObjectID() + ". ";

		// player uses potion
		static_cast<Potion*>(grid[targetR][targetC])->usePotion(static_cast<Player*>(grid[playerR][playerC]));

		// remove the potion
		delete grid[targetR][targetC];

		// add a floortile to where the potion was
		setGameObject(targetR, targetC, new FloorTile(targetR, targetC, "floortile"));

		return s;
	}
}

/*********** playerAttckHelper ***********
 Purpose: this fuction is a helper for the player attacking
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::playerAttackHelper(int targetR, int targetC, Enemy** enemies, int numEnemies) {
	if (grid[targetR][targetC] == 0 || grid[targetR][targetC]->getSuperObjectID() != "enemy") {
		return "You cannot attack there. ";
	} else {
		// player attacks the enemy
		string s = static_cast<Player*>(grid[playerR][playerC])->attack(static_cast<Enemy*>(grid[targetR][targetC]));

		// remove the enemy if dead
		if (static_cast<Enemy*>(grid[targetR][targetC])->isDead()) {
			for (int i = 0; i < numEnemies; i++) {
				if (enemies[i] == grid[targetR][targetC]) {
					enemies[i] = 0;
				}
			}

			GameObject* temp = grid[targetR][targetC];

			if (grid[targetR][targetC]->getObjectID() == "merchant") {
				setGameObject(targetR, targetC, new MerchantHoard(targetR, targetC, "merchanthoard"));
			} else {
				setGameObject(targetR, targetC, new FloorTile(targetR, targetC, "floortile"));
			}

			delete temp;
		}

		return s;
	}
}

// singleton instance for a dungeon grid
DungeonGrid* DungeonGrid::instance = 0;

// get the singleton instance for the dungeon grid
DungeonGrid* DungeonGrid::getInstance() {
	if (!instance) {
		instance = new DungeonGrid();
		atexit(cleanup);
	}

	return instance;
}

/*********** cleanup ***********
 Purpose: this fuction cleans up for freeing the dungeon grid
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::cleanup() {
	delete instance;
}

/*********** DungeonGrid ***********
 Purpose: this is a constructor for DungeonGrid
 
 Returns: N/A
 
 Errors: none
 *********************************/
DungeonGrid::DungeonGrid() {
	// width and height of the dungeon grid
	this->width = 79;
	this->height = 25;

	// create and initialize the grid of game objects
	grid = new GameObject**[height];
	for (int i = 0; i < height; i++) {
		grid[i] = new GameObject*[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grid[i][j] = 0;
		}
	}

	// 5 chambers
	chambers = new Chamber*[5];
	for (int i = 0; i < 5; i++) {
		chambers[i] = 0;
	}
}

/*********** ~DungeonGrid ***********
 Purpose: Destructor for DungeionGrid
 
 Returns: N/A
 
 Errors: none
 *********************************/
DungeonGrid::~DungeonGrid() {
	clearDungeon(true);
}

/*********** setupobjects ***********
 Purpose: this fuction sets up objects for the DungeionGrid
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::setupObjects(Player* player, Enemy** enemies) {
	// spawn the player
	int chamberNumberPlayer = rand() % 5;
	spawnPlayer(chamberNumberPlayer, player);

	// spawn the stairs
	int chamberNumberStairs = rand() % 5;
	while (chamberNumberStairs == chamberNumberPlayer) {
		chamberNumberStairs = rand() % 5;
	}
	spawnStairs(chamberNumberStairs);

	spawnPotions();

	int numEnemies = 20;
	int enemyIndex = 0;

	spawnGold(numEnemies, enemyIndex, enemies);

	spawnEnemies(numEnemies, enemyIndex, enemies);
}

/*********** spawnPlayer ***********
 Purpose: this function spawns player on the grid
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::spawnPlayer(int chamberNumberPlayer, Player* player) {
	int chamberRowNum = chambers[chamberNumberPlayer]->getChamberRow();

	int r = chambers[chamberNumberPlayer]->getRowNumber(chamberRowNum);
	int c = chambers[chamberNumberPlayer]->getColumnNumber(chamberRowNum);

	while (grid[r][c]->getObjectID() != "floortile") {
		chamberRowNum = chambers[chamberNumberPlayer]->getChamberRow();

		r = chambers[chamberNumberPlayer]->getRowNumber(chamberRowNum);
		c = chambers[chamberNumberPlayer]->getColumnNumber(chamberRowNum);
	}

	delete grid[r][c];
	grid[r][c] = player;
	player->setPrevStepObject(0);

	playerR = r;
	playerC = c;
}

/*********** spawnStairs ***********
 Purpose: this function randomly spawns stairs on grid
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::spawnStairs(int chamberNumberStairs) {
	int chamberRowNum = chambers[chamberNumberStairs]->getChamberRow();

	int r = chambers[chamberNumberStairs]->getRowNumber(chamberRowNum);
	int c = chambers[chamberNumberStairs]->getColumnNumber(chamberRowNum);

	while (grid[r][c]->getObjectID() != "floortile") {
		chamberRowNum = chambers[chamberNumberStairs]->getChamberRow();

		r = chambers[chamberNumberStairs]->getRowNumber(chamberRowNum);
		c = chambers[chamberNumberStairs]->getColumnNumber(chamberRowNum);
	}

	delete grid[r][c];
	grid[r][c] = new Stairs(r, c, "stairs");
}

/*********** spawnPotions ***********
 Purpose: this fuction randomly spawns potions on the grid
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::spawnPotions() {
	int numPotions = 10;

	for (int i = 0; i < numPotions; i++) {
		int chamberNum = rand() % 5;

		int chamberRowNum = chambers[chamberNum]->getChamberRow();

		int r = chambers[chamberNum]->getRowNumber(chamberRowNum);
		int c = chambers[chamberNum]->getColumnNumber(chamberRowNum);

		while (grid[r][c]->getObjectID() != "floortile") {
			chamberNum = rand() % 5;

			chamberRowNum = chambers[chamberNum]->getChamberRow();

			r = chambers[chamberNum]->getRowNumber(chamberRowNum);
			c = chambers[chamberNum]->getColumnNumber(chamberRowNum);
		}

		delete grid[r][c];
		int whichPotion = rand() % 6;
		if (whichPotion == 0) {
			grid[r][c] = new RestoreHealth(r, c, "RH");
		} else if (whichPotion == 1) {
			grid[r][c] = new BoostAttack(r, c, "BA");
		} else if (whichPotion == 2) {
			grid[r][c] = new BoostDef(r, c, "BD");
		} else if (whichPotion == 3) {
			grid[r][c] = new PoisonHealth(r, c, "PH");
		} else if (whichPotion == 4) {
			grid[r][c] = new WoundAttack(r, c, "WA");
		} else {
			grid[r][c] = new WoundDef(r, c, "WD");
		}
	}
}

/*********** spawnGold ***********
 Purpose: this fuction randomly spawns gold on the board
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::spawnGold(int& numEnemies, int& enemyIndex, Enemy** enemies) {
	int numGold = 10;

	for (int i = 0; i < numGold; i++) {
		int chamberNum = rand() % 5;

		int chamberRowNum = chambers[chamberNum]->getChamberRow();

		int r = chambers[chamberNum]->getRowNumber(chamberRowNum);
		int c = chambers[chamberNum]->getColumnNumber(chamberRowNum);

		while (grid[r][c]->getObjectID() != "floortile") {
			chamberNum = rand() % 5;

			chamberRowNum = chambers[chamberNum]->getChamberRow();

			r = chambers[chamberNum]->getRowNumber(chamberRowNum);
			c = chambers[chamberNum]->getColumnNumber(chamberRowNum);
		}

		int whichGold = rand() % 8;
		if (0 <= whichGold && whichGold <= 1) {
			delete grid[r][c];
			grid[r][c] = new SmallHoard(r, c, "smallhoard");
		} else if (whichGold == 2) {
			while (grid[r - 1][c]->getObjectID() != "floortile"
					&& grid[r - 1][c + 1]->getObjectID() != "floortile"
					&& grid[r][c + 1]->getObjectID() != "floortile"
					&& grid[r + 1][c + 1]->getObjectID() != "floortile"
					&& grid[r + 1][c]->getObjectID() != "floortile"
					&& grid[r + 1][c - 1]->getObjectID() != "floortile"
					&& grid[r][c - 1]->getObjectID() != "floortile"
					&& grid[r - 1][c - 1]->getObjectID() != "floortile") {
				chamberNum = rand() % 5;

				chamberRowNum = chambers[chamberNum]->getChamberRow();

				r = chambers[chamberNum]->getRowNumber(chamberRowNum);
				c = chambers[chamberNum]->getColumnNumber(chamberRowNum);

				while (grid[r][c]->getObjectID() != "floortile") {
					chamberNum = rand() % 5;

					chamberRowNum = chambers[chamberNum]->getChamberRow();

					r = chambers[chamberNum]->getRowNumber(chamberRowNum);
					c = chambers[chamberNum]->getColumnNumber(chamberRowNum);
				}
			}

			delete grid[r][c];
			grid[r][c] = new DragonHoard(r, c, "dragonhoard");
			if (grid[r - 1][c]->getObjectID() == "floortile") {
				delete grid[r - 1][c];
				grid[r - 1][c] = new Dragon(r - 1, c, r, c, "dragon", static_cast<DragonHoard*>(grid[r][c]));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r - 1][c]);
			} else if (grid[r - 1][c + 1]->getObjectID() == "floortile") {
				delete grid[r - 1][c + 1];
				grid[r - 1][c + 1] = new Dragon(r - 1, c + 1, r, c, "dragon", static_cast<DragonHoard*>(grid[r][c]));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r - 1][c + 1]);
			} else if (grid[r][c + 1]->getObjectID() == "floortile") {
				delete grid[r][c + 1];
				grid[r][c + 1] = new Dragon(r, c + 1, r, c, "dragon", static_cast<DragonHoard*>(grid[r][c]));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c + 1]);
			} else if (grid[r + 1][c + 1]->getObjectID() == "floortile") {
				delete grid[r + 1][c + 1];
				grid[r + 1][c + 1] = new Dragon(r + 1, c + 1, r, c, "dragon", static_cast<DragonHoard*>(grid[r][c]));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r + 1][c + 1]);
			} else if (grid[r + 1][c]->getObjectID() == "floortile") {
				delete grid[r + 1][c];
				grid[r + 1][c] = new Dragon(r + 1, c, r, c, "dragon", static_cast<DragonHoard*>(grid[r][c]));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r + 1][c]);
			} else if (grid[r + 1][c - 1]->getObjectID() == "floortile") {
				delete grid[r + 1][c - 1];
				grid[r + 1][c - 1] = new Dragon(r + 1, c - 1, r, c, "dragon", static_cast<DragonHoard*>(grid[r][c]));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r + 1][c - 1]);
			} else if (grid[r][c - 1]->getObjectID() == "floortile") {
				delete grid[r][c - 1];
				grid[r][c - 1] = new Dragon(r, c - 1, r, c, "dragon", static_cast<DragonHoard*>(grid[r][c]));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c - 1]);
			} else {
				delete grid[r - 1][c - 1];
				grid[r - 1][c - 1] = new Dragon(r - 1, c - 1, r, c, "dragon", static_cast<DragonHoard*>(grid[r][c]));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r - 1][c - 1]);
			}

			enemyIndex++;
			numEnemies--;
		} else {
			delete grid[r][c];
			grid[r][c] = new NormalHoard(r, c, "normalhoard");
		}
	}
}

/*********** spawnEnemies ***********
 Purpose: this fuction randomly spawns enemies on the grid
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::spawnEnemies(int numEnemies, int enemyIndex,
		Enemy** enemies) {
	for (int i = 0; i < numEnemies; i++) {
		int chamberNum = rand() % 5;

		int chamberRowNum = chambers[chamberNum]->getChamberRow();

		int r = chambers[chamberNum]->getRowNumber(chamberRowNum);
		int c = chambers[chamberNum]->getColumnNumber(chamberRowNum);

		while (grid[r][c]->getObjectID() != "floortile") {
			chamberNum = rand() % 5;

			chamberRowNum = chambers[chamberNum]->getChamberRow();

			r = chambers[chamberNum]->getRowNumber(chamberRowNum);
			c = chambers[chamberNum]->getColumnNumber(chamberRowNum);
		}

		delete grid[r][c];
		int whichEnemy = rand() % 18;
		if (0 <= whichEnemy && whichEnemy <= 3) {
			grid[r][c] = new Human(r, c, "human");
		} else if (4 <= whichEnemy && whichEnemy <= 6) {
			grid[r][c] = new Dwarf(r, c, "dwarf");
		} else if (7 <= whichEnemy && whichEnemy <= 11) {
			grid[r][c] = new Halfling(r, c, "halfling");
		} else if (12 <= whichEnemy && whichEnemy <= 13) {
			grid[r][c] = new Elf(r, c, "elf");
		} else if (14 <= whichEnemy && whichEnemy <= 15) {
			grid[r][c] = new Orc(r, c, "orc");
		} else {
			grid[r][c] = new Merchant(r, c, "merchant");
		}

		enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
		enemyIndex++;
	}
}
/*********** setgameobjects ***********
 Purpose: this fuction sets the objects on to the grid
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::setGameObject(int r, int c, GameObject* gameObject) {
	grid[r][c] = gameObject;
}

/*********** enemiesmove ***********
 Purpose: this fuction move the ememies on the grid
 
 Returns: void
 
 Errors: none
 *********************************/
string DungeonGrid::enemiesMove(Enemy **enemies, int numEnemies) {
	string s = "";
	for (int i = 0; i < numEnemies; i++) {
		if (enemies[i] != 0) {
			s.append(enemies[i]->move(this));
		}
	}

	return s;
}

/*********** getGameObject ***********
 Purpose: this fuction gets the game object on the grid
 
 Returns:gameobject*
 
 Errors: none
 *********************************/
GameObject* DungeonGrid::getGameObject(int r, int c) {
	return grid[r][c];
}

#if GAMETYPE == 1

/*********** playerMove ***********
 Purpose: this fuction moves your player in the required directon as taken in by the string
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::playerMove(string direction) {
	if (direction == "no") {
		return playerMoveHelper(playerR - 1, playerC, direction);
	} else if (direction == "so") {
		return playerMoveHelper(playerR + 1, playerC, direction);
	} else if (direction == "ea") {
		return playerMoveHelper(playerR, playerC + 1, direction);
	} else if (direction == "we") {
		return playerMoveHelper(playerR, playerC - 1, direction);
	} else if (direction == "ne") {
		return playerMoveHelper(playerR - 1, playerC + 1, direction);
	} else if (direction == "nw") {
		return playerMoveHelper(playerR - 1, playerC - 1, direction);
	} else if (direction == "sw") {
		return playerMoveHelper(playerR + 1, playerC - 1, direction);
	} else {
		return playerMoveHelper(playerR + 1, playerC + 1, direction);
	}
}

/*********** usePotion ***********
 Purpose: this fuction uses the potion in the given direction by the string taken in
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::usePotion(string direction) {
	if (direction == "no") {
		return usePotionHelper(playerR - 1, playerC);
	} else if (direction == "so") {
		return usePotionHelper(playerR + 1, playerC);
	} else if (direction == "ea") {
		return usePotionHelper(playerR, playerC + 1);
	} else if (direction == "we") {
		return usePotionHelper(playerR, playerC - 1);
	} else if (direction == "ne") {
		return usePotionHelper(playerR - 1, playerC + 1);
	} else if (direction == "nw") {
		return usePotionHelper(playerR - 1, playerC - 1);
	} else if (direction == "sw") {
		return usePotionHelper(playerR + 1, playerC - 1);
	} else {
		return usePotionHelper(playerR + 1, playerC + 1);
	}
}

/*********** playerAttack ***********
 Purpose: this fuction makes the player attack inthe given direction
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::playerAttack(string direction, Enemy** enemies, int numEnemies) {
	if (direction == "no") {
		return playerAttackHelper(playerR - 1, playerC, enemies, numEnemies);
	} else if (direction == "so") {
		return playerAttackHelper(playerR + 1, playerC, enemies, numEnemies);
	} else if (direction == "ea") {
		return playerAttackHelper(playerR, playerC + 1, enemies, numEnemies);
	} else if (direction == "we") {
		return playerAttackHelper(playerR, playerC - 1, enemies, numEnemies);
	} else if (direction == "ne") {
		return playerAttackHelper(playerR - 1, playerC + 1, enemies, numEnemies);
	} else if (direction == "nw") {
		return playerAttackHelper(playerR - 1, playerC - 1, enemies, numEnemies);
	} else if (direction == "sw") {
		return playerAttackHelper(playerR + 1, playerC - 1, enemies, numEnemies);
	} else {
		return playerAttackHelper(playerR + 1, playerC + 1, enemies, numEnemies);
	}
}

/*********** operator << ***********
 Purpose: this is an overloaded  output operator for printing out the whole grid
 
 Returns: ostream&
 
 Errors: none
 *********************************/
ostream & operator<<(ostream & o, DungeonGrid & dungeonGrid) {
	for (int i = 0; i < dungeonGrid.height; i++) {
		for (int j = 0; j < dungeonGrid.width; j++) {
			if (dungeonGrid.grid[i][j] == 0) {
				o << ' ';
			} else {
				o << dungeonGrid.grid[i][j];
			}
		}
		o << endl;
	}

	return o;
}

/*********** createDefaultFloor ***********
 Purpose: this fuction creates a default floor if no other argument is given
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::createDefaultFloor(string filename, Player* player, int& track, Enemy** enemies) {
	if (filename == "") {
		ifstream ifs("defaultfloor.txt");

		char ch; // character to be read from the file
		// corresponding coordinates on the dungeon grid
		int r = 0;
		int c = 0;
		while (!ifs.eof()) {
			ch = ifs.get();

			if (ch == '|') {
				setGameObject(r, c, new VerticalWall(r, c, "verticalwall"));
				c++;
			} else if (ch == '-') {
				setGameObject(r, c, new HorizontalWall(r, c, "horizontalwall"));
				c++;
			} else if (ch == '+') {
				setGameObject(r, c, new Doorway(r, c, "doorway"));
				c++;
			} else if (ch == '#') {
				setGameObject(r, c, new Passage(r, c, "passage"));
				c++;
			} else if (ch == ' ') {
				setGameObject(r, c, 0);
				c++;
			} else if (ch == '.') {
				setGameObject(r, c, new FloorTile(r, c, "floortile"));
				c++;
			} else {
				r++;
				c = 0;
			}
		}

		chambers[0] = new Chamber(6);
		chambers[1] = new Chamber(12);
		chambers[2] = new Chamber(5);
		chambers[3] = new Chamber(9);
		chambers[4] = new Chamber(8);

		// chamber #1 in default map
		for (int i = 0; i < 6; i++) {
			chambers[0]->setObjectCoords(i, 0, i + 2, 2);
			chambers[0]->setObjectCoords(i, 1, i + 2, 29);
		}
		// chamber #2 in default map
		for (int i = 0; i < 2; i++) {
			chambers[1]->setObjectCoords(i, 0, i + 2, 38);
			chambers[1]->setObjectCoords(i, 1, i + 2, 62);
		}
		chambers[1]->setObjectCoords(2, 0, 4, 38);
		chambers[1]->setObjectCoords(2, 1, 4, 70);
		chambers[1]->setObjectCoords(3, 0, 5, 38);
		chambers[1]->setObjectCoords(3, 1, 5, 73);
		for (int i = 4; i < 6; i++) {
			chambers[1]->setObjectCoords(i, 0, i + 2, 38);
			chambers[1]->setObjectCoords(i, 1, i + 2, 76);
		}
		for (int i = 6; i < 12; i++) {
			chambers[1]->setObjectCoords(i, 0, i + 2, 60);
			chambers[1]->setObjectCoords(i, 1, i + 2, 76);
		}
		// chamber #3 in default map
		for (int i = 0; i < 5; i++) {
			chambers[2]->setObjectCoords(i, 0, i + 9, 37);
			chambers[2]->setObjectCoords(i, 1, i + 9, 50);
		}
		// chamber #4 in default map
		for (int i = 0; i < 9; i++) {
			chambers[3]->setObjectCoords(i, 0, i + 14, 3);
			chambers[3]->setObjectCoords(i, 1, i + 14, 25);
		}

		// chamber #5 in default map
		for (int i = 0; i < 3; i++) {
			chambers[4]->setObjectCoords(i, 0, i + 15, 64);
			chambers[4]->setObjectCoords(i, 1, i + 15, 76);
		}
		for (int i = 3; i < 8; i++) {
			chambers[4]->setObjectCoords(i, 0, i + 15, 36);
			chambers[4]->setObjectCoords(i, 1, i + 15, 76);
		}
	} else {
		ifstream ifs(filename.c_str());

		string s;
		for (int i = 0; i < track; i++) {
			getline(ifs, s);
		}

		while (ifs.peek() == '\n') {
			ifs.ignore();
			track++;
		}

		char ch; // character to be read from the file
		// corresponding coordinates on the dungeon grid
		int r = 0;
		int c = 0;

		int enemyIndex = 0;

		while (r < 25) {
			ch = ifs.get();

			if (ch == '|') {
				setGameObject(r, c, new VerticalWall(r, c, "verticalwall"));
				c++; 
			} else if (ch == '-') {
				setGameObject(r, c, new HorizontalWall(r, c, "horizontalwall"));
				c++; 
			} else if (ch == '+') {
				setGameObject(r, c, new Doorway(r, c, "doorway"));
				c++; 
			} else if (ch == '#') {
				setGameObject(r, c, new Passage(r, c, "passage"));
				c++; 
			} else if (ch == ' ') {
				setGameObject(r, c, 0);
				c++;
			} else if (ch == '.') {
				setGameObject(r, c, new FloorTile(r, c, "floortile"));
				c++;
			} else if (ch == '0') {
				setGameObject(r, c, new RestoreHealth(r, c, "RH"));
				c++;
			} else if (ch == '1') {
				setGameObject(r, c, new BoostAttack(r, c, "BA"));
				c++;
			} else if (ch == '2') {
				setGameObject(r, c, new BoostDef(r, c, "BD"));
				c++;
			} else if (ch == '3') {
				setGameObject(r, c, new PoisonHealth(r, c, "PH"));
				c++;
			} else if (ch == '4') {
				setGameObject(r, c, new WoundAttack(r, c, "WA"));
				c++;
			} else if (ch == '5') {
				setGameObject(r, c, new WoundDef(r, c, "WD"));
				c++;
			} else if (ch == '6') {
				setGameObject(r, c, new NormalHoard(r, c, "normalhoard"));
				c++;
			} else if (ch == '7') {
				setGameObject(r, c, new SmallHoard(r, c, "smallhoard"));
				c++;
			} else if (ch == '8') {
				setGameObject(r, c, new MerchantHoard(r, c, "merchanthoard"));
				c++;
			} else if (ch == '9') {
				setGameObject(r, c, new DragonHoard(r, c, "dragonhoard"));
				if (grid[r - 1][c + 1]->getObjectID() == "dragon") {
					if (static_cast<Dragon*>(grid[r - 1][c + 1])->getHoard() == 0) {
						static_cast<Dragon*>(grid[r - 1][c + 1])->setHoard(static_cast<DragonHoard*>(grid[r][c]), r, c);
						static_cast<DragonHoard*>(grid[r][c])->setClaimed();
					}
				} else if (grid[r - 1][c]->getObjectID() == "dragon") {
					if (static_cast<Dragon*>(grid[r - 1][c])->getHoard() == 0) {
						static_cast<Dragon*>(grid[r - 1][c])->setHoard(static_cast<DragonHoard*>(grid[r][c]), r, c);
						static_cast<DragonHoard*>(grid[r][c])->setClaimed();
					}
				} else if (grid[r - 1][c - 1]->getObjectID() == "dragon") {
					if (static_cast<Dragon*>(grid[r - 1][c - 1])->getHoard() == 0) {
						static_cast<Dragon*>(grid[r - 1][c - 1])->setHoard(static_cast<DragonHoard*>(grid[r][c]), r, c);
						static_cast<DragonHoard*>(grid[r][c])->setClaimed();
					}
				} else if (grid[r][c - 1]->getObjectID() == "dragon") {
					if (static_cast<Dragon*>(grid[r][c - 1])->getHoard() == 0) {
						static_cast<Dragon*>(grid[r][c - 1])->setHoard(static_cast<DragonHoard*>(grid[r][c]), r, c);
						static_cast<DragonHoard*>(grid[r][c])->setClaimed();
					}
				}
				c++;
			} else if (ch == '@') {
				setGameObject(r, c, player);
				playerR = r;
				playerC = c;
				c++;
			} else if (ch == '/') {
				setGameObject(r, c, new Stairs(r, c, "stairs"));
				c++;
			} else if (ch == 'D') {
				if (grid[r - 1][c + 1]->getObjectID() == "dragonhoard") {
					if (!static_cast<DragonHoard*>(grid[r - 1][c + 1])->isClaimed()) {
						grid[r][c] = new Dragon(r, c, r - 1, c + 1, "dragon", static_cast<DragonHoard*>(grid[r - 1][c + 1]));
						static_cast<DragonHoard*>(grid[r - 1][c + 1])->setClaimed();
						enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
					} else {
						if (grid[r - 1][c]->getObjectID() != "dragonhoard" && grid[r - 1][c - 1]->getObjectID() != "dragonhoard" && grid[r][c - 1]->getObjectID() != "dragonhoard") {
							grid[r][c] = new Dragon(r, c, r, c, "dragon", 0);
							enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
						}
					}
				} else if (grid[r - 1][c]->getObjectID() == "dragonhoard") {
					if (!static_cast<DragonHoard*>(grid[r - 1][c])->isClaimed()) {
						grid[r][c] = new Dragon(r, c, r - 1, c, "dragon", static_cast<DragonHoard*>(grid[r - 1][c]));
						static_cast<DragonHoard*>(grid[r - 1][c])->setClaimed();
						enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
					} else {
						if (grid[r - 1][c + 1]->getObjectID() != "dragonhoard" && grid[r - 1][c - 1]->getObjectID() != "dragonhoard" && grid[r][c - 1]->getObjectID() != "dragonhoard") {
							grid[r][c] = new Dragon(r, c, r, c, "dragon", 0);
							enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
						}
					}
				} else if (grid[r - 1][c - 1]->getObjectID() == "dragonhoard") {
					if (!static_cast<DragonHoard*>(grid[r - 1][c - 1])->isClaimed()) {
						grid[r][c] = new Dragon(r, c, r - 1, c - 1, "dragon", static_cast<DragonHoard*>(grid[r - 1][c - 1]));
						static_cast<DragonHoard*>(grid[r - 1][c - 1])->setClaimed();
						enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
					} else {
						if (grid[r - 1][c + 1]->getObjectID() != "dragonhoard" && grid[r - 1][c]->getObjectID() != "dragonhoard" && grid[r][c - 1]->getObjectID() != "dragonhoard") {
							grid[r][c] = new Dragon(r, c, r, c, "dragon", 0);
							enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
						}
					}
				} else if (grid[r][c - 1]->getObjectID() == "dragonhoard") {
					if (!static_cast<DragonHoard*>(grid[r][c - 1])->isClaimed()) {
						grid[r][c] = new Dragon(r, c, r, c - 1, "dragon", static_cast<DragonHoard*>(grid[r][c - 1]));
						static_cast<DragonHoard*>(grid[r][c - 1])->setClaimed();
						enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
					} else {
						if (grid[r - 1][c + 1]->getObjectID() != "dragonhoard" && grid[r - 1][c]->getObjectID() != "dragonhoard" && grid[r - 1][c - 1]->getObjectID() != "dragonhoard") {
							grid[r][c] = new Dragon(r, c, r, c, "dragon", 0);
							enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
						}
					}
				} else {
					grid[r][c] = new Dragon(r, c, r, c, "dragon", 0);
					enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				}

				enemyIndex++;
				c++;
			} else if (ch == 'W') {
				setGameObject(r, c, new Dwarf(r, c, "dwarf"));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				enemyIndex++;
				c++;
			} else if (ch == 'E') {
				setGameObject(r, c, new Elf(r, c, "elf"));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				enemyIndex++;
				c++;
			} else if (ch == 'H') {
				setGameObject(r, c, new Human(r, c, "human"));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				enemyIndex++;
				c++;
			} else if (ch == 'L') {
				setGameObject(r, c, new Halfling(r, c, "halfling"));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				enemyIndex++;
				c++;
			} else if (ch == 'M') {
				setGameObject(r, c, new Merchant(r, c, "merchant"));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				enemyIndex++;
				c++;
			} else if (ch == 'O') {
				setGameObject(r, c, new Orc(r, c, "orc"));
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				enemyIndex++;
				c++;
			} else {
				track++;
				r++;
				c = 0;
			}
		} // end while
	} // end if
}


void DungeonGrid::setupFloor(string filename, Player* player, int& track, Enemy** enemies) {
	createDefaultFloor(filename, player, track, enemies);
}

#elif GAMETYPE == 2

/*********** addPotionhelper ***********
 Purpose: this function is a helper to pock up potions
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::addPotionHelper(int targetR, int targetC) {
	if (grid[targetR][targetC] == 0
			|| grid[targetR][targetC]->getSuperObjectID() != "potion") {
		return "No potion there. ";
	} else {
		//adds a potion
		string s = static_cast<Player*>(grid[playerR][playerC])->addPotion(static_cast<Potion*>(grid[targetR][targetC]));

		// add a floortile to where the potion was
		if (s != "Inventory full. "){
			setGameObject(targetR, targetC, new FloorTile(targetR, targetC, "floortile"));
		}

		return s;
	}
}

/*********** buyPotionHelper ***********
 Purpose: this function is helper for buying potions
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::buyPotionHelper(int targetR, int targetC, Player* player) {
	if (grid[targetR][targetC] == 0 || grid[targetR][targetC]->getObjectID() != "merchant") {
		return "No merchant there. ";
	} else {
		bool tracker = false;
		string s = "";
		while (1) {
			clear();
			addstr("Which potion would you like to buy (all cost 5 Gold): 1. RH, 2: BA, 3: BD; or type \"n\" to end transaction.");
			addstr("\n");
			int index;
			index = getch();
			if (index == 'n') {
				if (!tracker) {
					return "No transaction. ";
				} else {
					if (s == "") {
						return "No transaction. ";
					} else {
						return s;
					}
				}
			}
			tracker = true;
			s.append(player->buyPotions(index - 48));
			player->displayPotions();
			addstr("Gold remaining: ");
			ostringstream oss;
			oss << static_cast<int>(player->getGold());
			addstr(oss.str().c_str());
			addstr("\n");

			addstr("Would you like to buy another potion? \"y\" for Yes or \"n\" for No");
			addstr("\n");
			int again;
			again = getch();
			while (again != 'y' && again != 'n') {
				addstr("Please enter the correct command");
				addstr("\n");
				again = getch();
			}

			if (again == 'y') {
				continue;
			} else {
				if (s == "") {
					return "No transaction. ";
				} else {
					return s;
				}
			}
		}
	}
}

/*********** playerMove ***********
 Purpose: this fuction moves the pleyer in the given direction
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::playerMove(int direction) {
	if (direction == 'o') {
		return playerMoveHelper(playerR - 1, playerC, "no");
	} else if (direction == 'l') {
		return playerMoveHelper(playerR + 1, playerC, "so");
	} else if (direction == ';') {
		return playerMoveHelper(playerR, playerC + 1, "ea");
	} else if (direction == 'k') {
		return playerMoveHelper(playerR, playerC - 1, "we");
	} else if (direction == 'p') {
		return playerMoveHelper(playerR - 1, playerC + 1, "ne");
	} else if (direction == 'i') {
		return playerMoveHelper(playerR - 1, playerC - 1, "nw");
	} else if (direction == ',') {
		return playerMoveHelper(playerR + 1, playerC - 1, "sw");
	} else {
		return playerMoveHelper(playerR + 1, playerC + 1, "se");
	}
}

/*********** addPotion ***********
 Purpose: this fuction adds potion from the grid to the inventory
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::addPotion(int direction) {
	if (direction == 'o') {
		return addPotionHelper(playerR - 1, playerC);
	} else if (direction == 'l') {
		return addPotionHelper(playerR + 1, playerC);
	} else if (direction == ';') {
		return addPotionHelper(playerR, playerC + 1);
	} else if (direction == 'k') {
		return addPotionHelper(playerR, playerC - 1);
	} else if (direction == 'p') {
		return addPotionHelper(playerR - 1, playerC + 1);
	} else if (direction == 'i') {
		return addPotionHelper(playerR - 1, playerC - 1);
	} else if (direction == ',') {
		return addPotionHelper(playerR + 1, playerC - 1);
	} else {
		return addPotionHelper(playerR + 1, playerC + 1);
	}
}

/*********** usePotion ***********
 Purpose: this fuction uses the potion from the floor by taking in direction
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::usePotion(int direction) {
	if (direction == 'o') {
		return usePotionHelper(playerR - 1, playerC);
	} else if (direction == 'l') {
		return usePotionHelper(playerR + 1, playerC);
	} else if (direction == ';') {
		return usePotionHelper(playerR, playerC + 1);
	} else if (direction == 'k') {
		return usePotionHelper(playerR, playerC - 1);
	} else if (direction == 'p') {
		return usePotionHelper(playerR - 1, playerC + 1);
	} else if (direction == 'i') {
		return usePotionHelper(playerR - 1, playerC - 1);
	} else if (direction == ',') {
		return usePotionHelper(playerR + 1, playerC - 1);
	} else {
		return usePotionHelper(playerR + 1, playerC + 1);
	}
}

/*********** createDefaultFloor ***********
 Purpose: this fuction player buys the potion from the merchant
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::buyPotion(int direction, Player* player) {
	if (Merchant::getHostility()) {
		return "Merchants are hostile towards PC, they will not sell potions to PC. ";
	}

	if (direction == 'o') {
		return buyPotionHelper(playerR - 1, playerC,player);
	} else if (direction == 'l') {
		return buyPotionHelper(playerR + 1, playerC,player);
	} else if (direction == ';') {
		return buyPotionHelper(playerR, playerC + 1,player);
	} else if (direction == 'k') {
		return buyPotionHelper(playerR, playerC - 1,player);
	} else if (direction == 'p') {
		return buyPotionHelper(playerR - 1, playerC + 1,player);
	} else if (direction == 'i') {
		return buyPotionHelper(playerR - 1, playerC - 1,player);
	} else if (direction == ',') {
		return buyPotionHelper(playerR + 1, playerC - 1,player);
	} else {
		return buyPotionHelper(playerR + 1, playerC + 1,player);
	}
}

/*********** playerAttack ***********
 Purpose: this fuction player attacks an enemy int the given direction
 
 Returns: string
 
 Errors: none
 *********************************/
string DungeonGrid::playerAttack(int direction, Enemy** enemies, int numEnemies) {
	if (direction == 'o') {
		return playerAttackHelper(playerR - 1, playerC, enemies, numEnemies);
	} else if (direction == 'l') {
		return playerAttackHelper(playerR + 1, playerC, enemies, numEnemies);
	} else if (direction == ';') {
		return playerAttackHelper(playerR, playerC + 1, enemies, numEnemies);
	} else if (direction == 'k') {
		return playerAttackHelper(playerR, playerC - 1, enemies, numEnemies);
	} else if (direction == 'p') {
		return playerAttackHelper(playerR - 1, playerC + 1, enemies, numEnemies);
	} else if (direction == 'i') {
		return playerAttackHelper(playerR - 1, playerC - 1, enemies, numEnemies);
	} else if (direction == ',') {
		return playerAttackHelper(playerR + 1, playerC - 1, enemies, numEnemies);
	} else {
		return playerAttackHelper(playerR + 1, playerC + 1, enemies, numEnemies);
	}
}

/*********** operator << ***********
 Purpose: this oveloaded output operator outputs the dungeongrid
 
 Returns: ostream&
 
 Errors: none
 *********************************/
ostream & operator<<(ostream & o, DungeonGrid & dungeonGrid) {
	for (int i = 0; i < dungeonGrid.height; i++) {
		for (int j = 0; j < dungeonGrid.width; j++) {
			if (dungeonGrid.grid[i][j] == 0) {
				addstr(" ");
			} else {
				o << dungeonGrid.grid[i][j];
			}
		}
		addstr("\n");
	}

	return o;
}

/*********** createRandomFloor ***********
 Purpose: this fuction creates random floor for each floor
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::createRandomFloor(string filename, Player* player, int& track, Enemy** enemies) {
	if (filename == "") {
		// set the border of the grid
		for (int i = 0; i < height; i++) {
			grid[i][0] = new VerticalWall(i, 0, "verticalwall");
			grid[i][width - 1] = new VerticalWall(i, width - 1, "verticalwall");
		}
		for (int i = 1; i < width - 1; i++) {
			grid[0][i] = new HorizontalWall(0, i, "horizontalwall");
			grid[height - 1][i] = new HorizontalWall(height - 1, i,
					"horizontalwall");
		}

		//int numChambers = rand() % 2 + 5;

		//if (numChambers == 5) {
		int numRowChamberOne = rand() % 4 + 6;
		int numRowChamberTwo = rand() % 8 + 5;
		int numRowChamberThree = rand() % 7 + 5;
		int numRowChamberFour = rand() % 2 + 5;
		int numRowChamberFive = rand() % 4 + 5;

		// set the actual number of columns in each chamber
		chambers[0] = new Chamber(numRowChamberOne);
		chambers[1] = new Chamber(numRowChamberTwo);
		chambers[2] = new Chamber(numRowChamberThree);
		chambers[3] = new Chamber(numRowChamberFour);
		chambers[4] = new Chamber(numRowChamberFive);

		// set the bounds for each chamber
		chambers[0]->setTopBound(1);
		chambers[0]->setBottomBound(9);
		chambers[0]->setLeftBound(2);
		chambers[0]->setRightBound(30);
		chambers[1]->setTopBound(2);
		chambers[1]->setBottomBound(13);
		chambers[1]->setLeftBound(44);
		chambers[1]->setRightBound(72);
		chambers[2]->setTopBound(12);
		chambers[2]->setBottomBound(22);
		chambers[2]->setLeftBound(3);
		chambers[2]->setRightBound(13);
		chambers[3]->setTopBound(13);
		chambers[3]->setBottomBound(18);
		chambers[3]->setLeftBound(20);
		chambers[3]->setRightBound(39);
		chambers[4]->setTopBound(16);
		chambers[4]->setBottomBound(23);
		chambers[4]->setLeftBound(54);
		chambers[4]->setRightBound(76);

		// set the total number of rows in each chamber
		chambers[0]->setTotalNumRow(chambers[0]->getBottomBound(),
				chambers[0]->getTopBound());
		chambers[1]->setTotalNumRow(chambers[1]->getBottomBound(),
				chambers[1]->getTopBound());
		chambers[2]->setTotalNumRow(chambers[2]->getBottomBound(),
				chambers[2]->getTopBound());
		chambers[3]->setTotalNumRow(chambers[3]->getBottomBound(),
				chambers[3]->getTopBound());
		chambers[4]->setTotalNumRow(chambers[4]->getBottomBound(),
				chambers[4]->getTopBound());

		// set the total number of columns in each chamber
		chambers[0]->setTotalNumColumn(chambers[0]->getLeftBound(),
				chambers[0]->getRightBound());
		chambers[1]->setTotalNumColumn(chambers[1]->getLeftBound(),
				chambers[1]->getRightBound());
		chambers[2]->setTotalNumColumn(chambers[2]->getLeftBound(),
				chambers[2]->getRightBound());
		chambers[3]->setTotalNumColumn(chambers[3]->getLeftBound(),
				chambers[3]->getRightBound());
		chambers[4]->setTotalNumColumn(chambers[4]->getLeftBound(),
				chambers[4]->getRightBound());

		for (int chamberNum = 0; chamberNum < 5; chamberNum++) {
			// determine the row number of the first row in the grid
			int rFirstRow = rand()
				% (chambers[chamberNum]->getTotalNumRow()
						- chambers[chamberNum]->getNumRows() + 1)
				+ chambers[chamberNum]->getTopBound();

			// determine the number of columns of each row
			int numColumns;
			if (chamberNum == 2) {
				numColumns = rand()
					% (chambers[chamberNum]->getTotalNumColumn() / 2 + 2)
					+ chambers[chamberNum]->getTotalNumColumn() / 2;
			} else if (chamberNum == 0 || chamberNum == 1 || chamberNum == 4) {
				numColumns = rand()
					% (chambers[chamberNum]->getTotalNumColumn() / 2 - 2)
					+ chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
			} else {
				numColumns = rand()
					% (chambers[chamberNum]->getTotalNumColumn() / 2 - 3)
					+ chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
			}

			// determine the column numbers for the first and last box of each row
			int cFirstBox = rand()
				% (chambers[chamberNum]->getTotalNumColumn() - numColumns + 1)
				+ chambers[chamberNum]->getLeftBound();
			int cLastBox = cFirstBox + numColumns - 1;

			for (int rowNum = 0; rowNum < chambers[chamberNum]->getNumRows();
					rowNum++) {
				int r = rFirstRow + rowNum;

				if (rowNum == 0
						|| rowNum == chambers[chamberNum]->getNumRows() - 1) {
					grid[r][cFirstBox] = new VerticalWall(r, cFirstBox,
							"verticalwall");
					for (int i = cFirstBox + 1; i < cLastBox; i++) {
						grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
					}
					grid[r][cLastBox] = new VerticalWall(r, cLastBox,
							"verticalwall");
				} else {
					grid[r][cFirstBox] = new VerticalWall(r, cFirstBox,
							"verticalwall");
					for (int i = cFirstBox + 1; i < cLastBox; i++) {
						grid[r][i] = new FloorTile(r, i, "floortile");
					}
					grid[r][cLastBox] = new VerticalWall(r, cLastBox,
							"verticalwall");
				}

				chambers[chamberNum]->setObjectCoords(rowNum, 0, r, cFirstBox);
				chambers[chamberNum]->setObjectCoords(rowNum, 1, r, cLastBox);
			}
		}

		///////////
		///////////
		///////////
		/*
			 for (int chamberNum = 0; chamberNum < 5; chamberNum++) { // loop through the 5 chambers
		// determine the row number of the first row in the grid
		int rFirstRow = rand() % (chambers[chamberNum]->getTotalNumRow() - chambers[chamberNum]->getNumRows() + 1) + chambers[chamberNum]->getTopBound();

		bool closed = false;

		for (int rowNum = 0; rowNum < chambers[chamberNum]->getNumRows(); rowNum++) { // loop through each row of the chamber
		// determine the row number in the grid for the current row
		int r = rFirstRow + rowNum;

		// the column number of the first and last box in the current row in the grid
		int cFirstBox;
		int cLastBox;

		// the column number of the first and last box in the previous row in the grid
		int prevCFirstBox;
		int prevCLastBox;
		if (rowNum != 0) {
		prevCFirstBox = chambers[chamberNum]->getColumnFirstBox(rowNum - 1);
		prevCLastBox = chambers[chamberNum]->getColumnLastBox(rowNum - 1);
		}

		// the number of columns of this row
		int numColumns;

		// determines cFirstBox and cLastBox for this row
		if (rowNum == chambers[chamberNum]->getNumRows() - 1) {
		cFirstBox = prevCFirstBox;
		cLastBox = prevCLastBox;

		// set the objects on the grid
		grid[r][cFirstBox] = new VerticalWall(r, cFirstBox, "verticalwall");
		for (int i = cFirstBox + 1; i < cLastBox; i++) {
		grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
		}
		grid[r][cLastBox] = new VerticalWall(r, cLastBox, "verticalwall");

		chambers[chamberNum]->setObjectCoords(rowNum, 0, r, cFirstBox);
		chambers[chamberNum]->setObjectCoords(rowNum, 1, r, cLastBox);
		} else {
		if (rowNum == 0) {
		// determine number of columns of the first row
		if (chamberNum == 2) {
		numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 + 2) + chambers[chamberNum]->getTotalNumColumn() / 2;
		} else if (chamberNum == 0 || chamberNum == 1 || chamberNum == 4) {
		numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 - 2) + chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
		} else {
		numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 - 3) + chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
		}

		// determine the column number of the first box of this row in the grid
		cFirstBox = rand() % (chambers[chamberNum]->getTotalNumColumn() - numColumns + 1) + chambers[chamberNum]->getLeftBound();

		// determine the column number of the last box of this row in the grid
		cLastBox = cFirstBox + numColumns - 1;

		// set the objects on the grid
		grid[r][cFirstBox] = new VerticalWall(r, cFirstBox, "verticalwall");
		for (int i = cFirstBox + 1; i < cLastBox; i++) {
		grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
		}
		grid[r][cLastBox] = new VerticalWall(r, cLastBox, "verticalwall");

		chambers[chamberNum]->setObjectCoords(rowNum, 0, r, cFirstBox);
		chambers[chamberNum]->setObjectCoords(rowNum, 1, r, cLastBox);
		} else if (rowNum == chambers[chamberNum]->getNumRows() - 2 && !closed) {
		cFirstBox = prevCFirstBox;
		cLastBox = prevCLastBox;

		// set the objects on the grid
		grid[r][cFirstBox] = new VerticalWall(r, cFirstBox, "verticalwall");
		for (int i = cFirstBox + 1; i < cLastBox; i++) {
			grid[r][i] = new FloorTile(r, i, "floortile");
		}
		grid[r][cLastBox] = new VerticalWall(r, cLastBox, "verticalwall");

		chambers[chamberNum]->setObjectCoords(rowNum, 0, r, cFirstBox);
		chambers[chamberNum]->setObjectCoords(rowNum, 1, r, cLastBox);
} else if (!closed) {
	// number of columns of the previous row
	int prevNumColumns = prevCLastBox - prevCFirstBox + 1;

	// determine the number of columns of the current row
	if (chamberNum == 2) {
		numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 + 2) + chambers[chamberNum]->getTotalNumColumn() / 2;
	} else if (chamberNum == 0 || chamberNum == 1 || chamberNum == 4) {
		numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 - 2) + chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
	} else {
		numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 - 3) + chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
	}
	while (numColumns != prevNumColumns && numColumns < prevNumColumns + 4) {
		if (chamberNum == 2) {
			numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 + 2) + chambers[chamberNum]->getTotalNumColumn() / 2;
		} else if (chamberNum == 0 || chamberNum == 1 || chamberNum == 4) {
			numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 - 2) + chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
		} else {
			numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 - 3) + chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
		}
		cout << "here" << endl;
	}

	// place the row based on previous row
	if (numColumns == prevNumColumns) {
		cFirstBox = prevCFirstBox;
		cLastBox = prevCLastBox;

		closed = true;
	} else {
		if (prevCFirstBox - chambers[chamberNum]->getLeftBound() < 2) {
			cFirstBox = prevCFirstBox;
			cLastBox = prevCLastBox;
		} else {
			cFirstBox = prevCFirstBox - rand() % (numColumns - prevNumColumns - 3) - 2;
			while (cFirstBox < chambers[chamberNum]->getLeftBound()) {
				cFirstBox = prevCFirstBox - rand() % (numColumns - prevNumColumns - 3) - 2;
				cout << "chamberNUM: " << chamberNum << endl;
				cout << "chamber left bound: " << chambers[chamberNum]->getLeftBound() << endl;
				cout << "chamber right bound: " << chambers[chamberNum]->getRightBound() << endl;
				cout << "chamber total column #: " << chambers[chamberNum]->getTotalNumColumn() << endl;
				cout << "this row's # of columns: " << numColumns << endl;
				cout << "prev C first box: " << prevCFirstBox << endl;
				cout << "prev C last box: " << prevCLastBox << endl;
				cout << "row num: " << rowNum << endl;
				cout << "first box: " << cFirstBox << endl;
				cout << "last box: " << cLastBox << endl << endl;
			}
			cLastBox = cFirstBox + numColumns - 1;
		}

		closed = false;
	}

	// set the objects on the grid
	grid[r][cFirstBox] = new VerticalWall(r, cFirstBox, "verticalwall");
	for (int i = cFirstBox + 1; i < prevCFirstBox; i++) {
		grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
	}
	if (numColumns > prevNumColumns){
		grid[r][prevCFirstBox] = new VerticalWall(r, prevCFirstBox, "verticalwall");
	}
	for (int i = prevCFirstBox + 1; i < prevCLastBox; i++) {
		grid[r][i] = new FloorTile(r, i, "floortile");
	}
	if (numColumns > prevNumColumns) {
		grid[r][prevCLastBox] = new VerticalWall(r, prevCLastBox, "verticalwall");
	}
	for (int i = prevCLastBox + 1; i < cLastBox; i++) {
		grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
	}
	grid[r][cLastBox] = new VerticalWall(r, cLastBox, "verticalwall");

	chambers[chamberNum]->setObjectCoords(rowNum, 0, r, cFirstBox);
	chambers[chamberNum]->setObjectCoords(rowNum, 1, r, cLastBox);
} else {
	// determine the number of columns of the current row
	if (chamberNum == 2) {
		numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 + 2) + chambers[chamberNum]->getTotalNumColumn() / 2;
	} else if (chamberNum == 0 || chamberNum == 1 || chamberNum == 4) {
		numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 - 2) + chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
	} else {
		numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 - 3) + chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
	}
	while (numColumns > chambers[chamberNum]->getTotalNumColumn() - 6) {
		if (chamberNum == 2) {
			numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 + 2) + chambers[chamberNum]->getTotalNumColumn() / 2;
		} else if (chamberNum == 0 || chamberNum == 1 || chamberNum == 4) {
			numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 - 2) + chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
		} else {
			numColumns = rand() % (chambers[chamberNum]->getTotalNumColumn() / 2 - 3) + chambers[chamberNum]->getTotalNumColumn() / 2 + 4;
		}
	}

	// determine cFirstBox and cLastBox
	cFirstBox = rand() % ((prevCLastBox - 2) - (prevCFirstBox - (numColumns - 2) + 1) + 1) + (prevCFirstBox - (numColumns - 2) + 1);
	cLastBox = cFirstBox + numColumns - 1;
	while (cFirstBox < chambers[chamberNum]->getLeftBound() || cLastBox > chambers[chamberNum]->getRightBound() || abs(cFirstBox - prevCFirstBox) == 1 || abs(cLastBox - prevCLastBox) == 1) {
		cFirstBox = rand() % ((prevCLastBox - 2) - (prevCFirstBox - (numColumns - 2) + 1) + 1) + (prevCFirstBox - (numColumns - 2) + 1);
		cLastBox = cFirstBox + numColumns - 1;
	}

	closed = false;

	// set the objects on the grid
	if (cFirstBox > prevCFirstBox && cFirstBox < prevCLastBox && cLastBox > prevCLastBox) {
		grid[r][prevCFirstBox] = new VerticalWall(r, prevCFirstBox, "verticalwall");
		for (int i = prevCFirstBox + 1; i < cFirstBox; i++) {
			grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
		}
		grid[r][cFirstBox] = new VerticalWall(r, cFirstBox, "verticalwall");
		for (int i = cFirstBox + 1; i < cLastBox; i++) {
			grid[r][i] = new FloorTile(r, i, "floortile");
		}
		grid[r][cLastBox] = new VerticalWall(r, cLastBox, "verticalwall");
		for (int i = prevCLastBox + 1; i < cLastBox; i++) {
			grid[r - 1][i] = new HorizontalWall(r - 1, i, "horizontalwall");
		}
		grid[r - 1][cLastBox] = new VerticalWall(r - 1, cLastBox, "verticalwall");

		chambers[chamberNum]->setObjectCoords(rowNum, 0, r, prevCFirstBox);
		chambers[chamberNum]->setObjectCoords(rowNum, 1, r, cLastBox);
		chambers[chamberNum]->setObjectCoords(rowNum - 1, 1, r - 1, cLastBox);
	} else if (cFirstBox < prevCFirstBox && cLastBox > prevCFirstBox && cLastBox < prevCLastBox) {
		grid[r][cFirstBox] = new VerticalWall(r, cFirstBox, "verticalwall");
		grid[r - 1][cFirstBox] = new VerticalWall(r - 1, cFirstBox, "verticalwall");
		for (int i = cFirstBox + 1; i < prevCFirstBox; i++) {
			grid[r - 1][i] = new HorizontalWall(r - 1, i, "horizontalwall");
		}
		for (int i = cFirstBox + 1; i < cLastBox; i++) {
			grid[r][i] = new FloorTile(r, i, "floortile");
		}
		grid[r][cLastBox] = new VerticalWall(r, cLastBox, "verticalwall");
		for (int i = cLastBox + 1; i < prevCLastBox; i++) {
			grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
		}
		grid[r][prevCLastBox] = new VerticalWall(r, prevCLastBox, "verticalwall");

		chambers[chamberNum]->setObjectCoords(rowNum, 0, r, cFirstBox);
		chambers[chamberNum]->setObjectCoords(rowNum, 1, r, prevCLastBox);
		chambers[chamberNum]->setObjectCoords(rowNum - 1, 0, r - 1, cFirstBox);
	} else if (cFirstBox > prevCFirstBox && cLastBox < prevCLastBox) {
		grid[r][prevCFirstBox] = new VerticalWall(r, prevCFirstBox, "verticalwall");
		for (int i = prevCFirstBox + 1; i < cFirstBox; i++) {
			grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
		}
		grid[r][cFirstBox] = new VerticalWall(r, cFirstBox, "verticalwall");
		for (int i = cFirstBox + 1; i < cLastBox; i++) {
			grid[r][i] = new FloorTile(r, i, "floortile");
		}
		grid[r][cLastBox] = new VerticalWall(r, cLastBox, "verticalwall");
		for (int i = cLastBox + 1; i < prevCLastBox; i++) {
			grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
		}
		grid[r][prevCLastBox] = new VerticalWall(r, prevCLastBox, "verticalwall");

		chambers[chamberNum]->setObjectCoords(rowNum, 0, r, prevCFirstBox);
		chambers[chamberNum]->setObjectCoords(rowNum, 1, r, prevCLastBox);
	} else if (cFirstBox == prevCFirstBox && cLastBox == prevCLastBox) {
		grid[r][prevCFirstBox] = new VerticalWall(r, prevCFirstBox, "verticalwall");
		for (int i = cFirstBox + 1; i < cLastBox; i++) {
			grid[r][i] = new FloorTile(r, i, "floortile");
		}
		grid[r][prevCLastBox] = new VerticalWall(r, prevCLastBox, "verticalwall");

		chambers[chamberNum]->setObjectCoords(rowNum, 0, r, cFirstBox);
		chambers[chamberNum]->setObjectCoords(rowNum, 1, r, cLastBox);
	} else if ((cFirstBox < prevCFirstBox && cLastBox > prevCLastBox) || (cFirstBox < prevCFirstBox && cLastBox == prevCLastBox) || (cFirstBox == prevCFirstBox && cLastBox > prevCLastBox)) {
		if (cFirstBox < prevCFirstBox) {
			grid[r][cFirstBox] = new VerticalWall(r, cFirstBox, "verticalwall");
		}
		for (int i = cFirstBox + 1; i < prevCFirstBox; i++) {
			grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
		}
		grid[r][prevCFirstBox] = new VerticalWall(r, prevCFirstBox, "verticalwall");
		for (int i = prevCFirstBox + 1; i < prevCLastBox; i++) {
			grid[r][i] = new FloorTile(r, i, "floortile");
		}
		grid[r][prevCLastBox] = new VerticalWall(r, prevCLastBox, "verticalwall");
		for (int i = prevCLastBox + 1; i < cLastBox; i++) {
			grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
		}
		if (cLastBox > prevCLastBox) {
			grid[r][cLastBox] = new VerticalWall(r, cLastBox, "verticalwall");
		}

		chambers[chamberNum]->setObjectCoords(rowNum, 0, r, cFirstBox);
		chambers[chamberNum]->setObjectCoords(rowNum, 1, r, cLastBox);
	} else {
		if (cFirstBox > prevCFirstBox) {
			grid[r][prevCFirstBox] = new VerticalWall(r, prevCFirstBox, "verticalwall");
		}
		for (int i = prevCFirstBox + 1; i < cFirstBox; i++) {
			grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
		}
		grid[r][cFirstBox] = new VerticalWall(r, cFirstBox, "verticalwall");
		for (int i = cFirstBox + 1; i < cLastBox; i++) {
			grid[r][i] = new FloorTile(r, i, "floortile");
		}
		grid[r][cLastBox] = new VerticalWall(r, cLastBox, "verticalwall");
		for (int i = cLastBox + 1; i < prevCLastBox; i++) {
			grid[r][i] = new HorizontalWall(r, i, "horizontalwall");
		}
		if (cLastBox < prevCLastBox) {
			grid[r][prevCLastBox] = new VerticalWall(r, prevCLastBox, "verticalwall");
		}

		chambers[chamberNum]->setObjectCoords(rowNum, 0, r, prevCFirstBox);
		chambers[chamberNum]->setObjectCoords(rowNum, 1, r, prevCLastBox);
	}
}
}

cout << "chamberNUM: " << chamberNum << endl;
cout << "chamber left bound: " << chambers[chamberNum]->getLeftBound() << endl;
cout << "chamber right bound: " << chambers[chamberNum]->getRightBound() << endl;
cout << "chamber total column #: " << chambers[chamberNum]->getTotalNumColumn() << endl;
cout << "this row's # of columns: " << numColumns << endl;
cout << "prev C first box: " << prevCFirstBox << endl;
cout << "prev C last box: " << prevCLastBox << endl;
cout << "row num: " << rowNum << endl;
cout << "first box: " << cFirstBox << endl;
cout << "last box: " << cLastBox << endl << endl;
}
}*/
//} else {
//}
// set the passages that are there regardless of how the chambers are
for (int i = 31; i < 44; i++) {
	if (grid[7][i] == 0) {
		grid[7][i] = new Passage(7, i, "passage");
	}
}
for (int i = 14; i < 20; i++) {
	if (grid[15][i] == 0) {
		grid[15][i] = new Passage(15, i, "passage");
	}
}
for (int i = 40; i < 54; i++) {
	if (grid[17][i] == 0) {
		grid[17][i] = new Passage(17, i, "passage");
	}
}
for (int i = 73; i < 76; i++) {
	if (grid[8][i] == 0) {
		grid[8][i] = new Passage(8, i, "passage");
	}
}
for (int i = 17; i < 47; i++) {
	if (grid[21][i] == 0) {
		grid[21][i] = new Passage(21, i, "passage");
	}
}
for (int i = 10; i < 22; i++) {
	if (grid[i][17] == 0) {
		grid[i][17] = new Passage(i, 17, "passage");
	}
}
for (int i = 17; i < 22; i++) {
	if (grid[i][46] == 0) {
		grid[i][46] = new Passage(i, 46, "passage");
	}
}
for (int i = 8; i < 16; i++) {
	if (grid[i][75] == 0) {
		grid[i][75] = new Passage(i, 75, "passage");
	}
}
for (int i = 64; i < 76; i++) {
	if (grid[15][i] == 0) {
		grid[15][i] = new Passage(15, i, "passage");
	}
}

// rightward passage from chamber one
for (int i = 0; i < chambers[0]->getNumRows(); i++) {
	int tempR = chambers[0]->getRowNumber(i);
	int tempC = chambers[0]->getColumnLastBox(i) - 1;

	if (grid[tempR][tempC]->getObjectID() == "floortile") {
		delete grid[tempR][tempC + 1];
		grid[tempR][tempC + 1] = new Doorway(tempR, tempC + 1, "doorway");

		for (int c = tempC + 2; c < 32; c++) {
			if (grid[tempR][c] != 0) {
				delete grid[tempR][c];
			}
			grid[tempR][c] = new Passage(tempR, c, "passage");
		}
		if (tempR <= 7) {
			for (int r = tempR + 1; r < 7; r++) {
				if (grid[r][31] != 0) {
					delete grid[r][31];
				}
				grid[r][31] = new Passage(tempR, 31, "passage");
			}
		} else {
			for (int r = tempR - 1; r > 7; r--) {
				if (grid[r][31] != 0) {
					delete grid[r][31];
				}
				grid[r][31] = new Passage(tempR, 31, "passage");
			}
		}

		break;
	}
}

// downward passage from chamber one
int tempR1 = chambers[0]->getRowNumber(chambers[0]->getNumRows() - 1);
delete grid[tempR1][17];
grid[tempR1][17] = new Doorway(tempR1, 17, "doorway");
for (int i = tempR1 + 1; i < 10; i++) {
	if (grid[i][17] != 0) { 
		delete grid[i][17];
	}
	grid[i][17] = new Passage(i, 17, "passage");
}

// leftward passage from chamber two
for (int i = 0; i < chambers[1]->getNumRows(); i++) {
	int tempR = chambers[1]->getRowNumber(i);
	int tempC = chambers[1]->getColumnFirstBox(i) + 1;

	if (grid[tempR][tempC]->getObjectID() == "floortile") {
		delete grid[tempR][tempC - 1];
		grid[tempR][tempC - 1] = new Doorway(tempR, tempC - 1, "doorway");

		for (int c = tempC - 2; c > 42; c--) {
			if (grid[tempR][c] != 0) { 
				delete grid[tempR][c];
			}
			grid[tempR][c] = new Passage(tempR, c, "passage");
		}
		if (tempR <= 7) {
			for (int r = tempR + 1; r < 7; r++) {
				if (grid[r][43] != 0) { 
					delete grid[r][43];
				}
				grid[r][43] = new Passage(tempR, 43, "passage");
			}
		} else {
			for (int r = tempR - 1; r > 7; r--) {
				if (grid[r][43] != 0) { 
					delete grid[r][43];
				}
				grid[r][43] = new Passage(tempR, 43, "passage");
			}
		}

		break;
	}
}

// rightward passage from chamber two
for (int i = 0; i < chambers[1]->getNumRows(); i++) {
	int tempR = chambers[1]->getRowNumber(i);
	int tempC = chambers[1]->getColumnLastBox(i) - 1;

	if (grid[tempR][tempC]->getObjectID() == "floortile") {
		delete grid[tempR][tempC + 1];
		grid[tempR][tempC + 1] = new Doorway(tempR, tempC + 1, "doorway");

		for (int c = tempC + 2; c < 74; c++) {
			if (grid[tempR][c] != 0) { 
				delete grid[tempR][c];
			}
			grid[tempR][c] = new Passage(tempR, c, "passage");
		}
		if (tempR <= 8) {
			for (int r = tempR + 1; r < 8; r++) {
				if (grid[r][73] != 0) { 
					delete grid[r][73];
				}
				grid[r][73] = new Passage(tempR, 73, "passage");
			}
		} else {
			for (int r = tempR - 1; r > 8; r--) {
				if (grid[r][73] != 0) { 
					delete grid[r][73];
				}
				grid[r][73] = new Passage(tempR, 73, "passage");
			}
		}

		break;
	}
}

// rightward passage from chamber three
for (int i = 0; i < chambers[2]->getNumRows(); i++) {
	int tempR = chambers[2]->getRowNumber(i);
	int tempC = chambers[2]->getColumnLastBox(i) - 1;

	if (grid[tempR][tempC]->getObjectID() == "floortile") {
		delete grid[tempR][tempC + 1];
		grid[tempR][tempC + 1] = new Doorway(tempR, tempC + 1, "doorway");

		for (int c = tempC + 2; c < 15; c++) {
			if (grid[tempR][c] != 0) { 
				delete grid[tempR][c];
			}
			grid[tempR][c] = new Passage(tempR, c, "passage");
		}
		if (tempR <= 15) {
			for (int r = tempR + 1; r < 15; r++) {
				if (grid[r][14] != 0) { 
					delete grid[r][14];
				}
				grid[r][14] = new Passage(tempR, 14, "passage");
			}
		} else {
			for (int r = tempR - 1; r > 15; r--) {
				if (grid[r][14] != 0) { 
					delete grid[r][14];
				}
				grid[r][14] = new Passage(tempR, 14, "passage");
			}
		}

		break;
	}
}

// leftward passage from chamber four
for (int i = 0; i < chambers[3]->getNumRows(); i++) {
	int tempR = chambers[3]->getRowNumber(i);
	int tempC = chambers[3]->getColumnFirstBox(i) + 1;

	if (grid[tempR][tempC]->getObjectID() == "floortile") {
		delete grid[tempR][tempC - 1];
		grid[tempR][tempC - 1] = new Doorway(tempR, tempC - 1, "doorway");

		for (int c = tempC - 2; c > 18; c--) {
			if (grid[tempR][c] != 0) { 
				delete grid[tempR][c];
			}
			grid[tempR][c] = new Passage(tempR, c, "passage");
		}
		if (tempR <= 15) {
			for (int r = tempR + 1; r < 15; r++) {
				if (grid[r][19] != 0) { 
					delete grid[r][19];
				}
				grid[r][19] = new Passage(tempR, 19, "passage");
			}
		} else {
			for (int r = tempR - 1; r > 15; r--) {
				if (grid[r][19] != 0) { 
					delete grid[r][19];
				}
				grid[r][19] = new Passage(tempR, 19, "passage");
			}
		}

		break;
	}
}

// rightward passage from chamber four
for (int i = 0; i < chambers[3]->getNumRows(); i++) {
	int tempR = chambers[3]->getRowNumber(i);
	int tempC = chambers[3]->getColumnLastBox(i) - 1;

	if (grid[tempR][tempC]->getObjectID() == "floortile") {
		delete grid[tempR][tempC + 1];
		grid[tempR][tempC + 1] = new Doorway(tempR, tempC + 1, "doorway");

		for (int c = tempC + 2; c < 41; c++) {
			if (grid[tempR][c] != 0) { 
				delete grid[tempR][c];
			}
			grid[tempR][c] = new Passage(tempR, c, "passage");
		}
		if (tempR <= 17) {
			for (int r = tempR + 1; r < 17; r++) {
				if (grid[r][40] != 0) { 
					delete grid[r][40];
				}
				grid[r][40] = new Passage(tempR, 40, "passage");
			}
		} else {
			for (int r = tempR - 1; r > 17; r--) {
				if (grid[r][40] != 0) { 
					delete grid[r][40];
				}
				grid[r][40] = new Passage(tempR, 40, "passage");
			}
		}

		break;
	}
}

// leftward passage from chamber five
for (int i = 0; i < chambers[4]->getNumRows(); i++) {
	int tempR = chambers[4]->getRowNumber(i);
	int tempC = chambers[4]->getColumnFirstBox(i) + 1;

	if (grid[tempR][tempC]->getObjectID() == "floortile") {
		delete grid[tempR][tempC - 1];
		grid[tempR][tempC - 1] = new Doorway(tempR, tempC - 1, "doorway");

		for (int c = tempC - 2; c > 52; c--) {
			if (grid[tempR][c] != 0) { 
				delete grid[tempR][c];
			}
			grid[tempR][c] = new Passage(tempR, c, "passage");
		}
		if (tempR <= 17) {
			for (int r = tempR + 1; r < 17; r++) {
				if (grid[r][53] != 0) { 
					delete grid[r][53];
				}
				grid[r][53] = new Passage(tempR, 53, "passage");
			}
		} else {
			for (int r = tempR - 1; r > 17; r--) {
				if (grid[r][53] != 0) { 
					delete grid[r][53];
				}
				grid[r][53] = new Passage(tempR, 53, "passage");
			}
		}

		break;
	}
}

// upward passage from chamber five
int tempR2 = chambers[4]->getRowNumber(0);
delete grid[tempR2][64];
grid[tempR2][64] = new Doorway(tempR2, 17, "doorway");
for (int i = tempR2 - 1; i > 15; i--) {
	if (grid[i][64] != 0) { 
		delete grid[i][64];
	}
	grid[i][64] = new Passage(i, 64, "passage");
}
} else {
	ifstream ifs(filename.c_str());

	string s;
	for (int i = 0; i < track; i++) {
		getline(ifs, s);
	}

	while (ifs.peek() == '\n') {
		ifs.ignore();
		track++;
	}

	char ch; // character to be read from the file
	// corresponding coordinates on the dungeon grid
	int r = 0;
	int c = 0;

	int enemyIndex = 0;

	while (r < 25) {
		ch = ifs.get();

		if (ch == '|') {
			setGameObject(r, c, new VerticalWall(r, c, "verticalwall"));
			c++; 
		} else if (ch == '-') {
			setGameObject(r, c, new HorizontalWall(r, c, "horizontalwall"));
			c++; 
		} else if (ch == '+') {
			setGameObject(r, c, new Doorway(r, c, "doorway"));
			c++; 
		} else if (ch == '#') {
			setGameObject(r, c, new Passage(r, c, "passage"));
			c++; 
		} else if (ch == ' ') {
			setGameObject(r, c, 0);
			c++;
		} else if (ch == '.') {
			setGameObject(r, c, new FloorTile(r, c, "floortile"));
			c++;
		} else if (ch == '0') {
			setGameObject(r, c, new RestoreHealth(r, c, "RH"));
			c++;
		} else if (ch == '1') {
			setGameObject(r, c, new BoostAttack(r, c, "BA"));
			c++;
		} else if (ch == '2') {
			setGameObject(r, c, new BoostDef(r, c, "BD"));
			c++;
		} else if (ch == '3') {
			setGameObject(r, c, new PoisonHealth(r, c, "PH"));
			c++;
		} else if (ch == '4') {
			setGameObject(r, c, new WoundAttack(r, c, "WA"));
			c++;
		} else if (ch == '5') {
			setGameObject(r, c, new WoundDef(r, c, "WD"));
			c++;
		} else if (ch == '6') {
			setGameObject(r, c, new NormalHoard(r, c, "normalhoard"));
			c++;
		} else if (ch == '7') {
			setGameObject(r, c, new SmallHoard(r, c, "smallhoard"));
			c++;
		} else if (ch == '8') {
			setGameObject(r, c, new MerchantHoard(r, c, "merchanthoard"));
			c++;
		} else if (ch == '9') {
			setGameObject(r, c, new DragonHoard(r, c, "dragonhoard"));
			if (grid[r - 1][c + 1]->getObjectID() == "dragon") {
				if (static_cast<Dragon*>(grid[r - 1][c + 1])->getHoard() == 0) {
					static_cast<Dragon*>(grid[r - 1][c + 1])->setHoard(static_cast<DragonHoard*>(grid[r][c]), r, c);
					static_cast<DragonHoard*>(grid[r][c])->setClaimed();
				}
			} else if (grid[r - 1][c]->getObjectID() == "dragon") {
				if (static_cast<Dragon*>(grid[r - 1][c])->getHoard() == 0) {
					static_cast<Dragon*>(grid[r - 1][c])->setHoard(static_cast<DragonHoard*>(grid[r][c]), r, c);
					static_cast<DragonHoard*>(grid[r][c])->setClaimed();
				}
			} else if (grid[r - 1][c - 1]->getObjectID() == "dragon") {
				if (static_cast<Dragon*>(grid[r - 1][c - 1])->getHoard() == 0) {
					static_cast<Dragon*>(grid[r - 1][c - 1])->setHoard(static_cast<DragonHoard*>(grid[r][c]), r, c);
					static_cast<DragonHoard*>(grid[r][c])->setClaimed();
				}
			} else if (grid[r][c - 1]->getObjectID() == "dragon") {
				if (static_cast<Dragon*>(grid[r][c - 1])->getHoard() == 0) {
					static_cast<Dragon*>(grid[r][c - 1])->setHoard(static_cast<DragonHoard*>(grid[r][c]), r, c);
					static_cast<DragonHoard*>(grid[r][c])->setClaimed();
				}
			}
			c++;
		} else if (ch == '@') {
			setGameObject(r, c, player);
			playerR = r;
			playerC = c;
			c++;
		} else if (ch == '/') {
			setGameObject(r, c, new Stairs(r, c, "stairs"));
			c++;
		} else if (ch == 'D') {
			if (grid[r - 1][c + 1]->getObjectID() == "dragonhoard") {
				if (!static_cast<DragonHoard*>(grid[r - 1][c + 1])->isClaimed()) {
					grid[r][c] = new Dragon(r, c, r - 1, c + 1, "dragon", static_cast<DragonHoard*>(grid[r - 1][c + 1]));
					static_cast<DragonHoard*>(grid[r - 1][c + 1])->setClaimed();
					enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				} else {
					if (grid[r - 1][c]->getObjectID() != "dragonhoard" && grid[r - 1][c - 1]->getObjectID() != "dragonhoard" && grid[r][c - 1]->getObjectID() != "dragonhoard") {
						grid[r][c] = new Dragon(r, c, r, c, "dragon", 0);
						enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
					}
				}
			} else if (grid[r - 1][c]->getObjectID() == "dragonhoard") {
				if (!static_cast<DragonHoard*>(grid[r - 1][c])->isClaimed()) {
					grid[r][c] = new Dragon(r, c, r - 1, c, "dragon", static_cast<DragonHoard*>(grid[r - 1][c]));
					static_cast<DragonHoard*>(grid[r - 1][c])->setClaimed();
					enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				} else {
					if (grid[r - 1][c + 1]->getObjectID() != "dragonhoard" && grid[r - 1][c - 1]->getObjectID() != "dragonhoard" && grid[r][c - 1]->getObjectID() != "dragonhoard") {
						grid[r][c] = new Dragon(r, c, r, c, "dragon", 0);
						enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
					}
				}
			} else if (grid[r - 1][c - 1]->getObjectID() == "dragonhoard") {
				if (!static_cast<DragonHoard*>(grid[r - 1][c - 1])->isClaimed()) {
					grid[r][c] = new Dragon(r, c, r - 1, c - 1, "dragon", static_cast<DragonHoard*>(grid[r - 1][c - 1]));
					static_cast<DragonHoard*>(grid[r - 1][c - 1])->setClaimed();
					enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				} else {
					if (grid[r - 1][c + 1]->getObjectID() != "dragonhoard" && grid[r - 1][c]->getObjectID() != "dragonhoard" && grid[r][c - 1]->getObjectID() != "dragonhoard") {
						grid[r][c] = new Dragon(r, c, r, c, "dragon", 0);
						enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
					}
				}
			} else if (grid[r][c - 1]->getObjectID() == "dragonhoard") {
				if (!static_cast<DragonHoard*>(grid[r][c - 1])->isClaimed()) {
					grid[r][c] = new Dragon(r, c, r, c - 1, "dragon", static_cast<DragonHoard*>(grid[r][c - 1]));
					static_cast<DragonHoard*>(grid[r][c - 1])->setClaimed();
					enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
				} else {
					if (grid[r - 1][c + 1]->getObjectID() != "dragonhoard" && grid[r - 1][c]->getObjectID() != "dragonhoard" && grid[r - 1][c - 1]->getObjectID() != "dragonhoard") {
						grid[r][c] = new Dragon(r, c, r, c, "dragon", 0);
						enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
					}
				}
			} else {
				grid[r][c] = new Dragon(r, c, r, c, "dragon", 0);
				enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
			}

			enemyIndex++;
			c++;
		} else if (ch == 'W') {
			setGameObject(r, c, new Dwarf(r, c, "dwarf"));
			enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
			enemyIndex++;
			c++;
		} else if (ch == 'E') {
			setGameObject(r, c, new Elf(r, c, "elf"));
			enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
			enemyIndex++;
			c++;
		} else if (ch == 'H') {
			setGameObject(r, c, new Human(r, c, "human"));
			enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
			enemyIndex++;
			c++;
		} else if (ch == 'L') {
			setGameObject(r, c, new Halfling(r, c, "halfling"));
			enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
			enemyIndex++;
			c++;
		} else if (ch == 'M') {
			setGameObject(r, c, new Merchant(r, c, "merchant"));
			enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
			enemyIndex++;
			c++;
		} else if (ch == 'O') {
			setGameObject(r, c, new Orc(r, c, "orc"));
			enemies[enemyIndex] = static_cast<Enemy*>(grid[r][c]);
			enemyIndex++;
			c++;
		} else {
			track++;
			r++;
			c = 0;
		}
	} // end while
}
}

/*********** setUpFloor ***********
 Purpose: this fuction sets up a ramdom floor
 
 Returns: void
 
 Errors: none
 *********************************/
void DungeonGrid::setupFloor(string filename, Player* player, int& track, Enemy** enemies) {
	createRandomFloor(filename, player, track, enemies);
}

#endif
