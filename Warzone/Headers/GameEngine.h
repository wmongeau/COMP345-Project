#pragma once

#include <string> 
#include <vector>
#include "LoggingObserver.h"

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
	State(const State& state);
	Enums::states getStateName();
	friend std::ostream& operator<<(std::ostream& os, const State& state);
	State& operator= (const State& state);
	~State();
private:
	Enums::states stateName;
};

class Transition {
public:
	Transition();
	Transition(Enums::transitions name);
	Transition(const Transition& transition);
	Enums::transitions getTransitionName();
	State* getNextState();
	virtual void execute() = 0;
	friend std::ostream& operator<<(std::ostream& os, const Transition& transition);
	Transition& operator= (const Transition& transition);
	~Transition();
protected:
	Enums::transitions transitionName;
	State* nextState;
};

class LoadMapTransition: public Transition{
public:
	LoadMapTransition();
	LoadMapTransition(const LoadMapTransition& loadMapTransition);
	void execute();
	LoadMapTransition& operator= (const LoadMapTransition& loadMapTransition);
};

class ValidateMapTransition: public Transition{
public:
	ValidateMapTransition();
	ValidateMapTransition(const ValidateMapTransition& validateMapTransition);
	void execute();
	ValidateMapTransition& operator= (const ValidateMapTransition& validateMapTransition);
};

class AddPlayerTransition: public Transition{
public:
	AddPlayerTransition();
	AddPlayerTransition(const AddPlayerTransition& addPlayerTransition);
	void execute();
	AddPlayerTransition& operator= (const AddPlayerTransition& addPlayerTransition);
};

class AssignCountriesTransition: public Transition{
public:
	AssignCountriesTransition();
	AssignCountriesTransition(const AssignCountriesTransition& assignCountriesTransition);
	void execute();
	AssignCountriesTransition& operator= (const AssignCountriesTransition& assignCountriesTransition);
};

class IssueOrderTransition: public Transition{
public:
	IssueOrderTransition();
	IssueOrderTransition(const IssueOrderTransition& issueOrderTransition);
	void execute();
	IssueOrderTransition& operator= (const IssueOrderTransition& issueOrderTransition);
};

class EndIssueOrdersTransition: public Transition{
public:
	EndIssueOrdersTransition();
	EndIssueOrdersTransition(const EndIssueOrdersTransition& endIssueOrdersTransition);
	void execute();
	EndIssueOrdersTransition& operator= (const EndIssueOrdersTransition& endIssueOrdersTransition);
};

class ExecOrderTransition: public Transition{
public:
	ExecOrderTransition();
	ExecOrderTransition(const ExecOrderTransition& execOrderTransition);
	void execute();
	ExecOrderTransition& operator= (const ExecOrderTransition& execOrderTransition);
};

class EndExecOrdersTransition: public Transition{
public:
	EndExecOrdersTransition();
	EndExecOrdersTransition(const EndExecOrdersTransition& endExecuteOrdersTransition);
	void execute();
	EndExecOrdersTransition& operator= (const EndExecOrdersTransition& endExecuteOrdersTransition);
};


class WinTransition: public Transition{
public:
	WinTransition();
	WinTransition(const WinTransition& winTransition);
	void execute();
	WinTransition& operator= (const WinTransition& winTransition);
};

class PlayTransition: public Transition{
public:
	PlayTransition();
	PlayTransition(const PlayTransition& playTransition);
	void execute();
	PlayTransition& operator= (const PlayTransition& playTransition);
};

class EndTransition: public Transition{
public:
	EndTransition();
	EndTransition(const EndTransition& endTransition);
	void execute();
	EndTransition& operator= (const EndTransition& endTransition);
};

class GameEngine:ILoggable,SubJect {
public: 
	GameEngine();
	GameEngine(const GameEngine& engine);
	State* getCurrentState();
	std::vector<Transition*> getAvailableTransitions();
	void execute(Transition* transition);
	string stringToLog();
	friend std::ostream& operator<< (std::ostream& os, const GameEngine& engine);
	GameEngine& operator= (const GameEngine& engine);
	~GameEngine();
private:
	State* currentState;
	std::vector<Transition*> availableTransitions;
	void updateAvailableTransitions();
};
