#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "GameEngine.h"
#include "LoggingObserver.h"

using namespace std;

class State;

enum CommandType
{
	loadMap, validateMap, addPlayer, tournament, gameStart, replay, quit, error
};

ostream& operator<<(ostream& out, CommandType commandType);

class Command:ILoggable, Subject {
public:
	Command();
	Command(CommandType commandType, string command);
	~Command();
	Command(const Command& c);
	Command& operator=(const Command& c);
	friend ostream& operator<<(ostream& out, const Command& c);
	void saveEffect(string effect);
	string getEffect();
	string getCommand();
	CommandType getCommandType();
	string stringToLog();
private:
	CommandType commandType;
	string command;
	string effect;
};

class CommandProcessor:ILoggable, Subject {
public:
	CommandProcessor();
	~CommandProcessor();
	CommandProcessor(const CommandProcessor& c);
	CommandProcessor& operator=(const CommandProcessor& c);
	friend ostream& operator<<(ostream& out, const CommandProcessor& c);
	Command* getCommand(State* currentState);
	vector<Command*> getCommandList();
	string stringToLog();
private:
	virtual Command* readCommand();
	void saveCommand(Command* command);
	bool validate(State* currentState, Command* command);
	vector<Command*> commandList;
};

class FileLineReader {
public:
	FileLineReader(string fileDirectory);
	FileLineReader();
	~FileLineReader();
	FileLineReader(const FileLineReader& c);
	FileLineReader& operator=(const FileLineReader& c);
	friend ostream& operator<<(ostream& os, const FileLineReader& c);
	string readLineFromFile();
private:
	int currentLine;
	string fileDirectory;
};

class FileCommandProcessorAdaptor: public CommandProcessor {
public:
	FileCommandProcessorAdaptor(string fileDirectory);
	FileCommandProcessorAdaptor();
	~FileCommandProcessorAdaptor();
	FileCommandProcessorAdaptor(const FileCommandProcessorAdaptor& c);
	FileCommandProcessorAdaptor& operator=(const FileCommandProcessorAdaptor& c);
	friend ostream& operator<<(ostream& os, const FileCommandProcessorAdaptor& c);
private:
	Command* readCommand();
	FileLineReader* flr;
};

string extractPlayerName(Command* command);
string extractMapFile(Command* command);
std::vector<string> getTournamentMaps(std::vector<string> args);
std::vector<string> getTournamentPlayers(std::vector<string> args);
int getTournamentNumberOfGames(std::vector<string> args);
int getTournamentMaxNumberOfTurns(std::vector<string> args);