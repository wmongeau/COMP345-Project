#include <iostream>
#include <string>
#include <fstream> 
#include <vector>

using namespace std;
#include "Map.h"

vector<string> splitString(string stringToSplit);

int main(){
	cout << "Enter the file path to the map you wish to play!" << endl;
	string filePath;
	cin >> filePath;
	ifstream file(filePath);
	string line;
	string currentMode;

	Map *map;
	map = new Map();

	int continentId = 1;

	while(getline(file, line)){

		if(line[0] == ';' || line == "") {
			continue;
		}
		else if(line == "[continents]") {
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
			vector<string> continentAsArray = splitString(line);
			Continent *continent;
			continent = new Continent(continentId, continentAsArray[0], stoi(continentAsArray[1]), continentAsArray[2]);
			map->addContinent(continent);
			continentId = continentId + 1;
		}
		else if (currentMode == "countries") {
			vector<string> countryAsArray = splitString(line);
			Territory *territory;
			territory = new Territory(stoi(countryAsArray[0]), countryAsArray[1], stoi(countryAsArray[2]), stoi(countryAsArray[3]), stoi(countryAsArray[4]));
			map->addTerritory(territory);

			for each (Continent* cont in map->Continents) {
				if (territory->ContinentId == cont->Id) {
					cont->addTerritory(territory);
				}
			}
		}
		else if (currentMode == "borders") {
			vector<string> bordersAsArray = splitString(line);
			vector<Territory*> allTerritories = map->Territories;
			Territory *currentTerritory;
			

			for each (Territory* var in allTerritories)
			{
				if (var->Id == stoi(bordersAsArray[0])) {
					currentTerritory = var;
				}
			}

			for (int i = 1; i < bordersAsArray.size(); i++) {
				for each (Territory* var in allTerritories)
					if (var->Id == stoi(bordersAsArray[i])) {
						currentTerritory->addBorder(var);
					}
			}
		}
	}
	cout << map->toString();
	file.close();
	return 1;
}

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

	return l;
};

