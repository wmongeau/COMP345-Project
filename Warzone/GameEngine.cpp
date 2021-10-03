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

State::~State() {  }

Transition::Transition() {
	transitionName = Enums::end;
}

Transition::Transition(Enums::transitions name) {
	transitionName = name;
}

Enums::transitions Transition::getTransitionName() {
	return transitionName;
}

State* Transition::getNextState() {
	return nextState;
}

Transition::~Transition() {
	delete nextState;
	nextState = NULL;
}
LoadMapTransition::LoadMapTransition() : Transition(Enums::loadMap) {
	nextState = new State(Enums::mapLoaded);
}

void LoadMapTransition::execute() {
	cout << "Executing Load Map Transition" << endl;
}

ValidateMapTransition::ValidateMapTransition() : Transition(Enums::validateMap) {
	nextState = new State(Enums::mapValidated);
}

void ValidateMapTransition::execute() {
	cout << "Executing Validate Map Transiton" << endl;
}

AddPlayerTransition::AddPlayerTransition() : Transition(Enums::addPlayer) {
	nextState = new State(Enums::playersAdded);
}

void AddPlayerTransition::execute() {
	cout << "Executing Add Player Transition" << endl;
}

AssignCountriesTransition::AssignCountriesTransition() : Transition(Enums::assignCountries) {
	nextState = new State(Enums::assignReinforcement);
}

void AssignCountriesTransition::execute() {
	cout << "Executing Assign Countries Transition" << endl;
}

IssueOrderTransition::IssueOrderTransition() : Transition(Enums::issueOrder) {
	nextState = new State(Enums::issueOrders);
}

void IssueOrderTransition::execute() {
	cout << "Executing Issue Order Transition" << endl;
}

EndIssueOrdersTransition::EndIssueOrdersTransition() : Transition(Enums::endIssueOrders) {
	nextState = new State(Enums::executeOrders);
}

void EndIssueOrdersTransition::execute() {
	cout << "Executing End Issue Orders Transition" << endl;
}

ExecOrderTransition::ExecOrderTransition() : Transition(Enums::execOrder) {
	nextState = new State(Enums::executeOrders);
}

void ExecOrderTransition::execute() {
	cout << "Executing Exec Order Transition" << endl;
}

EndExecOrdersTransition::EndExecOrdersTransition() : Transition(Enums::endExecuteOrders) {
	nextState = new State(Enums::assignReinforcement);
}

void EndExecOrdersTransition::execute() {
	cout << "Executing End Exec Orders Transition" << endl;
}

WinTransition::WinTransition() : Transition(Enums::winTransition) {
	nextState = new State(Enums::winState);
}

void WinTransition::execute() {
	cout << "Executing Win Transition" << endl;
}

PlayTransition::PlayTransition() : Transition(Enums::play) {
	nextState = new State(Enums::start);
}

void PlayTransition::execute() {
	cout << "Executing Play Transition" << endl;
}

EndTransition::EndTransition() : Transition(Enums::end) {
	nextState = new State(Enums::quit);
}

void EndTransition::execute() {
	cout << "Executing End Transition" << endl;
}

void GameEngine::updateAvailableTransitions() {
	switch(currentState -> getStateName()) {
		case Enums::start: {
			availableTransitions.clear();
			availableTransitions.push_back(new LoadMapTransition());
			break;
		}
		case Enums::mapLoaded: {
			availableTransitions.clear();
			availableTransitions.push_back(new LoadMapTransition());
			availableTransitions.push_back(new ValidateMapTransition());
			break;
		}
		case Enums::mapValidated: {
			availableTransitions.clear();
			availableTransitions.push_back(new AddPlayerTransition());
			break;
		}
		case Enums::playersAdded: {
			availableTransitions.clear();
			availableTransitions.push_back(new AddPlayerTransition());
			availableTransitions.push_back(new AssignCountriesTransition());
			break;
		}
		case Enums::assignReinforcement: {
			availableTransitions.clear();
			availableTransitions.push_back(new IssueOrderTransition());
			break;
		}
		case Enums::issueOrders: {
			availableTransitions.clear();
			availableTransitions.push_back(new IssueOrderTransition());
			availableTransitions.push_back(new EndIssueOrdersTransition());
			break;
		}
		case Enums::executeOrders: {
			availableTransitions.clear();
			availableTransitions.push_back(new ExecOrderTransition());
			availableTransitions.push_back(new EndExecOrdersTransition());
			availableTransitions.push_back(new WinTransition());
			break;
		}
		case Enums::winState: {
			availableTransitions.clear();
			availableTransitions.push_back(new PlayTransition());
			availableTransitions.push_back(new EndTransition());
			break;
		}
		case Enums::quit: {
			availableTransitions.clear();
		}
	}
}

State* GameEngine::getCurrentState() {
	return currentState;
}

vector<Transition*> GameEngine::getAvailableTransitions() {
	return availableTransitions;
}

void GameEngine::execute(Transition* transition) {
	transition -> execute();
	currentState = transition -> getNextState();
	updateAvailableTransitions();
}

GameEngine::~GameEngine() {
	delete currentState;
	currentState = NULL;
	availableTransitions.clear();
}
