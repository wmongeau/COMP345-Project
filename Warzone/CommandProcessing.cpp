#include "Headers/CommandProcessing.h"
#include <regex>
#include <fstream>

using namespace std;

ostream& operator<<(ostream& out, CommandType commandType)
{
	switch (commandType) {
	case CommandType::addPlayer:
		out << "Add Player";
		break;
	case CommandType::gameStart:
		out << "Game Start";
		break;
	case CommandType::loadMap:
		out << "Load Map";
		break;
	case CommandType::quit:
		out << "Quit";
		break;
	case CommandType::replay:
		out << "Replay";
		break;
	case CommandType::validateMap:
		out << "Validate Map";
		break;
	}

	return out;
}

ostream& operator<<(ostream& out, const Command& c)
{
	out << "This command is of type: " << c.commandType << " and contains the following command: " << c.command << endl;

	return out;
}

ostream& operator<<(ostream& out, const CommandProcessor& c)
{
	out << "The command processor contains the following commands: " << endl;
	for (auto c : c.commandList) {
		out << c << endl;
	}

	return out;
}

ostream& operator<<(ostream& os, const FileLineReader& c)
{
	os << "FileLineReader" << endl;

	return os;
}

ostream& operator<<(ostream& os, const FileCommandProcessorAdaptor& c)
{
	os << "FileCommandProcessorAdapter" << endl;

	return os;
}

string extractPlayerName(Command* command)
{
	if (command->getCommandType() != CommandType::addPlayer) return "";

	string commandString = command->getCommand();
	string delimiter = " ";

	return commandString.substr(1, commandString.find(delimiter));
}

string extractMapFile(Command* command)
{
	if (command->getCommandType() != CommandType::loadMap) return "";

	string commandString = command->getCommand();
	string delimiter = " ";

	return commandString.substr(1, commandString.find(delimiter));
}

CommandProcessor::CommandProcessor()
{
	this->commandList = vector<Command*>();
}

CommandProcessor::~CommandProcessor()
{
	for(auto c : commandList) {
		delete c;
		c = NULL;
	}
}

CommandProcessor::CommandProcessor(const CommandProcessor& c)
{
	this->commandList = c.commandList;
}

CommandProcessor& CommandProcessor::operator=(const CommandProcessor& c)
{
	this->commandList = c.commandList;

	return *this;
}

void CommandProcessor::getCommand(State* currentState)
{
	Command* command = readCommand();

	if (validate(currentState, command)) 
		saveCommand(command);
}

vector<Command*> CommandProcessor::getCommandList()
{
	return this->commandList;
}

string CommandProcessing::stringToLog()
{
	return "Command: "+commandList[commandList.size()-1]->getCommand()+'\n';
}

Command* CommandProcessing::readCommand()
{
	string commandString;
	getline(cin, commandString);
	regex loadmapRegex("loadmap .+");
	regex addplayerRegex("addplayer [a-zA-Z]+");

	if (commandString == "validatemap")
		return new Command(CommandType::validateMap, commandString);
	else if (commandString == "gamestart")
		return new Command(CommandType::gameStart, commandString);
	else if (commandString == "replay")
		return new Command(CommandType::replay, commandString);
	else if (commandString == "quit")
		return new Command(CommandType::quit, commandString);
	else if (regex_match(commandString, loadmapRegex)) 
		return new Command(CommandType::loadMap, commandString);
	else if (regex_match(commandString, addplayerRegex)) 
		return new Command(CommandType::addPlayer, commandString);

	return new Command(CommandType::error, commandString);
}

void CommandProcessor::saveCommand(Command* command)
{
	commandList.push_back(command);
	notify(this);
}

bool CommandProcessor::validate(State* currentState, Command* command)
{
	if (command->getCommandType() == CommandType::error) {
		command->saveEffect("effect: The command: " + command->getCommand() + " was invalid, therefore nothing happened.");
		return false;
	}
	else if (command->getCommandType() == CommandType::addPlayer && (currentState->getStateName() == Enums::states::mapValidated || currentState->getStateName() == Enums::states::playersAdded)) {
		command->saveEffect("effect: The player: " + extractPlayerName(command) + " is being added to the game.");
		return true;
	}
	else if (command->getCommandType() == CommandType::gameStart && currentState->getStateName() == Enums::states::playersAdded) {
		command->saveEffect("effects: The game is starting.");
		return true;
	}
	else if (command->getCommandType() == CommandType::replay && currentState->getStateName() == Enums::states::winState) {
		command->saveEffect("effect: The game is being replayed.");
		return true;
	}
	else if (command->getCommandType() == CommandType::quit && currentState->getStateName() == Enums::states::winState) {
		command->saveEffect("effect: Quitting out of the game.");
		return true;
	}
	else if (command->getCommandType() == CommandType::validateMap && currentState->getStateName() == Enums::states::mapLoaded) {
		command->saveEffect("effect: The map: " + extractMapFile(command) + " is being validated");
		return true;
	}
	else if (command->getCommandType() == CommandType::loadMap && (currentState->getStateName() == Enums::states::start || currentState->getStateName() == Enums::states::mapLoaded)) {
		command->saveEffect("effect: The game is starting.");
		return true;
	}

	return false;
}

Command::Command()
{
	this->commandType = CommandType::error;
	this->command = "";
	this->effect = "";
}

Command::Command(CommandType commandType, string command)
{
	this->commandType = commandType;
	this->command = command;
}

Command::~Command()
{
}

Command::Command(const Command& c)
{
	this->command = c.command;
	this->commandType = c.commandType;
	this->effect = c.effect;
}

Command& Command::operator=(const Command& c)
{
	this->command = c.command;
	this->commandType = c.commandType;
	this->effect = c.effect;

	return *this;
}

CommandType Command::getCommandType()
{
	return commandType;
}

string Command::stringToLog()
{
	return "Command's Effect: "+effect+'\n';
}

void Command::saveEffect(string effect)
{
	this->effect = effect;
	notify(this);
}

string Command::getEffect()
{
	return this->effect;
}

string Command::getCommand()
{
	return this->command;
}

FileLineReader::FileLineReader(string fileDirectory)
{
	this->currentLine = 1;
	this->fileDirectory = fileDirectory;
}

FileLineReader::~FileLineReader()
{
}

FileLineReader::FileLineReader(const FileLineReader& c)
{
	this->currentLine = c.currentLine;
	this->fileDirectory = c.fileDirectory;
}

FileLineReader& FileLineReader::operator=(const FileLineReader& c)
{
	return *this;
}

string FileLineReader::readLineFromFile()
{
	ifstream file(fileDirectory);
	string line;

	for (int i = 1; i <= currentLine; i++) {
		getline(file, line);
	}

	currentLine++;
	file.close();

	return line;
}

FileCommandProcessorAdaptor::FileCommandProcessorAdaptor(string fileDirectory)
{
	this->flr = new FileLineReader(fileDirectory);
}

FileCommandProcessorAdaptor::~FileCommandProcessorAdaptor()
{
	delete flr;
	flr = NULL;
}

FileCommandProcessorAdaptor::FileCommandProcessorAdaptor(const FileCommandProcessorAdaptor& c)
{
	this->flr = c.flr;
}

FileCommandProcessorAdaptor& FileCommandProcessorAdaptor::operator=(const FileCommandProcessorAdaptor& c)
{
	this->flr = c.flr;

	return *this;
}

Command* FileCommandProcessorAdaptor::readCommand()
{
	string commandString = flr->readLineFromFile();
	regex loadmapRegex("loadmap .+");
	regex addplayerRegex("addplayer [a-zA-Z]+");

	if (commandString == "validatemap")
		return new Command(CommandType::validateMap, commandString);
	else if (commandString == "gamestart")
		return new Command(CommandType::gameStart, commandString);
	else if (commandString == "replay")
		return new Command(CommandType::replay, commandString);
	else if (commandString == "quit")
		return new Command(CommandType::quit, commandString);
	else if (regex_match(commandString, loadmapRegex))
		return new Command(CommandType::loadMap, commandString);
	else if (regex_match(commandString, addplayerRegex))
		return new Command(CommandType::addPlayer, commandString);

	return new Command(CommandType::error, commandString);
}
