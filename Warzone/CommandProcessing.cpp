#include "Headers/CommandProcessing.h"
#include <regex>

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

ostream& operator<<(ostream& out, const CommandProcessing& c)
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

CommandProcessing::CommandProcessing()
{
	this->commandList = vector<Command*>();
}

CommandProcessing::~CommandProcessing()
{
	for(auto c : commandList) {
		delete c;
		c = NULL;
	}
}

CommandProcessing::CommandProcessing(const CommandProcessing& c)
{
	this->commandList = c.commandList;
}

CommandProcessing& CommandProcessing::operator=(const CommandProcessing& c)
{
	this->commandList = c.commandList;

	return *this;
}

void CommandProcessing::getCommand(State* currentState)
{
	Command* command = readCommand();

	if (validate(currentState, command)) 
		saveCommand(command);
}

vector<Command*> CommandProcessing::getCommandList()
{
	return this->commandList;
}

Command* CommandProcessing::readCommand()
{
	string commandString;
	cin >> commandString;
	regex loadmapRegex("loadmap <.+>");
	regex addplayerRegex("addplayer <[a-zA-Z]+>");

	if (commandString == "validatemap")
		return new Command(CommandType::validateMap, commandString, "Validate the map that was loaded");
	else if (commandString == "gamestart")
		return new Command(CommandType::gameStart, commandString, "Start the game");
	else if (commandString == "replay")
		return new Command(CommandType::replay, commandString, "Replay the game");
	else if (commandString == "quit")
		return new Command(CommandType::quit, commandString, "Quit the game");
	else if (regex_match(commandString, loadmapRegex)) 
		return new Command(CommandType::loadMap, commandString, "Load the map");
	else if (regex_match(commandString, addplayerRegex)) 
		return new Command(CommandType::addPlayer, commandString, "Adding player");

	return new Command(CommandType::error, commandString, "There was an error creating a command or the command was invalid");
}

void CommandProcessing::saveCommand(Command* command)
{
	commandList.push_back(command);
}

bool CommandProcessing::validate(State* currentState, Command* command)
{
	if (command->getCommandType() == CommandType::error)
		return false;
	else if (command->getCommandType() == CommandType::addPlayer && (currentState->getStateName() == Enums::states::mapValidated || currentState->getStateName() == Enums::states::playersAdded))
		return true;
	else if (command->getCommandType() == CommandType::gameStart && currentState->getStateName() == Enums::states::playersAdded)
		return true;
	else if (command->getCommandType() == CommandType::replay && currentState->getStateName() == Enums::states::winState)
		return true;
	else if (command->getCommandType() == CommandType::quit && currentState->getStateName() == Enums::states::winState)
		return true;
	else if (command->getCommandType() == CommandType::validateMap && currentState->getStateName() == Enums::states::mapLoaded)
		return true;
	else if (command->getCommandType() == CommandType::loadMap && (currentState->getStateName() == Enums::states::start || currentState->getStateName() == Enums::states::mapLoaded))
		return true;
	else if (command->getCommandType() == CommandType::addPlayer && (currentState->getStateName() == Enums::states::mapValidated || currentState->getStateName() == Enums::states::playersAdded))
		return true;

	return false;
}

Command::Command()
{
	this->commandType = CommandType::error;
	this->command = "";
	this->effect = "";
}

Command::Command(CommandType commandType, string command, string effect)
{
	this->commandType = commandType;
	this->command = command;
	this->effect = effect;
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

void Command::saveEffect(string effect)
{
	this->effect = effect;
}

string Command::getEffect()
{
	return this->effect;
}

string Command::getCommand()
{
	return this->command;
}

FileLineReader::FileLineReader()
{
}

FileLineReader::~FileLineReader()
{
}

FileLineReader::FileLineReader(const FileLineReader& c)
{
}

FileLineReader& FileLineReader::operator=(const FileLineReader& c)
{
	return *this;
}

string FileLineReader::readLineFromFile()
{
	// todo, read the file maybe all at once? or line by line? idk
	return string();
}

FileCommandProcessorAdaptor::FileCommandProcessorAdaptor()
{
	this->flr = new FileLineReader();
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

void FileCommandProcessorAdaptor::readCommand()
{
	// todo use the adapter pattern here idk how though
}
