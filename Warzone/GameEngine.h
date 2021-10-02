#pragma once

#include <string> 
#include <vector>

namespace Enums{
	enum states { start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, winState, quit };
	enum transitions { loadMap, validateMap, addPlayer, assignCountries, issueOrder, endIssueOrders, endExecuteOrders, execOrder, winTransition, play, end };
	std::string statesEnumToString(states value);
	std::string transitionsEnumToString(transitions value);
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
	void execute();
};

class ValidateMapTransition: public Transition{
public:
	ValidateMapTransition();
	void execute();
};

class AddPlayerTransition: public Transition{
public:
	AddPlayerTransition();
	void execute();
};

class AssignCountriesTransition: public Transition{
public:
	AssignCountriesTransition();
	void execute();
};

class IssueOrderTransition: public Transition{
public:
	IssueOrderTransition();
	void execute();
};

class EndIssueOrdersTransition: public Transition{
public:
	EndIssueOrdersTransition();
	void execute();
};

class ExecOrderTransition: public Transition{
public:
	ExecOrderTransition();
	void execute();
};

class EndExecOrdersTransition: public Transition{
	EndExecOrdersTransition();
	void execute();
};


class WinTransition: public Transition{
	WinTransition();
	void execute();
};

class PlayTransition: public Transition{
	PlayTransition();
	void execute();
};

class EndTransition: public Transition{
	EndTransition();
	void execute();
};

class GameEngine {
public: GameEngine();
	State* getCurrentState();
	std::vector<Transition*> getAvailableTransitions();
	void execute(Transition* transition);
private:
	State* currentState;
	std::vector<Transition*> availableTransitions;
	void updateAvailableTransitions();
};
