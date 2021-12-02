/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <cstring>
#include <iostream>
#include <string>

using namespace std;
#include "../Headers/GameEngine.h"
#include "../Headers/CommandProcessing.h"

void tournamentModeDriver(int argc, char* argv[]) {
	CommandProcessor* processor;

	if (argc == 2) {
		processor = new CommandProcessor();
	}
	else if (argc == 3) {
		processor = new FileCommandProcessorAdaptor(argv[2]);
	}
	else {
		processor = new CommandProcessor();
		//cout << "You did not valid command line arguments when starting Warzone!" << endl;
	}

	GameEngine* engine;
	engine = new GameEngine(processor);

	engine->startupPhase();
	delete engine;
	engine = NULL;
}

void StrategyPattern();

// Entry point for the game
int main(int argc, char *argv[]) {
	int selectedModule; 
 	do {
 		cout << "Enter the number of the part you would like to test:" << endl; 
 		cout << "[1] Part 1  Strategy Pattern" << endl; 
 		cout << "[2] Part 2 Tournament Mode" << endl; 
 		cout << "[3] Quit" << endl;

 		cin >> selectedModule; 

 		while(selectedModule < 1 || selectedModule > 3) { 
 			cout << "Please enter a valid option:" << endl; 
 			cin >> selectedModule; 
 		} 

 		cin.ignore(); 

 		if(selectedModule == 1) {
			StrategyPattern();
		}
 		else if(selectedModule == 2) { 
			tournamentModeDriver(argc, argv);
 		}
 	} while(selectedModule != 3);

	return 0;
}

void StrategyPattern() {
	string arg;
	arg = "StrategyTest.txt";
	FileCommandProcessorAdaptor* fileProcessor = new FileCommandProcessorAdaptor(arg);
	GameEngine* engine = new GameEngine(fileProcessor);
	engine->startupPhase();
	for (int i = 0; i < engine->getPlayers().size();i++) {
		if (engine->getPlayers()[i]->getPlayerName() == "Neutral")
			engine->getPlayers()[0]->changePlayerType(PlayerType::neutral);
		else if (engine->getPlayers()[i]->getPlayerName() == "Benevolent")
			engine->getPlayers()[1]->changePlayerType(PlayerType::benevolent);
		else if (engine->getPlayers()[i]->getPlayerName() == "Human")
			engine->getPlayers()[2]->changePlayerType(PlayerType::human);
		else if (engine->getPlayers()[i]->getPlayerName() == "Aggressive")
			engine->getPlayers()[3]->changePlayerType(PlayerType::aggressive);
		else if (engine->getPlayers()[i]->getPlayerName() == "Cheater")
			engine->getPlayers()[4]->changePlayerType(PlayerType::cheater);
	}
	engine->mainGameLoop();
	delete engine;
	engine = NULL;
}