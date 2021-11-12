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
#include "../Headers/MainGameLoopDriver.h"

void commandProcessorDriver(int argc, char* argv[]) {
	CommandProcessor* processor;
	string source;

	if (argc == 2) {
		processor = new CommandProcessor();
		source = "Command Line";
	}
	else if (argc == 3) {
		processor = new FileCommandProcessorAdaptor(argv[2]);
		source = "File";
	}
	else {
		cout << "You did not enter valid command line arguments when starting Warzone!" << endl;
		return;
	}

	cout << "Because of the given command line argument, commands will be read from source: " + source << endl;
	cout << "Starting with command: loadmap bigeurope.map. This command is called from state: start and results in the map being loaded when executed. (state: maploaded)" << endl;
	State* currentState = new State(Enums::states::start);
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Next command: loadmap bigeurope.map. This command is called from state: maploaded and results in the map being loaded when executed. (state: maploaded)" << endl;
	delete currentState;
	currentState = NULL;
	currentState = new State(Enums::states::mapLoaded);
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Next command: validatemap. This command is called from state: maploaded and results in the map being validated when executed. (state: mapvalidated)" << endl;
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Next command: addplayer Patrick. This command is called from state: mapvalidated and results in the player: Patrick being added when executed. (state: playersadded)" << endl;
	delete currentState;
	currentState = NULL;
	currentState = new State(Enums::states::mapValidated);
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Next command: addplayer William. This command is called from state: playersadded and results in the player: William being added when executed. (state: playersadded)" << endl;
	delete currentState;
	currentState = NULL;
	currentState = new State(Enums::states::playersAdded);
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Next command: addplayer Amadou. This command is called from state: playersadded and results in the player: Amadou being added when executed. (state: playersadded)" << endl;
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Next command: gamestart. This command is called from state: playersadded and results the game starting when executed. (state: assignreinforcements)" << endl;
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Next command: replay. This command is called from state: win and results in a new game starting from before a map is even loaded. (state: start)." << endl;
	delete currentState;
	currentState = NULL;
	currentState = new State(Enums::states::winState);
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Next command: quit. This command is called from state: win and results in the program exiting. (state: none/exit program)." << endl;
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Next command: invalidcommandjusttotest. This command is called from state: win and results in no command being added to the command list." << endl;
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Next command: gamestart. This command is called from state: win and results in no command being added to the command list as this is not a valid state for the command." << endl;
	cout << *(processor->getCommand(currentState)) << endl;

	cout << "Lastly, we will print our command list to demonstrate that only valid commands are added, and the validate() method works correctly." << endl;
	cout << *processor << endl;

	delete currentState;
	currentState = NULL;
	delete processor;
	processor = NULL;
}
void logObserverDriver();
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
			commandProcessorDriver(argc, argv);
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
			mainGameLoopDriver();
 		} 
 		else if(selectedModule == 4) {
			ordersDriver();
 		} 
 		else if(selectedModule == 5) {
			logObserverDriver();
 		}
 	} while(selectedModule != 6);		

	return 0;
}

void logObserverDriver() {
	CommandProcessor* processor = new CommandProcessor();
	GameEngine* engine = new GameEngine(processor);
	bool done = false;
	int counter = 0;
	while (engine->getCurrentState()->getStateName() != Enums::assignReinforcement) {
		cout << "These are the currently available commands: " << endl;
		for (Transition* transition : engine->getAvailableTransitions())
		{
			cout << *transition << endl;
		}
		cout << "-------------------------------------------------------------" << endl;

		cout << "Please enter one of the available commands" << endl;
		processor->getCommand(engine->getCurrentState());
		Command* command = processor->getCommandList().back();
		cout << "-------------------------------------------------------------" << endl;
		engine->execute(command);
		cout << "-------------------------------------------------------------" << endl;
	}
	for (int i = 0; i < engine->getPlayers().size(); i++) {
		engine->getPlayers()[i]->setEnemies(engine->getPlayers());
		engine->getPlayers()[i]->setIsTurnFinish(false);
		engine->getPlayers()[i]->setCanAttack();
	}
	while (!done) {
		for (int i = 0; i < engine->getPlayers().size(); i++) {
			if (!engine->getPlayers()[i]->getIsTurnFinish())
				engine->getPlayers()[i]->issueOrder();
			else
				counter++;
		}
		if (counter == engine->getPlayers().size())
		{
			done = true;
		}
		else {
			counter = 0;
		}
	}
	done = false;
	for (int i = 0; i < engine->getPlayers().size(); i++) {
		for(int j=0;j< engine->getPlayers()[i]->getOrders()->getOrdersVector().size();j++)
			engine->getPlayers()[i]->getOrders()->getOrdersVector()[j]->execute();
	}
}