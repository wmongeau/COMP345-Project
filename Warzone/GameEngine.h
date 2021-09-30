#pragma once

#include <string> 
#include <vector>

namespace Enums{
	enum states { start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, winState };
	enum transitions { loadMap, validateMap, addPlayer, assignCountries, issueOrder, endIssueOrders, endExecuteOrders, execOrder, winTransition, play, end };
	std::string statesEnumToString(states value);
	std::string transitionsEnumToString();
}

class State {
public:
	State();
	State(Enums::states name);
	Enums::states getStateName();
private:
	Enums::states stateName;
};

class Transition {
public:
	Transition();
	Transition( Enums::transitions name);
	Enums::transitions getTransitionName();
	State* getNextState();
	virtual void execute();
private:
	Enums::transitions transitionName;
protected:
	State* nextState;
};

class LoadMapTransition: public Transition{
public:
	LoadMapTransition();
	LoadMapTransition(Enums::transitions name);
	void execute();
};

class ValidateMapTransition: public Transition{
public:
	void execute();
};

class AddPlayerTransition: public Transition{
public:
	void execute();
};

class AssignCountriesTransition: public Transition{
public:
	void execute();
};

class IssueOrderTransition: public Transition{
public:
	void execute();
};

class EndIssueOrdersTransition: public Transition{
public:
	void execute();
};

class ExecOrderTransition: public Transition{
public:
	void execute();
};

class EndExecOrdersTransition: public Transition{
	void execute();
};


class WinTransition: public Transition{
	void execute();
};

class PlayTransition: public Transition{
	void execute();
};

class EndTransition: public Transition{
	void execute();
};

class GameEngine {
public: GameEngine();
	State getCurrentState();
	std::vector<Transition*> getAvailableTransitions();
	void execute(Transition* transition);
private:
	State* currentState;
	std::vector<Transition*> availableTransitions;
	void updateAvailableTransitions();
};
