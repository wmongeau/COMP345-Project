#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "GameEngine.h"

using namespace std;

enum CommandType
{
	loadMap, validateMap, addPlayer, gameStart, replay, quit, error
};

ostream& operator<<(ostream& out, CommandType commandType);

class Command {
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
private:
	CommandType commandType;
	string command;
	string effect;
};

class CommandProcessor {
public:
	CommandProcessor();
	~CommandProcessor();
	CommandProcessor(const CommandProcessor& c);
	CommandProcessor& operator=(const CommandProcessor& c);
	friend ostream& operator<<(ostream& out, const CommandProcessor& c);
	void getCommand(State* currentState);
	vector<Command*> getCommandList();
private:
	virtual Command* readCommand();
	void saveCommand(Command* command);
	bool validate(State* currentState, Command* command);
	vector<Command*> commandList;
};

class FileLineReader {
public:
	FileLineReader(string fileDirectory);
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