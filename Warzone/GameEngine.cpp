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

State* Transition::getNextState() {
	return nextState;
}

void Transition::execute() {
	cout << "Executing base transiton" << endl;
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
