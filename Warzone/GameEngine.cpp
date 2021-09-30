/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "GameEngine.h"


// Get current state 
// Get possible next states
// Send transition

GameEngine::GameEngine() {
	currentState = new State(Enums::start);
	updateAvailableTransitions();
}


State::State() {
	stateName = Enums::start;
};

State::State(Enums::states name) {
	stateName = name;
}

Enums::states State::getStateName() {
	return stateName;
}

Transition::Transition() {
	transitionName = Enums::end;
}

Transition::Transition(Enums::transitions name) {
	transitionName = name;
}

Enums::transitions Transition::getTransitionName() {
	return transitionName;
}

LoadMapTransition::LoadMapTransition(Enums::transitions name) : Transition(name) {
	nextState = new State(Enums::mapLoaded);
}
void LoadMapTransition::execute() {
	cout << "Executing Load Map Transition";
}

void GameEngine::updateAvailableTransitions() {
	switch(currentState -> getStateName()) {
		case Enums::start: {
			availableTransitions.clear();
			availableTransitions.push_back(new Transition(Enums::loadMap));
			break;
		}
		case Enums::mapLoaded: {
			availableTransitions.clear();
			availableTransitions.push_back(new Transition(Enums::loadMap));
			availableTransitions.push_back( new Transition(Enums::validateMap));
			break;
		}
		case Enums::mapValidated: {
			availableTransitions.clear();
			availableTransitions.push_back(new Transition(Enums::addPlayer));
			break;
		}
		case Enums::playersAdded: {
			availableTransitions.clear();
			availableTransitions.push_back(new Transition(Enums::addPlayer));
			availableTransitions.push_back(new Transition(Enums::assignCountries));
			break;
		}
		case Enums::assignReinforcement: {
			availableTransitions.clear();
			availableTransitions.push_back(new Transition(Enums::issueOrder));
			break;
		}
		case Enums::issueOrders: {
			availableTransitions.clear();
			availableTransitions.push_back(new Transition(Enums::issueOrder));
			availableTransitions.push_back(new Transition(Enums::endIssueOrders));
			break;
		}
		case Enums::executeOrders: {
			availableTransitions.clear();
			availableTransitions.push_back(new Transition(Enums::execOrder));
			availableTransitions.push_back(new Transition(Enums::endExecuteOrders));
			availableTransitions.push_back(new Transition(Enums::winTransition));
			break;
		}
		case Enums::winState: {
			availableTransitions.clear();
			availableTransitions.push_back(new Transition(Enums::play));
			availableTransitions.push_back(new Transition(Enums::end));
			break;
		}
	}
}

void GameEngine::execute(Transition* transition) {
	transition -> execute();
	currentState = transition -> getNextState();
}
