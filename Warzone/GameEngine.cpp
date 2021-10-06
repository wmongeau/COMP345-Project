/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "GameEngine.h"

State::State() {
	stateName = Enums::start;
};

State::State(Enums::states name) {
	stateName = name;
}

State::State(const State& state){
	stateName = state.stateName;
}

Enums::states State::getStateName() {
	return stateName;
}

std::ostream& operator<<(std::ostream& os, const State& state) {
	os << Enums::statesEnumToString(state.stateName);
	return os;
}

State& State::operator= (const State& state) {
	stateName = state.stateName;
	return *this;
}

State::~State() {  

}

Transition::Transition() {
	transitionName = Enums::end;
}

Transition::Transition(Enums::transitions name) {
	transitionName = name;
}

Transition::Transition(const Transition& transition) {
	transitionName = transition.transitionName;
	nextState = transition.nextState;
}

Enums::transitions Transition::getTransitionName() {
	return transitionName;
}

State* Transition::getNextState() {
	return nextState;
}

std::ostream& operator<<(std::ostream& os, const Transition& transition) {
	os << Enums::transitionsEnumToString(transition.transitionName);
	return os;
}

Transition& Transition::operator= (const Transition& transition) {
	transitionName = transition.transitionName;
	nextState = transition.nextState;
	return *this;
}

Transition::~Transition() {
	delete nextState;
	nextState = NULL;
}

LoadMapTransition::LoadMapTransition() : Transition(Enums::loadMap) {
	nextState = new State(Enums::mapLoaded);
}

LoadMapTransition::LoadMapTransition(const LoadMapTransition& loadMapTransition) : Transition(loadMapTransition.transitionName) {
	nextState = loadMapTransition.nextState;
}

void LoadMapTransition::execute() {
	cout << "Executing Load Map Transition" << endl;
}

LoadMapTransition& LoadMapTransition::operator= (const LoadMapTransition& loadMapTransition) {
	transitionName = loadMapTransition.transitionName;
	nextState = loadMapTransition.nextState;
	return *this;
}

ValidateMapTransition::ValidateMapTransition() : Transition(Enums::validateMap) {
	nextState = new State(Enums::mapValidated);
}

ValidateMapTransition::ValidateMapTransition(const ValidateMapTransition& validateMapTransition) : Transition(validateMapTransition.transitionName) {
	nextState = validateMapTransition.nextState;
}

void ValidateMapTransition::execute() {
	cout << "Executing Validate Map Transiton" << endl;
}

ValidateMapTransition& ValidateMapTransition::operator= (const ValidateMapTransition& validateMapTransition) {
	transitionName = validateMapTransition.transitionName;
	nextState = validateMapTransition.nextState;
	return *this;
}

AddPlayerTransition::AddPlayerTransition() : Transition(Enums::addPlayer) {
	nextState = new State(Enums::playersAdded);
}

AddPlayerTransition::AddPlayerTransition(const AddPlayerTransition& addPlayerTransition) : Transition(addPlayerTransition.transitionName) {
	nextState = addPlayerTransition.nextState;
}

void AddPlayerTransition::execute() {
	cout << "Executing Add Player Transition" << endl;
}

AddPlayerTransition& AddPlayerTransition::operator= (const AddPlayerTransition& addPlayerTransition) {
	transitionName = addPlayerTransition.transitionName;
	nextState = addPlayerTransition.nextState;
	return *this;
}

AssignCountriesTransition::AssignCountriesTransition() : Transition(Enums::assignCountries) {
	nextState = new State(Enums::assignReinforcement);
}

AssignCountriesTransition::AssignCountriesTransition(const AssignCountriesTransition& assignCountriestransition) : Transition(assignCountriestransition.transitionName) {
	nextState = assignCountriestransition.nextState;
}

void AssignCountriesTransition::execute() {
	cout << "Executing Assign Countries Transition" << endl;
}

AssignCountriesTransition& AssignCountriesTransition::operator= (const AssignCountriesTransition& assignCountriesTranstion) {
	transitionName = assignCountriesTranstion.transitionName;
	nextState = assignCountriesTranstion.nextState;
	return *this;
}

IssueOrderTransition::IssueOrderTransition() : Transition(Enums::issueOrder) {
	nextState = new State(Enums::issueOrders);
}

IssueOrderTransition::IssueOrderTransition(const IssueOrderTransition& issueOrderTransition) : Transition(issueOrderTransition.transitionName) {
	nextState = issueOrderTransition.nextState;
}

void IssueOrderTransition::execute() {
	cout << "Executing Issue Order Transition" << endl;
}

IssueOrderTransition& IssueOrderTransition::operator= (const IssueOrderTransition& issueOrderTransition) {
	transitionName = issueOrderTransition.transitionName;
	nextState = issueOrderTransition.nextState;
	return *this;
}

EndIssueOrdersTransition::EndIssueOrdersTransition() : Transition(Enums::endIssueOrders) {
	nextState = new State(Enums::executeOrders);
}

EndIssueOrdersTransition::EndIssueOrdersTransition(const EndIssueOrdersTransition& endIssueOrdersTransition) : Transition(endIssueOrdersTransition.transitionName) {
	nextState = endIssueOrdersTransition.nextState;
}

void EndIssueOrdersTransition::execute() {
	cout << "Executing End Issue Orders Transition" << endl;
}

EndIssueOrdersTransition& EndIssueOrdersTransition::operator= (const EndIssueOrdersTransition& endIssueOrdersTransition) {
	transitionName = endIssueOrdersTransition.transitionName;
	nextState = endIssueOrdersTransition.nextState;
	return *this;
}

ExecOrderTransition::ExecOrderTransition() : Transition(Enums::execOrder) {
	nextState = new State(Enums::executeOrders);
}

ExecOrderTransition::ExecOrderTransition(const ExecOrderTransition& execOrderTransition) : Transition(execOrderTransition.transitionName) {
	nextState = execOrderTransition.nextState;
}

void ExecOrderTransition::execute() {
	cout << "Executing Exec Order Transition" << endl;
}

ExecOrderTransition& ExecOrderTransition::operator= (const ExecOrderTransition& execOrderTransition) {
	transitionName = execOrderTransition.transitionName;
	nextState = execOrderTransition.nextState;
	return *this;
}

EndExecOrdersTransition::EndExecOrdersTransition() : Transition(Enums::endExecuteOrders) {
	nextState = new State(Enums::assignReinforcement);
}

EndExecOrdersTransition::EndExecOrdersTransition(const EndExecOrdersTransition& endExecuteOrdersTransition) : Transition(endExecuteOrdersTransition.transitionName) {
	nextState = endExecuteOrdersTransition.nextState;
}

void EndExecOrdersTransition::execute() {
	cout << "Executing End Exec Orders Transition" << endl;
}

EndExecOrdersTransition& EndExecOrdersTransition::operator= (const EndExecOrdersTransition& endExecuteOrdersTransition) {
	transitionName = endExecuteOrdersTransition.transitionName;
	nextState = endExecuteOrdersTransition.nextState;
	return *this;
}

WinTransition::WinTransition() : Transition(Enums::winTransition) {
	nextState = new State(Enums::winState);
}

WinTransition::WinTransition(const WinTransition& winTransition) : Transition(winTransition.transitionName) {
	nextState = winTransition.nextState;
}

void WinTransition::execute() {
	cout << "Executing Win Transition" << endl;
}

WinTransition& WinTransition::operator= (const WinTransition& winTransition) {
	transitionName = winTransition.transitionName;
	nextState = winTransition.nextState;
	return *this;
}

PlayTransition::PlayTransition() : Transition(Enums::play) {
	nextState = new State(Enums::start);
}

PlayTransition::PlayTransition(const PlayTransition& playTransition) : Transition(playTransition.transitionName) {
	nextState = playTransition.nextState;
}

void PlayTransition::execute() {
	cout << "Executing Play Transition" << endl;
}

PlayTransition& PlayTransition::operator= (const PlayTransition& playTransition) {
	transitionName = playTransition.transitionName;
	nextState = playTransition.nextState;
	return *this;
}

EndTransition::EndTransition() : Transition(Enums::end) {
	nextState = new State(Enums::quit);
}

EndTransition::EndTransition(const EndTransition& endTransition) : Transition(endTransition.transitionName) {
	nextState = endTransition.nextState;
}

void EndTransition::execute() {
	cout << "Executing End Transition" << endl;
}

EndTransition& EndTransition::operator= (const EndTransition& endTransition) {
	transitionName = endTransition.transitionName;
	nextState = endTransition.nextState;
	return *this;
}

GameEngine::GameEngine() {
	currentState = new State(Enums::start);
	updateAvailableTransitions();
}

GameEngine::GameEngine(const GameEngine& engine) {
	currentState = engine.currentState;
	availableTransitions = engine.availableTransitions;
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

std::ostream& operator<< (std::ostream& os, const GameEngine& engine) {
	os << "-------------------------------------------------------------" << endl;
	os << "You are currently in the " << *engine.currentState << " state." << endl;
	os << "-------------------------------------------------------------" << endl;

	vector<Transition*> availableTransitions = engine.availableTransitions;	
	int index = 0;

	for(Transition* transition : availableTransitions) {
		os << "[" << index << "]"<< " " << *transition << endl;
		index++;
	}
	
	os << "-------------------------------------------------------------" << endl;

	return os;
}

GameEngine& GameEngine::operator= (const GameEngine& engine) {
	currentState = engine.currentState;
	availableTransitions = engine.availableTransitions;
	return *this;
}

GameEngine::~GameEngine() {
	delete currentState;
	currentState = NULL;
	availableTransitions.clear();
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
