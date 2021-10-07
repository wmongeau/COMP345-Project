/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "GameEngine.h"
#include "CardsDriver.h"
#include "MapDriver.h"
#include "OrdersDriver.h"
#include "PlayerDriver.h"

void gameEngineDriver() {
	GameEngine *engine;
	engine = new GameEngine();
	do {
		vector<Transition*> availableTransitions = engine -> getAvailableTransitions();
		cout << *engine << endl;
		cout << "Select a command by entering its number: " << endl;
		int selected;
		cin >> selected;
		
		while(selected < 0 || selected >= availableTransitions.size()){
			cout << "Please select one of the available actions:" << endl;
			cin >> selected;
		}

		engine -> execute(availableTransitions[selected]);
	} while(Enums::statesEnumToString(engine -> getCurrentState() -> getStateName()) != "Quit");

	delete engine;
	engine = NULL;
}

// Entry point for the game
int main() {
	int selectedMode;
	cout << "Select which mode you would like to use by entering its number:" << endl;
	cout << "[0] Evaluation mode" << endl;
	cout << "[1] Normal mode" << endl;
	cin >> selectedMode;

	while(selectedMode != 0 && selectedMode != 1) {
		cout << "Please enter a valid option:" << endl;
		cin >> selectedMode;
	}

	if(selectedMode == 1) {
		cout << "You have selected normal mode!" << endl;
		gameEngineDriver();
	}
	else {
		cout << "You have selected evaluation mode!" << endl;

		int selectedModule;
		do {
			cout << "Enter the number of the part you would like to test:" << endl;
			cout << "[1] Part 1 Map" << endl;
			cout << "[2] Part 2 Player" << endl;
			cout << "[3] Part 3 Orders List" << endl;
			cout << "[4] Part 4 Cards Deck/Hand" << endl;
			cout << "[5] Part 5 Game Engine" << endl;
			cout << "[6] Quit" << endl;

			cin >> selectedModule;

			while(selectedModule < 1 || selectedModule > 6) {
				cout << "Please enter a valid option:" << endl;
				cin >> selectedModule;
			}

			cin.ignore();

			if(selectedModule == 1) {
				mapDriver();
			}
			else if(selectedModule == 2) {
				cout << "Before demonstrating the player class, we must load a map!" << endl; 
				Map* map;
				map = MapLoader::loadMap();
				playerDriver(map);
			}
			else if(selectedModule == 3) {
				ordersDriver();
			}
			else if(selectedModule == 4) {
				cardsDriver();
			}
			else if(selectedModule == 5) {
				gameEngineDriver();
			}
		} while(selectedModule != 6);
	}

	return 0;
}

