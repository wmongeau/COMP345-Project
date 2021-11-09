/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <cstring>
#include <iostream>
#include <string>

using namespace std;
#include "../Headers/GameEngine.h"
#include "../Headers/CardsDriver.h"
#include "../Headers/MapDriver.h"
#include "../Headers/OrdersDriver.h"
#include "../Headers/PlayerDriver.h"
#include "../Headers/CommandProcessing.h"

// Entry point for the game
int main(int argc, char *argv[]) {
	int selectedModule; 
 	do {
 		cout << "Enter the number of the part you would like to test:" << endl; 
 		cout << "[1] Part 1 Command Processor" << endl; 
 		cout << "[2] Part 2 Startup Phase" << endl; 
 		cout << "[3] Part 3 Main Game Loop" << endl; 
 		cout << "[4] Part 4 Order Execution" << endl; 
 		cout << "[5] Part 5 Game Log Observer" << endl; 
 		cout << "[6] Quit" << endl; 

 		cin >> selectedModule; 

 		while(selectedModule < 1 || selectedModule > 6) { 
 			cout << "Please enter a valid option:" << endl; 
 			cin >> selectedModule; 
 		} 

 		cin.ignore(); 

 		if(selectedModule == 1) { 
 		} 
 		else if(selectedModule == 2) { 
			CommandProcessor* processor;

			if(argc == 2) {
				processor = new CommandProcessor();	
			}
			else if(argc == 3) {
				processor = new FileCommandProcessorAdaptor(argv[2]);
			} 
			else {
				cout << "You did not valid command line arguments when starting Warzone!" << endl;
				return 1;
			}

			GameEngine *engine;
			engine = new GameEngine(processor);

			engine -> startupPhase();
			delete engine;
			engine = NULL;
 		}
 		else if(selectedModule == 3) { 
 		} 
 		else if(selectedModule == 4) {
 		} 
 		else if(selectedModule == 5) {
 		}
 	} while(selectedModule != 6);		

	return 0;
}

