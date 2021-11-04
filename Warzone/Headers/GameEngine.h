#pragma once

#include <string> 
#include <vector>
#include "LoggingObserver.h"
#include "CommandProcessing.h"

namespace Enums{
	enum states { start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, winState, quit };
	enum transitions { loadMap, validateMap, addPlayer, assignCountries, issueOrder, endIssueOrders, endExecuteOrders, execOrder, winTransition, play, end };
	std::string statesEnumToString(states value);
	std::string transitionsEnumToString(transitions value);
}

class Command;

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
	virtual void execute(string args) = 0;
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
	void execute(string args);
	LoadMapTransition& operator= (const LoadMapTransition& loadMapTransition);
};

class ValidateMapTransition: public Transition{
public:
	ValidateMapTransition();
	ValidateMapTransition(const ValidateMapTransition& validateMapTransition);
	void execute(string args);
	ValidateMapTransition& operator= (const ValidateMapTransition& validateMapTransition);
};

class AddPlayerTransition: public Transition{
public:
	AddPlayerTransition();
	AddPlayerTransition(const AddPlayerTransition& addPlayerTransition);
	void execute(string args);
	AddPlayerTransition& operator= (const AddPlayerTransition& addPlayerTransition);
};

class AssignCountriesTransition: public Transition{
public:
	AssignCountriesTransition();
	AssignCountriesTransition(const AssignCountriesTransition& assignCountriesTransition);
	void execute(string args);
	AssignCountriesTransition& operator= (const AssignCountriesTransition& assignCountriesTransition);
};

class IssueOrderTransition: public Transition{
public:
	IssueOrderTransition();
	IssueOrderTransition(const IssueOrderTransition& issueOrderTransition);
	void execute(string args);
	IssueOrderTransition& operator= (const IssueOrderTransition& issueOrderTransition);
};

class EndIssueOrdersTransition: public Transition{
public:
	EndIssueOrdersTransition();
	EndIssueOrdersTransition(const EndIssueOrdersTransition& endIssueOrdersTransition);
	void execute(string args);
	EndIssueOrdersTransition& operator= (const EndIssueOrdersTransition& endIssueOrdersTransition);
};

class ExecOrderTransition: public Transition{
public:
	ExecOrderTransition();
	ExecOrderTransition(const ExecOrderTransition& execOrderTransition);
	void execute(string args);
	ExecOrderTransition& operator= (const ExecOrderTransition& execOrderTransition);
};

class EndExecOrdersTransition: public Transition{
public:
	EndExecOrdersTransition();
	EndExecOrdersTransition(const EndExecOrdersTransition& endExecuteOrdersTransition);
	void execute(string args);
	EndExecOrdersTransition& operator= (const EndExecOrdersTransition& endExecuteOrdersTransition);
};


class WinTransition: public Transition{
public:
	WinTransition();
	WinTransition(const WinTransition& winTransition);
	void execute(string args);
	WinTransition& operator= (const WinTransition& winTransition);
};

class PlayTransition: public Transition{
public:
	PlayTransition();
	PlayTransition(const PlayTransition& playTransition);
	void execute(string args);
	PlayTransition& operator= (const PlayTransition& playTransition);
};

class EndTransition: public Transition{
public:
	EndTransition();
	EndTransition(const EndTransition& endTransition);
	void execute(string args);
	EndTransition& operator= (const EndTransition& endTransition);
};

class GameEngine:ILoggable,SubJect {
public: 
	GameEngine();
	GameEngine(const GameEngine& engine);
	State* getCurrentState();
	std::vector<Transition*> getAvailableTransitions();
	void execute(Transition* transition, string args);
	void startupPhase();
	void execute(Command* command);
	string stringToLog();
	friend std::ostream& operator<< (std::ostream& os, const GameEngine& engine);
	GameEngine& operator= (const GameEngine& engine);
	~GameEngine();
private:
	State* currentState;
	std::vector<Transition*> availableTransitions;
	void updateAvailableTransitions();
};
