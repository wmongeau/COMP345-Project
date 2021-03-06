/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;
#include "./Headers/GameEngine.h"
#include "./Headers/CommandProcessing.h"
#include "./Headers/MapDriver.h"

//Default constructor for the State class
State::State()
{
	stateName = Enums::start;
};

//Constructor that takes the name of the state to construct for the State class
State::State(Enums::states name)
{
	stateName = name;
}

//Copy constructor for the state class
State::State(const State& state)
{
	stateName = state.stateName;
}

//Accessor for the state name
Enums::states State::getStateName()
{
	return stateName;
}

//Stream operator overload for the State class
std::ostream& operator<<(std::ostream& os, const State& state)
{
	os << Enums::statesEnumToString(state.stateName);
	return os;
}

//Assignment operator override for the State class
State& State::operator=(const State& state)
{
	stateName = state.stateName;
	return *this;
}

//Destructor for the State class
State::~State()
{
}

//Default constructor for the Transition class
Transition::Transition()
{
	transitionName = Enums::end;
}

//Constructor that takes a transition name as a parameter
Transition::Transition(Enums::transitions name)
{
	transitionName = name;
}

//Copy constructor for the Transition class
Transition::Transition(const Transition& transition)
{
	transitionName = transition.transitionName;
	nextState = transition.nextState;
}

//Accessor for the transition name
Enums::transitions Transition::getTransitionName()
{
	return transitionName;
}

//Accessor for the next state of a transition
State* Transition::getNextState()
{
	return nextState;
}

//Stream operator overload for the Transition class
std::ostream& operator<<(std::ostream& os, const Transition& transition)
{
	os << Enums::transitionsEnumToString(transition.transitionName);
	return os;
}

//Assignment operator override for the Transition class
Transition& Transition::operator=(const Transition& transition)
{
	transitionName = transition.transitionName;
	nextState = transition.nextState;
	return *this;
}

//Destructor for the Transition class
Transition::~Transition()
{
	delete nextState;
	nextState = NULL;
}

//Default constructor for the LoadMapTransition class
LoadMapTransition::LoadMapTransition() : Transition(Enums::loadMap)
{
	nextState = new State(Enums::mapLoaded);
}

//Copy constructor for the LoadMapTransition class
LoadMapTransition::LoadMapTransition(const LoadMapTransition& loadMapTransition) : Transition(loadMapTransition)
{
	nextState = loadMapTransition.nextState;
}

//Method that executes the LoadMapTransition
void LoadMapTransition::execute(string args, GameEngine* engine)
{
	cout << "Executing Load Map Transition" << endl;
	engine->setMap(MapLoader::loadMap(args));
	cout << "Loaded Map " << args << endl;
}

//Assignment operator override for the LoadMapTransition
LoadMapTransition& LoadMapTransition::operator=(const LoadMapTransition& loadMapTransition)
{
	transitionName = loadMapTransition.transitionName;
	nextState = loadMapTransition.nextState;
	return *this;
}

//Default constructor for the ValidateMapTransition class
ValidateMapTransition::ValidateMapTransition() : Transition(Enums::validateMap)
{
	nextState = new State(Enums::mapValidated);
}

//Copy constructor for the ValidateMapTransition class
ValidateMapTransition::ValidateMapTransition(const ValidateMapTransition& validateMapTransition) : Transition(validateMapTransition)
{
	nextState = validateMapTransition.nextState;
}

//Method that executes the ValidateMapTransition
void ValidateMapTransition::execute(string args, GameEngine* engine)
{
	cout << "Executing Validate Map Transition" << endl;
	bool valid = engine->getMap()->validate();
	cout << "Map is valid: " << valid << endl;
}

//Assignment operator override for the ValidateMapTransition class
ValidateMapTransition& ValidateMapTransition::operator=(const ValidateMapTransition& validateMapTransition)
{
	transitionName = validateMapTransition.transitionName;
	nextState = validateMapTransition.nextState;
	return *this;
}

//Default constructor for the AddPlayerTransition class
AddPlayerTransition::AddPlayerTransition() : Transition(Enums::addPlayer)
{
	nextState = new State(Enums::playersAdded);
}

//Copy constructor for the AddPlayerTransition class
AddPlayerTransition::AddPlayerTransition(const AddPlayerTransition& addPlayerTransition) : Transition(addPlayerTransition)
{
	nextState = addPlayerTransition.nextState;
}

//Method that executes the AddPlayerTransition
void AddPlayerTransition::execute(string args, GameEngine* engine)
{
	cout << "Executing Add Player Transition" << endl;
	PlayerType type;
	string name = args + "(Player " + to_string(engine->getPlayers().size()) + ")";
	if (args == "Aggressive") {
		type = PlayerType::aggressive;
	}
	else if (args == "Benevolent") {
		type = PlayerType::benevolent;
	}
	else if (args == "Neutral") {
		type = PlayerType::neutral;
	}
	else if (args == "Cheater") {
		type = PlayerType::cheater;
	}
	else {
		type = PlayerType::human;
	}
	engine->addPlayer(new Player(name, type));
	cout << "Added " + name << endl;
}

//Assignment operator override for the AddPlayerTransition class
AddPlayerTransition& AddPlayerTransition::operator=(const AddPlayerTransition& addPlayerTransition)
{
	transitionName = addPlayerTransition.transitionName;
	nextState = addPlayerTransition.nextState;
	return *this;
}

//Default constructor for the AssignCountriesTransition class
AssignCountriesTransition::AssignCountriesTransition() : Transition(Enums::assignCountries)
{
	nextState = new State(Enums::assignReinforcement);
}

//Copy constructor for the AssignCountriesTransition class
AssignCountriesTransition::AssignCountriesTransition(const AssignCountriesTransition& assignCountriestransition) : Transition(assignCountriestransition)
{
	nextState = assignCountriestransition.nextState;
}

//Method that executes the AssignCountriesTransition
void AssignCountriesTransition::execute(string args, GameEngine* engine)
{
	srand(unsigned(time(0)));
	cout << "Executing Assign Countries Transition" << endl;

	engine->setStarting(false);

	vector<Player*> enginePlayers = engine->getPlayers();
	random_shuffle(enginePlayers.begin(), enginePlayers.end());
	engine->setPlayers(enginePlayers);

	cout << "Order of play: " << endl;
	for (Player* p : engine->getPlayers())
	{
		p->setEnemies(enginePlayers);
		cout << p->getPlayerName() << endl;
	}

	vector<Territory*> availableTerritories = vector<Territory*>(engine->getMap()->Territories);
	random_shuffle(availableTerritories.begin(), availableTerritories.end());
	int playerIndex = 0;

	for (Territory* t : availableTerritories)
	{
		engine->getPlayers().at(playerIndex)->addOwnedTerritory(t);
		if (playerIndex == engine->getPlayers().size() - 1)
		{
			playerIndex = 0;
		}
		else
		{
			playerIndex++;
		}
	}

	cout << "Territories have been assigned to players randomly" << endl;

	for (Player* p : engine->getPlayers())
	{
		p->setReinforcementPool(50);
		cout << p->getPlayerName() << " now has 50 armies in their reinforcement pool." << endl;
	}

	for (Player* p : engine->getPlayers())
	{
		p->deck = engine->getDeck();
		p->addCardToHand(engine->getDeck()->draw());
		p->addCardToHand(engine->getDeck()->draw());
		p->setIsTurnFinish(false);
		cout << p->getPlayerName() << " has drawn two cards." << endl;
	}

	cout << "Startup phase is done!" << endl;
}

//Assignment operator override for the AssignCountriesTransition class
AssignCountriesTransition& AssignCountriesTransition::operator=(const AssignCountriesTransition& assignCountriesTranstion)
{
	transitionName = assignCountriesTranstion.transitionName;
	nextState = assignCountriesTranstion.nextState;
	return *this;
}

//Default constructor for the IssueOrderTransition class
IssueOrderTransition::IssueOrderTransition() : Transition(Enums::issueOrder)
{
	nextState = new State(Enums::issueOrders);
}

//Copy constructor for the IssueOrderTransition class
IssueOrderTransition::IssueOrderTransition(const IssueOrderTransition& issueOrderTransition) : Transition(issueOrderTransition)
{
	nextState = issueOrderTransition.nextState;
}

//Method that executes the IssueOrderTransition
void IssueOrderTransition::execute(string args, GameEngine* engine)
{
	cout << "Executing Issue Order Transition" << endl;
	engine->issueOrderPhase();

}

//Assignment operator override for the IssueOrderTransition class
IssueOrderTransition& IssueOrderTransition::operator=(const IssueOrderTransition& issueOrderTransition)
{
	transitionName = issueOrderTransition.transitionName;
	nextState = issueOrderTransition.nextState;
	return *this;
}

//Default constructor for th EndIssueOrdersTransition class
EndIssueOrdersTransition::EndIssueOrdersTransition() : Transition(Enums::endIssueOrders)
{
	nextState = new State(Enums::executeOrders);
}

//Copy constructor for the EndIssueOrdersTransition class
EndIssueOrdersTransition::EndIssueOrdersTransition(const EndIssueOrdersTransition& endIssueOrdersTransition) : Transition(endIssueOrdersTransition)
{
	nextState = endIssueOrdersTransition.nextState;
}

//Method that executes the EndIssueOrdersTransition
void EndIssueOrdersTransition::execute(string args, GameEngine* engine)
{
	cout << "Executing End Issue Orders Transition" << endl;
}

//Assignment operator override for the EndIssueOrdersTransition class
EndIssueOrdersTransition& EndIssueOrdersTransition::operator=(const EndIssueOrdersTransition& endIssueOrdersTransition)
{
	transitionName = endIssueOrdersTransition.transitionName;
	nextState = endIssueOrdersTransition.nextState;
	return *this;
}

//Default constructor for the ExecOrderTransition class
ExecOrderTransition::ExecOrderTransition() : Transition(Enums::execOrder)
{
	nextState = new State(Enums::executeOrders);
}

//Copy constructor for the ExecOrderTransition class
ExecOrderTransition::ExecOrderTransition(const ExecOrderTransition& execOrderTransition) : Transition(execOrderTransition)
{
	nextState = execOrderTransition.nextState;
}

//Method that executes the ExecOrderTransition
void ExecOrderTransition::execute(string args, GameEngine* engine)
{

	cout << "Executing Exec Order Transition" << endl;
	engine->executeOrderPhase();
}

//Assignment operator override for the ExecOrderTransition class
ExecOrderTransition& ExecOrderTransition::operator=(const ExecOrderTransition& execOrderTransition)
{
	transitionName = execOrderTransition.transitionName;
	nextState = execOrderTransition.nextState;
	return *this;
}

//Default constructor for the EndExecOrdersTransition class
EndExecOrdersTransition::EndExecOrdersTransition() : Transition(Enums::endExecuteOrders)
{
	nextState = new State(Enums::assignReinforcement);
}

//Copy constructor for the EndExecOrdersTransition class
EndExecOrdersTransition::EndExecOrdersTransition(const EndExecOrdersTransition& endExecuteOrdersTransition) : Transition(endExecuteOrdersTransition)
{
	nextState = endExecuteOrdersTransition.nextState;
}

//Method that executes the EndExecOrdersTransition
void EndExecOrdersTransition::execute(string args, GameEngine* engine)
{
	cout << "Executing End Exec Orders Transition" << endl;
	engine->reinforcementPhase();
}

//Assignment operator override for the EndExecOrdersTransition class
EndExecOrdersTransition& EndExecOrdersTransition::operator=(const EndExecOrdersTransition& endExecuteOrdersTransition)
{
	transitionName = endExecuteOrdersTransition.transitionName;
	nextState = endExecuteOrdersTransition.nextState;
	return *this;
}

//Default constructor for the WinTransition class
WinTransition::WinTransition() : Transition(Enums::winTransition)
{
	nextState = new State(Enums::winState);
}

//Copy constructor for the WinTransition class
WinTransition::WinTransition(const WinTransition& winTransition) : Transition(winTransition)
{
	nextState = winTransition.nextState;
}

//Method that executes the WinTransition
void WinTransition::execute(string args, GameEngine* engine)
{
	cout << "Executing Win Transition" << endl;
}

//Assignment operator override for the WinTransition class
WinTransition& WinTransition::operator=(const WinTransition& winTransition)
{
	transitionName = winTransition.transitionName;
	nextState = winTransition.nextState;
	return *this;
}

//Default constructor for the PlayTransition class
PlayTransition::PlayTransition() : Transition(Enums::play)
{
	nextState = new State(Enums::start);
}

//Copy constructor for the PlayTransition class
PlayTransition::PlayTransition(const PlayTransition& playTransition) : Transition(playTransition)
{
	nextState = playTransition.nextState;
}

//Method that executes the PlayTransition
void PlayTransition::execute(string args, GameEngine* engine)
{
	cout << "Executing Play Transition" << endl;
}

//Assignment operator override for the PlayTransition class
PlayTransition& PlayTransition::operator=(const PlayTransition& playTransition)
{
	transitionName = playTransition.transitionName;
	nextState = playTransition.nextState;
	return *this;
}

//Default constructor for the EndTransition class
EndTransition::EndTransition() : Transition(Enums::end)
{
	nextState = new State(Enums::quit);
}

//Copy constructor for the EndTransition class
EndTransition::EndTransition(const EndTransition& endTransition) : Transition(endTransition)
{
	nextState = endTransition.nextState;
}

//Method that executes the EndTransition
void EndTransition::execute(string args, GameEngine* engine)
{
	cout << "Executing End Transition" << endl;
}

//Assignment operator override for the EndTransition class
EndTransition& EndTransition::operator=(const EndTransition& endTransition)
{
	transitionName = endTransition.transitionName;
	nextState = endTransition.nextState;
	return *this;
}

//Default constructor for the TournamentTransition class
TournamentTransition::TournamentTransition() : Transition(Enums::tournament)
{
	nextState = new State(Enums::quit);
}

//Copy constructor for the TournamentTransition class
TournamentTransition::TournamentTransition(const TournamentTransition& tournamentTransition) : Transition(tournamentTransition)
{
	nextState = tournamentTransition.nextState;
}

//Method that executes the TournamentTransition 
void TournamentTransition::execute(string args, GameEngine* engine)
{
	cout << "Starting Tournament" << endl;
	for (string map : engine->getTournamentMaps()) {
		for (int i = 0; i < engine->getTournamentNumberOfGames(); i++) {
			cout << "Starting game for map: " << map << endl;
			engine->execute(new LoadMapTransition(), map);
			engine->execute(new ValidateMapTransition(), "");
			for (string player : engine->getTournamentPlayers()) {
				engine->execute(new AddPlayerTransition(), player);
			}
			engine->execute(new AssignCountriesTransition(), "");
			std::vector<string> game;
			game.push_back(map);
			engine->addGame(game);
			engine->mainGameLoop();
		}
	}

	storeTournamentResults(engine);
	notify(this);
}

// This method sotres the results of a tournament in a string in the transition that can then be used for logging
void TournamentTransition::storeTournamentResults(GameEngine* engine)
{
	string tournamentResultsString = "";
	tournamentResultsString += "Tournament Mode:\n" ;
	tournamentResultsString += "M: ";

	for (string map : engine->getTournamentMaps()) {
		tournamentResultsString += map;
		tournamentResultsString += ", ";
	}

	tournamentResultsString += "\n";

	tournamentResultsString += "P: ";

	for (string player : engine->getTournamentPlayers()) {
		tournamentResultsString += player;
		tournamentResultsString += ", ";
	}

	tournamentResultsString += "\n";

	tournamentResultsString += "G: ";
	tournamentResultsString += std::to_string(engine->getTournamentNumberOfGames());
	tournamentResultsString += "\n";

	tournamentResultsString += "D: ";
	tournamentResultsString += std::to_string(engine->getTournamentMaxNumberOfTurns());
	tournamentResultsString += "\n";

	tournamentResultsString += "Results: \n";

	tournamentResultsString += "           ";

	for (int i = 1; i <= engine->getTournamentNumberOfGames(); i++) {
		tournamentResultsString += "Game ";
		tournamentResultsString += std::to_string(i);
		tournamentResultsString += "    ";
	}

	tournamentResultsString += "\n";

	int counter = 0;

	for (vector<string> game : engine->getGames()) {
		if (counter != 0 && counter % engine->getTournamentNumberOfGames() == 0) {
			tournamentResultsString += "\n";
		}

		if (counter % engine->getTournamentNumberOfGames() == 0) {
			tournamentResultsString += game.front();
			tournamentResultsString += " ";
		}
		tournamentResultsString += game.back();
		tournamentResultsString += "      ";

		counter++;
	}

	tournamentResultsString += "\n";
	cout << tournamentResultsString;
	tournamentResults = tournamentResultsString;
}

// This method logs the results of a tournament
string TournamentTransition::stringToLog() {
	return tournamentResults;
}

//Assignment operator override for the TournamentTransition class
TournamentTransition& TournamentTransition::operator=(const TournamentTransition& tournamentTransition)
{
	transitionName = tournamentTransition.transitionName;
	nextState = tournamentTransition.nextState;
	return *this;
}

//Default constructor for the GameEngine class
GameEngine::GameEngine()
{
	currentState = new State(Enums::start);
	updateAvailableTransitions();
	map = NULL;
	processor = new CommandProcessor();
	players = vector<Player*>();
	starting = true;
	deck = new Deck();
	winner = false;
	tournamentMaps = vector<string>();
	tournamentPlayers = vector<string>();
	tournamentTurns = 0;
	tournamentGames = 0;
	games = vector<vector<string>>();
	tournamentMode = false;
}

//Constructor for the GameEngine class that takes in a command processor
GameEngine::GameEngine(CommandProcessor* passedProcessor) {
	currentState = new State(Enums::start);
	updateAvailableTransitions();
	map = NULL;
	processor = passedProcessor;
	players = vector<Player*>();
	starting = true;
	deck = new Deck();
	winner = false;
	tournamentMaps = vector<string>();
	tournamentPlayers = vector<string>();
	tournamentTurns = 0;
	tournamentGames = 0;
	games = vector<vector<string>>();
	tournamentMode = false;
}

//Copy constructor for the GameEngine class
GameEngine::GameEngine(const GameEngine& engine)
{
	currentState = engine.currentState;
	availableTransitions = engine.availableTransitions;
	processor = engine.processor;
	map = engine.map;
	players = engine.players;
	starting = engine.starting;
	deck = engine.deck;
	winner = engine.winner;
	tournamentMaps = engine.tournamentMaps;
	tournamentPlayers = engine.tournamentPlayers;
	tournamentGames = engine.tournamentGames;
	tournamentTurns = engine.tournamentTurns;
	games = engine.games;
	tournamentMode = engine.tournamentMode;
}

//Method that updates the available transitions of the game engine, given the current state
void GameEngine::updateAvailableTransitions()
{
	switch (currentState->getStateName())
	{
	case Enums::start:
	{
		for (auto p : availableTransitions)
		{
			delete p;
			p = NULL;
		}
		availableTransitions.clear();
		availableTransitions.push_back(new LoadMapTransition());
		availableTransitions.push_back(new TournamentTransition());
		break;
	}
	case Enums::mapLoaded:
	{
		for (auto p : availableTransitions)
		{
			delete p;
			p = NULL;
		}
		availableTransitions.clear();
		availableTransitions.push_back(new LoadMapTransition());
		availableTransitions.push_back(new ValidateMapTransition());
		break;
	}
	case Enums::mapValidated:
	{
		for (auto p : availableTransitions)
		{
			delete p;
			p = NULL;
		}
		availableTransitions.clear();
		availableTransitions.push_back(new AddPlayerTransition());
		break;
	}
	case Enums::playersAdded:
	{
		for (auto p : availableTransitions)
		{
			delete p;
			p = NULL;
		}
		availableTransitions.clear();
		if (players.size() <= 5)
		{
			availableTransitions.push_back(new AddPlayerTransition());
		}
		if (players.size() >= 2)
		{
			availableTransitions.push_back(new AssignCountriesTransition());
		}
		break;
	}
	case Enums::assignReinforcement:
	{
		for (auto p : availableTransitions)
		{
			delete p;
			p = NULL;
		}
		availableTransitions.clear();
		availableTransitions.push_back(new IssueOrderTransition());
		break;
	}
	case Enums::issueOrders:
	{
		for (auto p : availableTransitions)
		{
			delete p;
			p = NULL;
		}
		availableTransitions.clear();
		availableTransitions.push_back(new IssueOrderTransition());
		availableTransitions.push_back(new EndIssueOrdersTransition());
		break;
	}
	case Enums::executeOrders:
	{
		for (auto p : availableTransitions)
		{
			delete p;
			p = NULL;
		}
		availableTransitions.clear();
		availableTransitions.push_back(new ExecOrderTransition());
		availableTransitions.push_back(new EndExecOrdersTransition());
		availableTransitions.push_back(new WinTransition());
		break;
	}
	case Enums::winState:
	{
		for (auto p : availableTransitions)
		{
			delete p;
			p = NULL;
		}
		availableTransitions.clear();
		availableTransitions.push_back(new PlayTransition());
		availableTransitions.push_back(new EndTransition());
		break;
	}
	case Enums::quit:
	{
		for (auto p : availableTransitions)
		{
			delete p;
			p = NULL;
		}
		availableTransitions.clear();
	}
	}
}

//Accessor for the current state of the game engine
State* GameEngine::getCurrentState()
{
	return currentState;
}

//Accessor for the currently available transitions
vector<Transition*> GameEngine::getAvailableTransitions()
{
	return availableTransitions;
}

//Method that tells the game engine to execute a transition that is given as a parameter
void GameEngine::execute(Transition* transition, string args)
{
	transition->execute(args, this);
	delete currentState;
	currentState = new State(*(transition->getNextState()));
	notify(this);
	delete transition;
	transition = NULL;
	updateAvailableTransitions();
}

//Method that is used to start up the game and process commands from the user(S)
void GameEngine::startupPhase()
{
	cout << "Welcome to COMP 345 Warzone!" << endl;
	cout << "-------------------------------------------------------------" << endl;

	while (starting)
	{
		cout << "These are the currently available commands: " << endl;
		for (Transition* transition : availableTransitions)
		{
			cout << *transition << endl;
		}
		cout << "-------------------------------------------------------------" << endl;

		cout << "Please enter one of the available commands" << endl;
		processor->getCommand(getCurrentState());
		Command* command = processor->getCommandList().back();
		cout << "-------------------------------------------------------------" << endl;
		execute(command);
		cout << "-------------------------------------------------------------" << endl;
	}
}

//Method that takes in a command and executes the appropriate command
void GameEngine::execute(Command* command)
{
	switch (command->getCommandType())
	{
		case CommandType::loadMap:
		{
			string args = splitString(command->getCommand()).back();
			execute(new LoadMapTransition(), args);
			break;
		}
		case CommandType::validateMap:
		{
			string args = "";
			execute(new ValidateMapTransition(), args);
			break;
		}
		case CommandType::addPlayer:
		{
			string args = splitString(command->getCommand()).back();
			execute(new AddPlayerTransition(), args);
			break;
		}
		case CommandType::gameStart:
		{
			string args = "";
			execute(new AssignCountriesTransition(), args);
			break;
		}
		case CommandType::tournament:
		{
			vector<string> args = splitString(command->getCommand());
			tournamentMaps = getTournamentMaps(args);
			tournamentPlayers = getTournamentPlayers(args);
			tournamentGames = getTournamentNumberOfGames(args);
			tournamentTurns = getTournamentMaxNumberOfTurns(args);
			tournamentMode = true;
			starting = false;
			execute(new TournamentTransition(), "");
			break;
		}
		case CommandType::replay:
		{
			string args = "";
			execute(new PlayTransition(), args);
			break;
		}
		case CommandType::quit:
		{
			string args = "";
			execute(new EndTransition(), args);
			break;
		}
		case CommandType::error:
		{
			cout << "The command you entered was invalid." << endl;
		}
	}
}

//This method extracts the maps from a tournament command
vector<string> GameEngine::getTournamentMaps(vector<string> args)
{
	bool map = false;
	vector<string> maps;

	for (string str : args) {
		if (str == "-M") {
			map = true;
		}
		else if (str == "-P" || str == "-G" || str == "-D") {
			map = false;
		}
		else {
			if (map) {
				maps.push_back(str);
			}
		}
	}

	return maps;
}

//This method extracts the player strategies from a tournament command
vector<string> GameEngine::getTournamentPlayers(vector<string> args)
{
	bool player = false;
	vector<string> players;

	for (string str : args) {
		if (str == "-P") {
			player = true;
		}
		else if (str == "-M" || str == "-G" || str == "-D") {
			player = false;
		}
		else {
			if (player) {
				players.push_back(str);
			}
		}
	}

	return players;
}

//This method extracts the number of games to be played per map from a tournament command
int GameEngine::getTournamentNumberOfGames(vector<string> args)
{
	bool game = false;
	int numberOfGames = 0;

	for (string str : args) {
		if (str == "-G") {
			game = true;
		}
		else if (str == "-M" || str == "-P" || str == "-D") {
			game = false;
		}
		else {
			if (game) {
				std::string::size_type sz;

				numberOfGames = std::stoi(str, &sz);
			}
		}
	}

	return numberOfGames;
}

//This method extracts the maximum number of turns to be played per game from a tournament command
int GameEngine::getTournamentMaxNumberOfTurns(vector<string> args)
{
	bool turn = false;
	int numberOfTurns = 0;

	for (string str : args) {
		if (str == "-D") {
			turn = true;
		}
		else if (str == "-M" || str == "-P" || str == "-G") {
			turn = false;
		}
		else {
			if (turn) {
				std::string::size_type sz;

				numberOfTurns = std::stoi(str, &sz);
			}
		}
	}

	return numberOfTurns;
}

// This method returns the maps to be used in the tournament
vector<string> GameEngine::getTournamentMaps()
{
	return tournamentMaps;
}

// This method returns the player strategies to be used in the tournament
vector<string> GameEngine::getTournamentPlayers()
{
	return tournamentPlayers;
}

//This method returns the number of games to be played per map in the tournament
int GameEngine::getTournamentNumberOfGames()
{
	return tournamentGames;
}

//This methid returns the maximum number of turns to be played per game in a tournament
int GameEngine::getTournamentMaxNumberOfTurns()
{
	return tournamentTurns;
}

//This method returns whether or not the GameEngine is currently running a tournament
bool GameEngine::getTournamentMode() 
{
	return tournamentMode;
}

//ILoggable function
string GameEngine::stringToLog()
{
	return "GameEngine new state: " + statesEnumToString(getCurrentState()->getStateName()) + '\n';
}

//Getter for the map of the engine
Map* GameEngine::getMap()
{
	return map;
}

//Setter for the map of the engine
void GameEngine::setMap(Map* loadedMap)
{
	map = loadedMap;
}

//Getter for the list of players in the game
vector<Player*> GameEngine::getPlayers()
{
	return players;
}

//Method to add a player to the game
void GameEngine::addPlayer(Player* player)
{
	players.push_back(player);
}

//Setter for the list of players in the game
void GameEngine::setPlayers(vector<Player*> newPlayers) {
	players = newPlayers;
}

//Getter for the boolean indicating whether or not we are in the startup phase
bool GameEngine::getStarting()
{
	return starting;
}

//Setter for the boolean indicating if we are in the startup phase
void GameEngine::setStarting(bool isStarting)
{
	starting = isStarting;
}

//Getter for the game's card deck
Deck* GameEngine::getDeck()
{
	return deck;
}

//stream operator overload for the GameEngine class
std::ostream& operator<<(std::ostream& os, const GameEngine& engine)
{
	os << "-------------------------------------------------------------" << endl;
	os << "You are currently in the " << *engine.currentState << " state." << endl;
	os << "-------------------------------------------------------------" << endl;

	vector<Transition*> availableTransitions = engine.availableTransitions;
	int index = 0;

	for (Transition* transition : availableTransitions)
	{
		os << "[" << index << "]"
			<< " " << *transition << endl;
		index++;
	}

	os << "-------------------------------------------------------------" << endl;

	return os;
}

//Assignment operator override for the GameEngine class
GameEngine& GameEngine::operator=(const GameEngine& engine)
{
	currentState = engine.currentState;
	availableTransitions = engine.availableTransitions;
	map = engine.map;
	processor = engine.processor;
	players = engine.players;
	starting = engine.starting;
	deck = engine.deck;
	winner = engine.winner;
	tournamentMaps = engine.tournamentMaps;
	tournamentPlayers = engine.tournamentPlayers;
	tournamentGames = engine.tournamentGames;
	tournamentTurns = engine.tournamentTurns;
	games = engine.games;
	tournamentMode = engine.tournamentMode;
	return *this;
}

//Destructor for the GameEngine class
GameEngine::~GameEngine()
{
	delete currentState;
	currentState = NULL;

	for (auto p : availableTransitions)
	{
		delete p;
		p = NULL;
	}

	for (auto p : players)
	{
		delete p;
		p = NULL;
	}

	delete map;
	map = NULL;

	delete processor;
	processor = NULL;

	delete deck;
	deck = NULL;
}

//Method that converts a states enum to a string
std::string Enums::statesEnumToString(Enums::states value)
{
	switch (value)
	{
	case Enums::start:
	{
		return "Start";
	}
	case Enums::mapLoaded:
	{
		return "Map Loaded";
	}
	case Enums::mapValidated:
	{
		return "Map Validated";
	}
	case Enums::playersAdded:
	{
		return "Players Added";
	}
	case Enums::assignReinforcement:
	{
		return "Assign Reinforcement";
	}
	case Enums::issueOrders:
	{
		return "Issue Orders";
	}
	case Enums::executeOrders:
	{
		return "Execute Orders";
	}
	case Enums::winState:
	{
		return "Win";
	}
	case Enums::quit:
	{
		return "Quit";
	}
	}

	return "Error";
}

//Method that converts a transitions enum to a string
std::string Enums::transitionsEnumToString(Enums::transitions value)
{
	switch (value)
	{
	case Enums::loadMap:
	{
		return "loadmap <filename>";
	}
	case Enums::validateMap:
	{
		return "validatemap";
	}
	case Enums::addPlayer:
	{
		return "addplayer <playername>";
	}
	case Enums::assignCountries:
	{
		return "gamestart";
	}
	case Enums::issueOrder:
	{
		return "Issue an Order";
	}
	case Enums::endIssueOrders:
	{
		return "End Issuing Orders";
	}
	case Enums::execOrder:
	{
		return "Execute Order";
	}
	case Enums::endExecuteOrders:
	{
		return "End Executing Orders";
	}
	case Enums::winTransition:
	{
		return "Win Transition";
	}
	case Enums::play:
	{
		return "replay";
	}
	case Enums::end:
	{
		return "quit";
	}
	case Enums::tournament:
	{
		return "tournament -M <spaceseperatedlistofmaps> -P <spaceseperatedlistofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>";
	}
	}

	return "Error";
}
// main game loop method.
// Iterates until only one of the players owns all the territories in the map, at which point a winner is announced and the game ends. 
// The main game loop also checks for any player that does not control at least one territory; if so, the player is removed from the game.

void GameEngine::mainGameLoop()
{
	bool firstTurn = true;
	int currentTurn = 1;

	while (currentState->getStateName() != Enums::winState)
	{
		// iterates through the players list, if a player no longer has a territory (they lose), they get removed
		for (int i = 0; i < players.size(); i++)
		{
			if (players[i]->getOwnedTerritories().empty())
			{
				players.erase(players.begin() + i);
			}
			else {
				players[i]->toDefend();
				players[i]->toAttack();
			}
		}
		if (!firstTurn)
		{
			execute(new EndExecOrdersTransition, "");
		}
		firstTurn = false;
		execute(new IssueOrderTransition, "");
		execute(new EndIssueOrdersTransition, "");
		execute(new ExecOrderTransition, "");
		currentTurn++;


		if (tournamentMode && currentTurn > tournamentTurns) {
			games.back().push_back("Draw");
			execute(new WinTransition(), "");
		}

		//checks if a player won
		for (int i = 0; i < players.size(); i++)
		{
			if (players[i]->getOwnedTerritories().size() == map->Territories.size())
			{
				if (tournamentMode) {
					games.back().push_back(players[i]->getPlayerName());
				}
				cout << "-------------------------------------------------------------" << endl;
				cout << players[i]->getPlayerName() << " is the winner" << endl;
				winner = true;
				execute(new WinTransition, "");
			}
		}
	}

	if (tournamentMode) {
		execute(new PlayTransition(), "");
		return;
	}

	cout << "These are the currently available commands: " << endl;
	for (Transition* transition : availableTransitions)
	{
		cout << *transition << endl;
	}
	cout << "-------------------------------------------------------------" << endl;

	cout << "Please enter one of the available commands" << endl;
	cin.ignore();
	processor->getCommand(new State(Enums::winState));
	Command* command = processor->getCommandList().back();
	cout << "-------------------------------------------------------------" << endl;
	execute(command);
	cout << "-------------------------------------------------------------" << endl;
}

// Returns information about games played during a tournament
std::vector<std::vector<string>> GameEngine::getGames() {
	return games;
}

// Stores information about a given game ina tournament
void GameEngine::addGame(std::vector<string> game) {
	games.push_back(game);
}

// method to check if the continent is owned.
bool GameEngine::checkIfContinentOwned(Player* player, Continent* continent)
{
	Player* currentPlayer;
	for (Territory* territory : continent->getTerritories())
	{
		currentPlayer = territory->getPlayer();
		if (territory->getPlayer() == NULL || currentPlayer->getPlayerName() != player->getPlayerName())
		{
			return false;
		}
	}
	return true;
}
 
// Reinforcement phase method is called in a round-robin fashion.
// Players are given a number of armies that depends on the number of territories they own, (# of territories owned divided by 3, rounded down).
// It assigned at least 3 armies to each player to deploy. 
// If the player owns a continent it includes continent bonus
void GameEngine::reinforcementPhase() {

	cout << "Executing End Exec Orders Transition" << endl;
	int numTerritories = 0;
	const int MIN_ARMIES = 3;
	int numArmies;

	cout << "Reinforcement Phase" << endl;
	cout << "-------------------------------------------------------------" << endl;

	// check if a player owns all the territories of an entire continent
	for (int i = 0; i < players.size(); i++)
	{
		numTerritories = players[i]->getOwnedTerritories().size();
		numArmies = floor(numTerritories / 3);
		if (numArmies < 3)
		{
			numArmies = MIN_ARMIES;
		}
		for (Continent* cont : map->Continents)
		{
			//If the player owns all the territories of an entire continent, the player is given a number of armies corresponding to the continent???s control bonus value.
			if (checkIfContinentOwned(players[i], cont))
				numArmies = numArmies + cont->getArmyValue();
		}
		players[i]->setReinforcementPool(numArmies);
		cout << players[i]->getPlayerName() << " reinforcement pool has " << players[i]->getReinforcementPool() << " armies." << endl;
		cout << players[i]->getPlayerName() << " currently has " << numTerritories << " territories. \n"
			<< endl;
	}
}
// Execute order phase is called in round robin fashion
void GameEngine::executeOrderPhase() {
	bool isAllExecuted = false;
	int counter = 0;
	int numberOwnedTerritory;
	vector<bool> playerHasDrawn = vector<bool>();
	for (int i = 0; i < players.size(); i++)
		playerHasDrawn.push_back(false);

	cout << "Orders Execution Phase" << endl;
	cout << "-------------------------------------------------------------" << endl;
	vector<Order*> orderList;
	// iterates to check if all orders have been executed
	if (!isAllExecuted) {
		for (int i = 0; i < players.size(); i++) {
			if (players[i]->getOrders()->getOrdersVector().size() != 0) {
				numberOwnedTerritory = players[i]->getOwnedTerritories().size();
				players[i]->getOrders()->getOrdersVector()[0]->execute();
				cout << *players[i]->getOrders()->getOrdersVector()[0];
				players[i]->getOrders()->remove(0);
				if (players[i]->getOwnedTerritories().size() > numberOwnedTerritory && !playerHasDrawn[i]) {
					if (deck->getDeckOfCards().size() != 0) {
						players[i]->addCardToHand(deck->draw());
						playerHasDrawn[i] = true;
					}
				}
			}
			else
				counter++;
		}
		if (counter == players.size())
		{
			isAllExecuted = true;
		}
		else {
			counter = 0;
			execute(new ExecOrderTransition, "");
		}
	}
}

// Method for issueOrderPhase()
// Orders are to be validated only when they are executed in the orders execution phase.
void GameEngine::issueOrderPhase() {
	bool allFinish = false;
	int counter = 0;
	cout << "Issue Order Phase" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if (!allFinish) {
		for (int i = 0; i < players.size(); i++) {
			if (!players[i]->getIsTurnFinish())
				players[i]->issueOrder();
			else
				counter++;
		}
		if (counter == players.size())
		{
			allFinish = true;
			for (int i = 0; i < players.size(); i++) {
				players[i]->setIsTurnFinish(false);
			}
		}
		else {
			counter = 0;
			execute(new IssueOrderTransition(), "");
		}
	}
}
