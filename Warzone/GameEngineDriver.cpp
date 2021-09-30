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
	string currentState = Enums::statesEnumToString(engine -> getCurrentState().getStateName());
	cout << "You are currently in the " << currentState << "state" << endl;

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
	}

	return "Error";
}
