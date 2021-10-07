#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <cstring>

#include "MapDriver.h"
#include "Player.h"

using namespace std;

//Driver for the map loading
void mapDriver() {
	Map* map;
	bool valid = false;
	try {
		while (!valid) {
			map = MapLoader::loadMap();
			if (map == NULL) {
				cout << "Error, map was null";
				return;
			}
			valid = map->validate();
			if (valid)
				cout << "Map is valid and playable!!" << endl;
			else
				cout << "Map is invalid!!" << endl;
		}
	}
	catch (exception e)
	{
		string answer;
		cout << "Unexpected error found!"<<endl
			<<"Press any key to exit application...";
		cin >> answer; 
		return;
	}
	cout << "Do you want to see the map's information?(y/n) ";
	char seeMap;
	cin >> seeMap;
	seeMap = toupper(seeMap);
	if (seeMap == 'Y')
		map->print();
};

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
		else if (line.find("[continents]") != std::string::npos) {
			currentMode = "continents";
			continue;
		}
		else if (line.find("[countries]") != std::string::npos)
		{
			currentMode = "countries";
			continue;
		}
		else if (line.find("[borders]") != std::string::npos) {
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
	if(continentStr == "\r"){
		return;
	}
	vector<string> continentAsArray = splitString(continentStr);
	Continent* continent;
	continent = new Continent(*continentId, continentAsArray[0], stoi(continentAsArray[1]), continentAsArray[2]);
	map->addContinent(continent);
	*continentId = *continentId + 1;
}

void MapLoader::loadCountry(string country, Map* map) {
	if(country == "\r"){
		return;
	}
	vector<string> countryAsArray = splitString(country);
	Territory* territory;
	territory = new Territory(stoi(countryAsArray[0]), countryAsArray[1], stoi(countryAsArray[2]), stoi(countryAsArray[3]), stoi(countryAsArray[4]));
	map->addTerritory(territory);
}

void MapLoader::loadBorder(string border, Map* map) {
	if(border == "\r"){
		return;
	}
	vector<string> bordersAsArray = splitString(border);
	vector<Territory*> allTerritories = map->Territories;
	Territory* currentTerritory;

	currentTerritory = map->getTerritoryById(stoi(bordersAsArray[0]));
	int current = stoi(bordersAsArray[0]);
	int edge = 0;
	for (int i = 1; i < bordersAsArray.size(); i++) {
		edge = stoi(bordersAsArray[i]);
		currentTerritory->addBorder(map->getTerritoryById(edge));
		if (currentTerritory->getContinentId() != map->getTerritoryById(edge)->getContinentId())
			map->getContinentById(currentTerritory->getContinentId())->addBorderContinent(map->getContinentById(map->getTerritoryById(edge)->getContinentId()));
	}
}



