/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "./Headers/GameEngine.h"

//Default constructor for the State class
State::State() {
	stateName = Enums::start;
};

//Constructor that takes the name of the state to construct for the State class
State::State(Enums::states name) {
	stateName = name;
}

//Copy constructor for the state class
State::State(const State& state){
	stateName = state.stateName;
}

//Accessor for the state name
Enums::states State::getStateName() {
	return stateName;
}

//Stream operator overload for the State class
std::ostream& operator<<(std::ostream& os, const State& state) {
	os << Enums::statesEnumToString(state.stateName);
	return os;
}

//Assignment operator override for the State class
State& State::operator= (const State& state) {
	stateName = state.stateName;
	return *this;
}

//Destructor for the State class
State::~State() {  

}

//Default constructor for the Transition class
Transition::Transition() {
	transitionName = Enums::end;
}

//Constructor that takes a transition name as a parameter
Transition::Transition(Enums::transitions name) {
	transitionName = name;
}

//Copy constructor for the Transition class
Transition::Transition(const Transition& transition) {
	transitionName = transition.transitionName;
	nextState = transition.nextState;
}

//Accessor for the transition name
Enums::transitions Transition::getTransitionName() {
	return transitionName;
}

//Accessor for the next state of a transition
State* Transition::getNextState() {
	return nextState;
}

//Stream operator overload for the Transition class
std::ostream& operator<<(std::ostream& os, const Transition& transition) {
	os << Enums::transitionsEnumToString(transition.transitionName);
	return os;
}

//Assignment operator override for the Transition class
Transition& Transition::operator= (const Transition& transition) {
	transitionName = transition.transitionName;
	nextState = transition.nextState;
	return *this;
}

//Destructor for the Transition class
Transition::~Transition() {
	delete nextState;
	nextState = NULL;
}

//Default constructor for the LoadMapTransition class
LoadMapTransition::LoadMapTransition() : Transition(Enums::loadMap) {
	nextState = new State(Enums::mapLoaded);
}

//Copy constructor for the LoadMapTransition class
LoadMapTransition::LoadMapTransition(const LoadMapTransition& loadMapTransition) : Transition(loadMapTransition) {
	nextState = loadMapTransition.nextState;
}

//Method that executes the LoadMapTransition
void LoadMapTransition::execute() {
	cout << "Executing Load Map Transition" << endl;
}

//Assignment operator override for the LoadMapTransition
LoadMapTransition& LoadMapTransition::operator= (const LoadMapTransition& loadMapTransition) {
	transitionName = loadMapTransition.transitionName;
	nextState = loadMapTransition.nextState;
	return *this;
}

//Default constructor for the ValidateMapTransition class
ValidateMapTransition::ValidateMapTransition() : Transition(Enums::validateMap) {
	nextState = new State(Enums::mapValidated);
}

//Copy constructor for the ValidateMapTransition class
ValidateMapTransition::ValidateMapTransition(const ValidateMapTransition& validateMapTransition) : Transition(validateMapTransition) {
	nextState = validateMapTransition.nextState;
}

//Method that executes the ValidateMapTransition
void ValidateMapTransition::execute() {
	cout << "Executing Validate Map Transiton" << endl;
}

//Assignment operator override for the ValidateMapTransition class
ValidateMapTransition& ValidateMapTransition::operator= (const ValidateMapTransition& validateMapTransition) {
	transitionName = validateMapTransition.transitionName;
	nextState = validateMapTransition.nextState;
	return *this;
}

//Default constructor for the AddPlayerTransition class
AddPlayerTransition::AddPlayerTransition() : Transition(Enums::addPlayer) {
	nextState = new State(Enums::playersAdded);
}

//Copy constructor for the AddPlayerTransition class
AddPlayerTransition::AddPlayerTransition(const AddPlayerTransition& addPlayerTransition) : Transition(addPlayerTransition) {
	nextState = addPlayerTransition.nextState;
}

//Method that executes the AddPlayerTransition 
void AddPlayerTransition::execute() {
	cout << "Executing Add Player Transition" << endl;
}

//Assignment operator override for the AddPlayerTransition class
AddPlayerTransition& AddPlayerTransition::operator= (const AddPlayerTransition& addPlayerTransition) {
	transitionName = addPlayerTransition.transitionName;
	nextState = addPlayerTransition.nextState;
	return *this;
}

//Default constructor for the AssignCountriesTransition class
AssignCountriesTransition::AssignCountriesTransition() : Transition(Enums::assignCountries) {
	nextState = new State(Enums::assignReinforcement);
}

//Copy constructor for the AssignCountriesTransition class
AssignCountriesTransition::AssignCountriesTransition(const AssignCountriesTransition& assignCountriestransition) : Transition(assignCountriestransition) {
	nextState = assignCountriestransition.nextState;
}

//Method that executes the AssignCountriesTransition
void AssignCountriesTransition::execute() {
	cout << "Executing Assign Countries Transition" << endl;
}

//Assignment operator override for the AssignCountriesTransition class
AssignCountriesTransition& AssignCountriesTransition::operator= (const AssignCountriesTransition& assignCountriesTranstion) {
	transitionName = assignCountriesTranstion.transitionName;
	nextState = assignCountriesTranstion.nextState;
	return *this;
}

//Default constructor for the IssueOrderTransition class
IssueOrderTransition::IssueOrderTransition() : Transition(Enums::issueOrder) {
	nextState = new State(Enums::issueOrders);
}

//Copy constructor for the IssueOrderTransition class
IssueOrderTransition::IssueOrderTransition(const IssueOrderTransition& issueOrderTransition) : Transition(issueOrderTransition) {
	nextState = issueOrderTransition.nextState;
}

//Method that executes the IssueOrderTransition
void IssueOrderTransition::execute() {
	cout << "Executing Issue Order Transition" << endl;
}

//Assignment operator override for the IssueOrderTransition class
IssueOrderTransition& IssueOrderTransition::operator= (const IssueOrderTransition& issueOrderTransition) {
	transitionName = issueOrderTransition.transitionName;
	nextState = issueOrderTransition.nextState;
	return *this;
}

//Default constructor for th EndIssueOrdersTransition class
EndIssueOrdersTransition::EndIssueOrdersTransition() : Transition(Enums::endIssueOrders) {
	nextState = new State(Enums::executeOrders);
}

//Copy constructor for the EndIssueOrdersTransition class
EndIssueOrdersTransition::EndIssueOrdersTransition(const EndIssueOrdersTransition& endIssueOrdersTransition) : Transition(endIssueOrdersTransition) {
	nextState = endIssueOrdersTransition.nextState;
}

//Method that executes the EndIssueOrdersTransition
void EndIssueOrdersTransition::execute() {
	cout << "Executing End Issue Orders Transition" << endl;
}

//Assignment operator override for the EndIssueOrdersTransition class
EndIssueOrdersTransition& EndIssueOrdersTransition::operator= (const EndIssueOrdersTransition& endIssueOrdersTransition) {
	transitionName = endIssueOrdersTransition.transitionName;
	nextState = endIssueOrdersTransition.nextState;
	return *this;
}

//Default constructor for the ExecOrderTransition class
ExecOrderTransition::ExecOrderTransition() : Transition(Enums::execOrder) {
	nextState = new State(Enums::executeOrders);
}

//Copy constructor for the ExecOrderTransition class
ExecOrderTransition::ExecOrderTransition(const ExecOrderTransition& execOrderTransition) : Transition(execOrderTransition) {
	nextState = execOrderTransition.nextState;
}

//Method that executes the ExecOrderTransition
void ExecOrderTransition::execute() {
	cout << "Executing Exec Order Transition" << endl;
}

//Assignment operator override for the ExecOrderTransition class
ExecOrderTransition& ExecOrderTransition::operator= (const ExecOrderTransition& execOrderTransition) {
	transitionName = execOrderTransition.transitionName;
	nextState = execOrderTransition.nextState;
	return *this;
}

//Default constructor for the EndExecOrdersTransition class
EndExecOrdersTransition::EndExecOrdersTransition() : Transition(Enums::endExecuteOrders) {
	nextState = new State(Enums::assignReinforcement);
}

//Copy constructor for the EndExecOrdersTransition class
EndExecOrdersTransition::EndExecOrdersTransition(const EndExecOrdersTransition& endExecuteOrdersTransition) : Transition(endExecuteOrdersTransition) {
	nextState = endExecuteOrdersTransition.nextState;
}

//Method that executes the EndExecOrdersTransition
void EndExecOrdersTransition::execute() {
	cout << "Executing End Exec Orders Transition" << endl;
}

//Assignment operator override for the EndExecOrdersTransition class
EndExecOrdersTransition& EndExecOrdersTransition::operator= (const EndExecOrdersTransition& endExecuteOrdersTransition) {
	transitionName = endExecuteOrdersTransition.transitionName;
	nextState = endExecuteOrdersTransition.nextState;
	return *this;
}

//Default constructor for the WinTransition class
WinTransition::WinTransition() : Transition(Enums::winTransition) {
	nextState = new State(Enums::winState);
}

//Copy constructor for the WinTransition class
WinTransition::WinTransition(const WinTransition& winTransition) : Transition(winTransition) {
	nextState = winTransition.nextState;
}

//Method that executes the WinTransition
void WinTransition::execute() {
	cout << "Executing Win Transition" << endl;
}

//Assignment operator override for the WinTransition class
WinTransition& WinTransition::operator= (const WinTransition& winTransition) {
	transitionName = winTransition.transitionName;
	nextState = winTransition.nextState;
	return *this;
}

//Default constructor for the PlayTransition class
PlayTransition::PlayTransition() : Transition(Enums::play) {
	nextState = new State(Enums::start);
}

//Copy constructor for the PlayTransition class
PlayTransition::PlayTransition(const PlayTransition& playTransition) : Transition(playTransition) {
	nextState = playTransition.nextState;
}

//Method that executes the PlayTransition
void PlayTransition::execute() {
	cout << "Executing Play Transition" << endl;
}

//Assignment operator override for the PlayTransition class
PlayTransition& PlayTransition::operator= (const PlayTransition& playTransition) {
	transitionName = playTransition.transitionName;
	nextState = playTransition.nextState;
	return *this;
}

//Default constructor for the EndTransition class
EndTransition::EndTransition() : Transition(Enums::end) {
	nextState = new State(Enums::quit);
}

//Copy constructor for the EndTransition class
EndTransition::EndTransition(const EndTransition& endTransition) : Transition(endTransition) {
	nextState = endTransition.nextState;
}

//Method that executes the EndTransition
void EndTransition::execute() {
	cout << "Executing End Transition" << endl;
}

//Assignment operator override for the EndTransition class
EndTransition& EndTransition::operator= (const EndTransition& endTransition) {
	transitionName = endTransition.transitionName;
	nextState = endTransition.nextState;
	return *this;
}

//Default constructor for the GameEngine class
GameEngine::GameEngine() {
	currentState = new State(Enums::start);
	updateAvailableTransitions();
}

//Copy constructor for the GameEngine class
GameEngine::GameEngine(const GameEngine& engine) {
	currentState = engine.currentState;
	availableTransitions = engine.availableTransitions;
}

//Method that updates the available transitions of the game engine, given the current state
void GameEngine::updateAvailableTransitions() {
	switch(currentState -> getStateName()) {
		case Enums::start: {
			for (auto p : availableTransitions) {
				delete p;
				p = NULL;
			}
			availableTransitions.clear();
			availableTransitions.push_back(new LoadMapTransition());
			break;
		}
		case Enums::mapLoaded: {
			for (auto p : availableTransitions) {
				delete p;
				p = NULL;
			}
			availableTransitions.clear();
			availableTransitions.push_back(new LoadMapTransition());
			availableTransitions.push_back(new ValidateMapTransition());
			break;
		}
		case Enums::mapValidated: {
			for (auto p : availableTransitions) {
				delete p;
				p = NULL;
			}
			availableTransitions.clear();
			availableTransitions.push_back(new AddPlayerTransition());
			break;
		}
		case Enums::playersAdded: {
			for (auto p : availableTransitions) {
				delete p;
				p = NULL;
			}
			availableTransitions.clear();
			availableTransitions.push_back(new AddPlayerTransition());
			availableTransitions.push_back(new AssignCountriesTransition());
			break;
		}
		case Enums::assignReinforcement: {
			for (auto p : availableTransitions) {
				delete p;
				p = NULL;
			}
			availableTransitions.clear();
			availableTransitions.push_back(new IssueOrderTransition());
			break;
		}
		case Enums::issueOrders: {
			for (auto p : availableTransitions) {
				delete p;
				p = NULL;
			}
			availableTransitions.clear();
			availableTransitions.push_back(new IssueOrderTransition());
			availableTransitions.push_back(new EndIssueOrdersTransition());
			break;
		}
		case Enums::executeOrders: {
			for (auto p : availableTransitions) {
				delete p;
				p = NULL;
			}
			availableTransitions.clear();
			availableTransitions.push_back(new ExecOrderTransition());
			availableTransitions.push_back(new EndExecOrdersTransition());
			availableTransitions.push_back(new WinTransition());
			break;
		}
		case Enums::winState: {
			for (auto p : availableTransitions) {
				delete p;
				p = NULL;
			}
			availableTransitions.clear();
			availableTransitions.push_back(new PlayTransition());
			availableTransitions.push_back(new EndTransition());
			break;
		}
		case Enums::quit: {
			for (auto p : availableTransitions) {
				delete p;
				p = NULL;
			}
			availableTransitions.clear();
		}
	}
}

//Accessor for the current state of the game engine
State* GameEngine::getCurrentState() {
	return currentState;
}

//Accessor for the currently available transitions
vector<Transition*> GameEngine::getAvailableTransitions() {
	return availableTransitions;
}

//Method that tells the game engine to execute a transitioin that is given as a parameter
void GameEngine::execute(Transition* transition) {
	transition -> execute();
	delete currentState;
	currentState = new State(*(transition -> getNextState()));
	notify(this);
	updateAvailableTransitions();
}

//Method that is used to start up the game and process commands from the user(S)
void GameEngine::startupPhase() {
	do {
		vector<Transition*> availableTransitions = getAvailableTransitions();
		int selected;
		cin >> selected;
		
		while(selected < 0 || selected >= availableTransitions.size()){
			cout << "Please select one of the available actions:" << endl;
			cin >> selected;
		}

		execute(availableTransitions[selected]);
	} while(Enums::statesEnumToString(getCurrentState() -> getStateName()) != "Quit");
///////////////////////////////////////////////////////////////////////////////////////////////	
	cout << "Welcome to COMP 345 Warzone! Here are the currently available commands:" << endl;
	
	for(Transition* transition : availableTransitions) {
		cout << *transition << endl;
	}

	cout << "Please enter one of the available commands"
}

//ILoggable function
string GameEngine::stringToLog()
{
	return "GameEngine new state: "+to_string(currentState->getStateName())+'\n';
}

//Strem operator overload for the GameEngine class
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

//Assignment operator override for the GameEngine class
GameEngine& GameEngine::operator= (const GameEngine& engine) {
	currentState = engine.currentState;
	availableTransitions = engine.availableTransitions;
	return *this;
}

//Destructor for the GameEngine class
GameEngine::~GameEngine() {
	delete currentState;
	currentState = NULL;

	for (auto p : availableTransitions) {
		delete p;
		p = NULL;
	}
}

//Method that converts a states enum to a string
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

//Method that converts a transitions enum to a string
std::string Enums::transitionsEnumToString(Enums::transitions value) {
	switch(value) {
		case Enums::loadMap: {
			return "loadmap <filename>";
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
