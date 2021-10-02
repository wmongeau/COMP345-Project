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
		currentState = Enums::statesEnumToString(engine -> getCurrentState() -> getStateName());
		cout << "You are currently in the " << currentState << " state" << endl;
		vector<Transition*> availableTransitions = engine -> getAvailableTransitions();	
		int index = 0;

		for(Transition* transition : availableTransitions) {
			cout << index << " " << Enums::transitionsEnumToString(transition -> getTransitionName()) << endl;
			index++;
		}
		
		cout << "Select a command by entering its number: " << endl;
		int selected;
		cin >> selected;

		engine -> execute(availableTransitions[selected]);
	} while(currentState != "Quit");
}

std::string Enums::statesEnumToString(Enums::states value){
	switch (value){
		case Enums::start: {
			return "Start" ;
	     	}
		case Enums::mapLoaded: {
			return "Map Loaded" ;
	     	}
		case Enums::mapValidated: {
			return "Map Validated" ;
	     	}
		case Enums::playersAdded: {
			return "Players Added" ;
	     	}
		case Enums::assignReinforcement: {
			return "Assign Reinforcement" ;
	     	}
		case Enums::issueOrders: {
			return "Issue Orders" ;
	     	}
		case Enums::executeOrders: {
			return "Execute Orders" ;
	     	}
		case Enums::winState: {
			return "Win" ;
	     	}
		case Enums::quit: {
			return "Quit";
		}
	}

	return "Error";
}

std::string Enums::transitionsEnumToString(Enums::transitions value) {
	switch(value) {
		case Enums::loadMap: {
			return "Load Map";
		}
		case Enums::validateMap: {
			return "Validate Map";
		}
		case Enums::addPlayer: {
			return "Add Player";
		}
		case Enums::assignCountries: {
			return "Assign Countries";
		}
		case Enums::issueOrder: {
			return "Issue an Order";
		}
		case Enums::endIssueOrders: {
			return "End Issuing Orders";
		}
		case Enums::execOrder: {
			return "Execute Order";
		}
		case Enums::endExecuteOrders: {
			return "End Executing Orders";
		}
		case Enums::winTransition: {
			return "Win Transition";
		}
		case Enums::play: {
			return "Play Again";
		}
		case Enums::end: {
			return "Quit";
		}
	}

	return "Error";
}
