#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <curses.h>

using namespace std;

#include "dungeongrid.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "player.h"
#include "merchant.h"

class Enemy;

#if GAMETYPE == 1

int main(int argc, char* args[]) {
	srand(static_cast<unsigned int>(time(0))); // seed the random number generator
	
	int track = 0;

	string filename = "";
	if (argc == 2) {
		filename = args[1];
	}

	srand(static_cast<unsigned int>(time(0))); // seed the random number generator

	DungeonGrid* dungeonGrid = DungeonGrid::getInstance(); // create the dungeon grid
	Player* player = 0; // the player

	string command;

	bool playerQuit = false;
	bool restart = false;
	bool playerDead = false;
	int floor = 1;

	// each game session
	while (1) {
		if (playerQuit) { // player quits
			break;
		}

		if (floor == 6) { // stairs in floor 5 is reached
			if (player != 0) { // check what race the player is for printing the score
				if (player->getObjectID() == "shade") {
					cout << "Score for this game session: " << static_cast<int>(player->getGold() * 1.5) << endl;
				} else {
					cout << "Score for this game session: " << static_cast<int>(player->getGold()) << endl;
				}

				break;
			}
		}

		floor = 1;

		string actionString = "Action: "; // output for the actions of the game

		// command prompt at the beginning of the game to choose a race or quit
		cout << "Choose 1 of the following races, or type q to exit the game"
			<< endl;
		cout << "d - Drow" << endl;
		cout << "v - Vampire" << endl;
		cout << "t - Troll" << endl;
		cout << "g - Goblin" << endl;
		cout << "s - Shade" << endl << endl;
		cout << "q - Exit" << endl;

		cin >> command;
		// if the command is invalid
		while (command != "q" && command != "d" && command != "v"
				&& command != "t" && command != "g" && command != "s") { // loop exits when the command is valid
			cout << "Please choose one of the options correctly." << endl;
			cin >> command;
		}

		// setup the player stats and add the player to the grid, or exit the game
		if (command == "q") { // quit
			return 0;
		} else if (command == "d") { // Drow
			player = new Drow("drow");
		} else if (command == "v") { // Vampire
			player = new Vampire("vampire");
		} else if (command == "t") { // Troll
			player = new Troll("troll");
		} else if (command == "g") { // Goblin
			player = new Goblin("goblin");
		} else if (command == "s") { // Shade (Default)
			player = new Player(25, 25, 125, 1);
		}

		// restart or first game
		if (restart || playerDead) {
			track = 0;
			dungeonGrid->clearDungeon2(true);
		}

		restart = false;
		playerDead = false;
		Merchant::becomeNeutral();

		// each floor
		while (1) {
			if (restart || playerQuit || floor == 6) {
				break;
			}

			// clear the previous floor
			dungeonGrid->clearDungeon2(false);

			// reset the player's stats
			player->resetStats();
			
			// all the enemies in this floor
			int numEnemies = 20;
			Enemy** enemies = new Enemy*[numEnemies];
			for (int i = 0; i < 20; i++) {
				enemies[i] = 0;
			}

			// setup floor level one
			dungeonGrid->setupFloor(filename, player, track, enemies);

			// setup the objects in game
			if (filename == "") {
				dungeonGrid->setupObjects(player, enemies);
			}

			// print the grid and character info
			cout << *dungeonGrid;
			player->displayStats(floor);
			cout << "Action: Player character has spawned." << endl;

			// each command within a floor
			while (!player->isDead()) {
				cin >> command;

				if (command != "no" && command != "so" && command != "ea"
						&& command != "we" && command != "ne" && command != "nw"
						&& command != "se" && command != "sw" && command != "u"
						&& command != "a" && command != "r" && command != "q") { // invalid command
					cout << "Please enter a valid command." << endl;
					continue;
				} else {
					player->hpRegen(); // regenerate hp for player

					// the player's move
					if (command == "q") { // player quits
						playerQuit = true;
						delete[] enemies;
						break;
					} else if (command == "r") { // player restarts the game
						restart = true;
						delete[] enemies;
						break;
					} else if (command == "no" || command == "so"
							|| command == "ea" || command == "we"
							|| command == "ne" || command == "nw"
							|| command == "se" || command == "sw") { // player moves
						string s = dungeonGrid->playerMove(command);

						if (s == "next floor") { // next floor is reached
							floor++;
							delete[] enemies;
							break;
						} else {
							actionString.append(s);
						}
					} else if (command == "u") { // use a potion on the floor
						string direction;
						cin >> direction;

						actionString.append(dungeonGrid->usePotion(direction));

					} else if (command == "a") { // attack a direction
						string direction;
						cin >> direction;

						actionString.append(dungeonGrid->playerAttack(direction, enemies, numEnemies));
					}

					// enemies' move
					actionString.append(dungeonGrid->enemiesMove(enemies, numEnemies));

					// print the grid
					cout << *dungeonGrid;
					player->displayStats(floor);
					cout << actionString << endl;
					actionString = "Action: ";
				} // end if
			} // end while

			if (player->isDead()) { // player is dead
				floor = 1;
				delete [] enemies;
				playerDead = true;
				break;
			} // end if
		} // end while
	} // end while

	return 0;
}

#elif GAMETYPE == 2

int main(int argc, char* args[]) {
	srand(static_cast<unsigned int>(time(0))); // seed the random number generator
	
	int track = 0;

	string filename = "";
	if (argc == 2) {
		filename = args[1];
	}

	// initialize ncurses
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	//

	DungeonGrid* dungeonGrid = DungeonGrid::getInstance(); // the game grid
	Player* player = 0; // the player

	int command;

	bool playerQuit = false;
	bool restart = false;
	bool playerDead = false;
	int floor = 1;

	// each game session
	while (1) {
		if (playerQuit) { // player quits
			break;
		}

		if (floor == 6) { // the stairs at floor 5 is reached
			if (player != 0) { // determine the race of the player to calculate the score
				clear();
				addstr("Score for this game session: ");
				if (player->getObjectID() == "shade") {
					ostringstream oss;
					oss << static_cast<int>(player->getGold() * 1.5);
					addstr(oss.str().c_str());
					addstr("\n");
				} else {
					ostringstream oss;
					oss << static_cast<int>(player->getGold());
					addstr(oss.str().c_str());
					addstr("\n");
				}
			}
		}

		floor = 1;

		string actionString = "Action: "; // string that displays the actions in the game

		// command prompt at the beginning of the game to choose a race or quit
		addstr("Choose 1 of the following races, or type q to exit the game");
		addstr("\n");
		addstr("d - Drow");
		addstr("\n");
		addstr("v - Vampire");
		addstr("\n");
		addstr("t - Troll");
		addstr("\n");
		addstr("g - Goblin");
		addstr("\n");
		addstr("s - Shade");
		addstr("\n");
		addstr("\n");
		addstr("q - Exit");
		addstr("\n");

		command = getch();
		// if the command is invalid
		while (command != 'q' && command != 'd' && command != 'v'
				&& command != 't' && command != 'g' && command != 's') { // loop exits when the command is valid
			addstr("Please choose one of the options correctly.");
			addstr("\n");
			command = getch();
		}

		// setup the player stats and add the player to the grid, or exit the game
		if (command == 'q') { // quit
			endwin();
			return 0;
		} else if (command == 'd') { // Drow
			player = new Drow("drow");
		} else if (command == 'v') { // Vampire
			player = new Vampire("vampire");
		} else if (command == 't') { // Troll
			player = new Troll("troll");
		} else if (command == 'g') { // Goblin
			player = new Goblin("goblin");
		} else if (command == 's') { // Shade (Default)
			player = new Player(25, 25, 125, 1);
		}

		clear();
		// restart or new game
		if (restart || playerDead) {
			track = 0;
			dungeonGrid->clearDungeon2(true);
		}
		restart = false;
		playerDead = false;
		Merchant::becomeNeutral();

		// each floor
		while (1) {
			if (restart || playerQuit || floor == 6) {
				break;
			}

			// clear the previous floor
			dungeonGrid->clearDungeon2(false);

			// reset the player's stats
			player->resetStats();

			// all the enemies in this floor
			int numEnemies = 20;
			Enemy** enemies = new Enemy*[numEnemies];
			for (int i = 0; i < 20; i++) {
				enemies[i] = 0;
			}

			//setup floor level one
			dungeonGrid->setupFloor(filename, player, track, enemies);
			
			// setup the objects in game
			if (filename == "") {
				dungeonGrid->setupObjects(player, enemies);
			}

			// print the grid and character info
			clear();
			cout << *dungeonGrid;
			player->displayStats(floor);
			player->displayPotions();
			addstr("Action: Player character has spawned.");
			addstr("\n");

			// each command within a floor
			while (!player->isDead()) {
				command = getch();

				if (command != 'o' && command != 'l' && command != ';'
						&& command != 'k' && command != 'p' && command != 'i'
						&& command != '/' && command != ',' && command != 'u'
						&& command != 'a' && command != 'r' && command != 'q'
						&& command != 'z' && command != '1' && command != '2' && command != '3' && command != '4' && command != '5' && command != '6' && command != '7' && command != '8' && command != '9' && command != '0' && command != 'b') { // invalid command
					addstr("Please press a valid command.");
					addstr("\n");
					continue;
				} else {
					player->hpRegen(); // regenerate hp for the player

					// the player's move
					if (command == 'q') { // player quits
						playerQuit = true;
						delete[] enemies;
						break;
					} else if (command == 'r') { // player restart
						restart = true;
						delete[] enemies;
						break;
					} else if (command == 'o' || command == 'l'
							|| command == ';' || command == 'k'
							|| command == 'p' || command == 'i'
							|| command == '/' || command == ',') { // player moves
						string s = dungeonGrid->playerMove(command);

						if (s == "next floor") { // player reaches next floor
							floor++;
							delete[] enemies;
							break;
						} else {
							actionString.append(s);
						}
					} else if (command == 'z') { // player picks up a potion
						int direction;
						direction = getch();

						actionString.append(dungeonGrid->addPotion(direction));
					} else if (command == 'u') { // player uses a potion
						int direction;
						direction = getch();

						actionString.append(dungeonGrid->usePotion(direction));
					} else if (command == '1' || command == '2' || command == '3' || command == '4' || command == '5' || command == '6' || command == '7' || command == '8' || command == '9' || command == '0') { // player uses a potion
						actionString.append(player->usePotion(command - 48));
					} else if (command == 'b') { // player buys a potion from merchant
						int direction;
						direction = getch();

						actionString.append(dungeonGrid->buyPotion(direction, player));
					} else if (command == 'a') { // player attacks a direction
						int direction;
						direction = getch();

						actionString.append(dungeonGrid->playerAttack(direction, enemies, numEnemies));
					}

					// enemies' move
					actionString.append(dungeonGrid->enemiesMove(enemies, numEnemies));

					// print the grid
					clear();
					cout << *dungeonGrid;
					player->displayStats(floor);
					player->displayPotions();
					addstr(actionString.c_str());
					addstr("\n");
					actionString = "Action: ";
				}
			} // end while

			if (player->isDead()) { // player is dead
				floor = 1;
				delete [] enemies;
				playerDead = true;
				break;
			} // end if
		} // end while
	} // end while

	endwin();
	return 0;
}

#endif
