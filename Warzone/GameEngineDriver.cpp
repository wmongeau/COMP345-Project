/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "GameEngine.h"
#include "Map.h"


int main() {
	GameEngine *engine;
	engine = new GameEngine();
	string currentState;
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
	} while(currentState != "Quit");

	return 0;
}

