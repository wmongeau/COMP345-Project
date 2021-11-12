#include "Headers/CommandProcessing.h"
#include <regex>
#include <fstream>

using namespace std;
/// <summary>
/// A stream insertion operator overload for the CommmandType enum.
/// Converts an enum of type CommandType to an ostream with a string representing the CommandType.
/// </summary>
/// <param name="out"></param>
/// <param name="commandType"></param>
/// <returns></returns>
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

/// <summary>
/// A stream insertion operator overload for the Command class.
/// Converts a reference to Command to an ostream displaying the Command's command string as well as it's effect if it exists.
/// </summary>
/// <param name="out"></param>
/// <param name="c"></param>
/// <returns></returns>
ostream& operator<<(ostream& out, const Command& c)
{
	out << c.command << endl;

	if (!empty(c.effect)) {
		out << c.effect << endl;
	}

	return out;
}

/// <summary>
/// A stream insertion operator overload for the CommandProcessor class.
/// Converts a reference to CommandProcessor to an ostream that prints all the commands saved in the processor's command list.
/// </summary>
/// <param name="out"></param>
/// <param name="c"></param>
/// <returns></returns>
ostream& operator<<(ostream& out, const CommandProcessor& c)
{
	out << "The command processor contains the following commands: " << endl;
	for (auto c : c.commandList) {
		out << *c << endl;
	}

	return out;
}

/// <summary>
/// A stream insertion operator overload for the FileLineReader class.
/// Converts a reference to a FileLineReader to an ostream that displays the file that is being read by the FileLineReader.
/// </summary>
/// <param name="os"></param>
/// <param name="c"></param>
/// <returns></returns>
ostream& operator<<(ostream& os, const FileLineReader& c)
{
	os << "FileLineReader is currently reading the following file: " << c.fileDirectory << endl;

	return os;
}

/// <summary>
/// A stream insertion operator overload for the FileCommandProcessorAdaptor class.
/// Converts a reference to a FileCommandProcessorAdaptor to an ostream that displays the contents of the processor's command list.
/// </summary>
/// <param name="out"></param>
/// <param name="c"></param>
/// <returns></returns>
ostream& operator<<(ostream& out, const FileCommandProcessorAdaptor& c)
{
	out << static_cast<CommandProcessor>(c) << endl;

	return out;
}

/// <summary>
/// A free function taking a pointer to a Command as a parameter and extracting the player name from it in the case that it is of type CommandType::addPlayer
/// </summary>
/// <param name="command"></param>
/// <returns>The name of the player (player name) in the command string "addplayer <player name>.</returns>
string extractPlayerName(Command* command)
{
	if (command->getCommandType() != CommandType::addPlayer) return "";

	string commandString = command->getCommand();
	string delimiter = " ";

	return commandString.erase(0, commandString.find(delimiter) + 1);
}

/// <summary>
/// A free function taking a pointer to a Command as a parameter and extracting the map file from it in the case that it is of type CommandType::loadMap
/// </summary>
/// <param name="command"></param>
/// <returns>The name of the map file (map file) in the command string "loadmap <map file>.</returns>
string extractMapFile(Command* command)
{
	if (command->getCommandType() != CommandType::loadMap) return "";

	string commandString = command->getCommand();
	string delimiter = " ";

	return commandString.erase(0, commandString.find(delimiter) + 1);
}

/// <summary>
/// Default constructor to the CommandProcessor class.
/// Sets the processor's commandList member to an empty vector of Command pointers.
/// </summary>
CommandProcessor::CommandProcessor()
{
	this->commandList = vector<Command*>();
}

/// <summary>
/// Destructor for the CommandProcessor class.
/// Destructs all Command's in the commandList class member and set's their references to null.
/// </summary>
CommandProcessor::~CommandProcessor()
{
	for(auto c : commandList) {
		delete c;
		c = NULL;
	}
}

/// <summary>
/// Copy constructor for the CommandProcessor class.
/// </summary>
/// <param name="c"></param>
CommandProcessor::CommandProcessor(const CommandProcessor& c)
{
	this->commandList = c.commandList;
}

/// <summary>
/// Equal operator overload for the class CommandProcessor.
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& c)
{
	this->commandList = c.commandList;

	return *this;
}

/// <summary>
/// Get's the next command string to be executed for the game.
/// </summary>
/// <param name="currentState"></param>
/// <returns>A pointer to the command object that was created as a result of the inputted command</returns>
Command* CommandProcessor::getCommand(State* currentState)
{
	Command* command = readCommand();

	if (validate(currentState, command)) 
		saveCommand(command);

	return command;
}

/// <summary>
/// Getter for the private commandList member of the CommandProcessor class.
/// </summary>
/// <returns>The command list of this instance of the CommandProcessor class as a vector of Command pointers.</returns>
vector<Command*> CommandProcessor::getCommandList()
{
	return this->commandList;
}

/// <summary>
/// Override of the stringToLog() method from the ILogable interface.
/// </summary>
/// <returns>The string to be written into the game log.</returns>
string CommandProcessor::stringToLog()
{
	return "Command: "+commandList[commandList.size()-1]->getCommand()+'\n';
}

/// <summary>
/// Reads a command string from the console and creates a Command object matching the input.
/// </summary>
/// <returns>A pointer to a command object create from the string command received in the console.</returns>
Command* CommandProcessor::readCommand()
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

/// <summary>
/// Saves a command to the CommandProcessor's command list.
/// </summary>
/// <param name="command"></param>
void CommandProcessor::saveCommand(Command* command)
{
	commandList.push_back(command);
	notify(this);
}

/// <summary>
/// Method taking a pointer to the current State of the game as well as a pointer to a Command to verify if the command is valid and if it can 
/// be executed in the current State of the game.
/// </summary>
/// <param name="currentState"></param>
/// <param name="command"></param>
/// <returns>True if the Command is valid, false otherwise.</returns>
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
		command->saveEffect("effect: The game is starting.");
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
		command->saveEffect("effect: The map is being validated");
		return true;
	}
	else if (command->getCommandType() == CommandType::loadMap && (currentState->getStateName() == Enums::states::start || currentState->getStateName() == Enums::states::mapLoaded)) {
		command->saveEffect("effect: The map: " + extractMapFile(command) + " is being loaded.");
		return true;
	}

	command->saveEffect("effect: The command: " + command->getCommand() + " was invalid, therefore nothing happened.");

	return false;
}

/// <summary>
/// Default constructor for the Command class.
/// Set's the commandType to CommandType::error.
/// Set's the command to an empty string.
/// Set's the effect to an empty string.
/// </summary>
Command::Command()
{
	this->commandType = CommandType::error;
	this->command = "";
	this->effect = "";
}


/// <summary>
/// Parameterized constructor for the Command class taking in a CommandType and string to set the commandType and command class members respectively. 
/// </summary>
/// <param name="commandType"></param>
/// <param name="command"></param>
Command::Command(CommandType commandType, string command)
{
	this->commandType = commandType;
	this->command = command;
	this->effect = "";
}

/// <summary>
/// Command desctuctor.
/// </summary>
Command::~Command()
{
}

/// <summary>
/// Copy construcotr for the Command class.
/// </summary>
/// <param name="c"></param>
Command::Command(const Command& c)
{
	this->command = c.command;
	this->commandType = c.commandType;
	this->effect = c.effect;
}

/// <summary>
/// Equal operator overload for the Command class.
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
Command& Command::operator=(const Command& c)
{
	this->command = c.command;
	this->commandType = c.commandType;
	this->effect = c.effect;

	return *this;
}

/// <summary>
/// Getter method for the private class member commandType.
/// </summary>
/// <returns>The commandType of the Command.</returns>
CommandType Command::getCommandType()
{
	return commandType;
}

/// <summary>
/// Override of the stringToLog() method from the ILogable interface.
/// </summary>
/// <returns>The string to be written into the game log.</returns>
string Command::stringToLog()
{
	return "Command's Effect: "+effect+'\n';
}

/// <summary>
/// Save's the effect of a Command in the private class member effect.
/// </summary>
/// <param name="effect"></param>
void Command::saveEffect(string effect)
{
	this->effect = effect;
	notify(this);
}

/// <summary>
/// Getter method for the private class member effect.
/// </summary>
/// <returns>The effect of the Command.</returns>
string Command::getEffect()
{
	return this->effect;
}

/// <summary>
/// Getter method for the private class member command.
/// </summary>
/// <returns>The command string of the Command.</returns>
string Command::getCommand()
{
	return this->command;
}

/// <summary>
/// Parameterized constructor for the FileLineReader that takes a string to the file it will be reading from.
/// </summary>
/// <param name="fileDirectory"></param>
FileLineReader::FileLineReader(string fileName)
{
	string filePath = "../GameCommandFiles/" + fileName;
#ifdef _WIN32
	filePath = "../../../GameCommandFiles/" + fileName;
#endif
	this->currentLine = 1;
	this->fileDirectory = filePath;
}

/// <summary>
/// Destructor for the class FileLineReader.
/// </summary>
FileLineReader::~FileLineReader()
{
}

/// <summary>
/// Copy construcotr for the class FileLineReader.
/// </summary>
/// <param name="c"></param>
FileLineReader::FileLineReader(const FileLineReader& c)
{
	this->currentLine = c.currentLine;
	this->fileDirectory = c.fileDirectory;
}

/// <summary>
/// Equal operator overload for the class FileLineReader.
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
FileLineReader& FileLineReader::operator=(const FileLineReader& c)
{
	this->fileDirectory = c.fileDirectory;
	this->currentLine = c.currentLine;

	return *this;
}

/// <summary>
/// Method used to read the current line from a file containing commands for a game.
/// </summary>
/// <returns>The current line in the file as a string.</returns>
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

/// <summary>
/// Paramaterized construcot for the class FileCommandProcessorAdaptor which takes in the file directory for the file it will read commands from.
/// </summary>
/// <param name="fileDirectory"></param>
FileCommandProcessorAdaptor::FileCommandProcessorAdaptor(string fileDirectory)
{
	this->flr = new FileLineReader(fileDirectory);
}

/// <summary>
/// Destructor for the class FileCommandProcessorAdaptor.
/// Desctructs the processors FileLineReader and sets it's reference to NULL.
/// </summary>
FileCommandProcessorAdaptor::~FileCommandProcessorAdaptor()
{
	delete flr;
	flr = NULL;
}

/// <summary>
/// Copy constructor for the class FileCommandProcessorAdaptor.
/// </summary>
/// <param name="c"></param>
FileCommandProcessorAdaptor::FileCommandProcessorAdaptor(const FileCommandProcessorAdaptor& c)
{
	this->flr = c.flr;
}

/// <summary>
/// Equal operator overload for the class FileCommandProcessorAdaptor.
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
FileCommandProcessorAdaptor& FileCommandProcessorAdaptor::operator=(const FileCommandProcessorAdaptor& c)
{
	this->flr = c.flr;

	return *this;
}

/// <summary>
/// Method to read the command on the current line of the processor FileLineReader and create a Command object from it.
/// </summary>
/// <returns>A pointer to a Command object created from the current string command in the FileLineReader.</returns>
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
