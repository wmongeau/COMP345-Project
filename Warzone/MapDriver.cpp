#include <iostream>
#include <string>
#include <fstream> 
#include <vector>

using namespace std;

#include "MapDriver.h";
#include "Player.h";

vector<Player*> playerDriver(Map* map);

//MAIN FUNCTIONS
int main() {
	Map* map;
	try {
		map = MapLoader::loadMap();
		vector<Player*> players = playerDriver(map);
	}
	catch (exception e)
	{
		cout << "This an invalid file";
	}
	cout << map->toString() << endl;
	return 1;
};

vector<Player*> playerDriver(Map* map) {
	Player* player1 = new Player("Will");
	Player* player2 = new Player("Basile");

	vector<Territory*> player1T = vector<Territory*>();
	vector<Territory*> player2T = vector<Territory*>();

	for (Territory* territory : map->Territories) {
		if ((rand() % 100 + 1) > 70) {
			player1T.push_back(territory);
		}
	}

	for (Territory* territory : map->Territories) {
		if ((rand() % 100 + 1) > 70) {
			player2T.push_back(territory);
		}
	}

	player1->CanDefend = player1T;
	player2->CanDefend = player2T;
	player1->CanAttack = player2T;
	player2->CanAttack = player1T;
	vector<Player*> players = vector<Player*>();
	players.push_back(player1);
	players.push_back(player2);
	return players;
}

//FUNCTIONS
//function to split string into an array with a space delimiter
vector<string> splitString(string stringToSplit) {
	vector<string> l;

	char* stringToSplitC = new char[stringToSplit.length() + 1];
	strcpy(stringToSplitC, stringToSplit.c_str());

	char* token;
	token = strtok(stringToSplitC, " ");

	while (token != NULL) {
		l.push_back(token);
		token = strtok(NULL, " ");
	}
	delete[] stringToSplitC;
	delete[] token;
	return l;
};


Map* MapLoader::loadMap() {
	cout << "Enter the file path to the map you wish to play!" << endl;
	string filePath;
	getline(cin, filePath);
	ifstream file(filePath);
	if (!file.is_open())
	{
		cout << "Error: Can't find file path: " << filePath << endl;
		return NULL;
	}
	string line;
	string currentMode;
	Map* map;
	map = new Map();
	int continentId = 1;

	while (getline(file, line)) {

		if (line[0] == ';' || line == "") {
			continue;
		}
		else if (line == "[continents]") {
			currentMode = "continents";
			continue;
		}
		else if (line == "[countries]")
		{
			currentMode = "countries";
			continue;
		}
		else if (line == "[borders]") {
			currentMode = "borders";
			continue;
		}

		if (currentMode == "continents") {
			MapLoader :: loadContinent(line, &continentId, map);
		}
		else if (currentMode == "countries") {
			loadCountry(line, map);
		}
		else if (currentMode == "borders") {
			loadBorder(line,map);
		}
	}
	file.close();
	return map;
};

void MapLoader::loadContinent(string continentStr, int *continentId, Map* map) {
	vector<string> continentAsArray = splitString(continentStr);
	Continent* continent;
	continent = new Continent(*continentId, continentAsArray[0], stoi(continentAsArray[1]), continentAsArray[2]);
	map->addContinent(continent);
	*continentId = *continentId + 1;
}

void MapLoader::loadCountry(string country, Map* map) {
	vector<string> countryAsArray = splitString(country);
	Territory* territory;
	territory = new Territory(stoi(countryAsArray[0]), countryAsArray[1], stoi(countryAsArray[2]), stoi(countryAsArray[3]), stoi(countryAsArray[4]));
	map->addTerritory(territory);
	for each (Continent * cont in map->Continents) {
		if (territory->ContinentId == cont->Id) {
			cont->addTerritory(territory);
		}
	}
}

void MapLoader::loadBorder(string border, Map* map) {
	vector<string> bordersAsArray = splitString(border);
	vector<Territory*> allTerritories = map->Territories;
	Territory* currentTerritory;

	for each (Territory * var in allTerritories)
	{
		if (var->Id == stoi(bordersAsArray[0])) {
			currentTerritory = var;
		}
	}
	int current = stoi(bordersAsArray[0]);
	int edge = 0;
	for (int i = 1; i < bordersAsArray.size(); i++) {
		edge = stoi(bordersAsArray[i]);
		for each (Territory * var in allTerritories)
			if (var->Id == stoi(bordersAsArray[i])) {
				currentTerritory->addBorder(var);
			}
	}
}



