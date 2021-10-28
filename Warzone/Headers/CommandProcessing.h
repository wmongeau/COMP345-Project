#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "GameEngine.h"
#include "LoggingObserver.h"

using namespace std;

enum CommandType
{
	loadMap, validateMap, addPlayer, gameStart, replay, quit, error
};

ostream& operator<<(ostream& out, CommandType commandType);

class Command:ILoggable, SubJect {
public:
	Command();
	Command(CommandType commandType, string command, string effect);
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

class CommandProcessing:ILoggable, SubJect {
public:
	CommandProcessing();
	~CommandProcessing();
	CommandProcessing(const CommandProcessing& c);
	CommandProcessing& operator=(const CommandProcessing& c);
	friend ostream& operator<<(ostream& out, const CommandProcessing& c);
	void getCommand(State* currentState);
	vector<Command*> getCommandList();
	string stringToLog();
private:
	Command* readCommand();
	void saveCommand(Command* command);
	bool validate(State* currentState, Command* command);
	vector<Command*> commandList;
};

class FileLineReader {
public:
	FileLineReader();
	~FileLineReader();
	FileLineReader(const FileLineReader& c);
	FileLineReader& operator=(const FileLineReader& c);
	friend ostream& operator<<(ostream& os, const FileLineReader& c);
	string readLineFromFile();
};

class FileCommandProcessorAdaptor : public CommandProcessing {
public:
	FileCommandProcessorAdaptor();
	~FileCommandProcessorAdaptor();
	FileCommandProcessorAdaptor(const FileCommandProcessorAdaptor& c);
	FileCommandProcessorAdaptor& operator=(const FileCommandProcessorAdaptor& c);
	friend ostream& operator<<(ostream& os, const FileCommandProcessorAdaptor& c);
private:
	void readCommand();
	FileLineReader* flr;
};