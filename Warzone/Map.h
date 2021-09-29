#pragma once

#include <string>
#include <list>
#include <vector>

class Territory {
public:
	int Id;
	std::string Name;
	int ContinentId;
	int X;
	int Y;
	std::vector<Territory*> Borders;
	Territory(int id, std::string name, int continentId, int x, int y);
	void addBorder(Territory* territory);
	std::string toString();
	~Territory();
};

class Continent {
public:
	int Id;
	std::string Name;
	int ArmyValue;
	std::string Colour;
	std::vector<Territory*> Territories;
	Continent(int id, std::string name, int armyVal, std::string colour);
	void addTerritory(Territory* territory);
	~Continent();
};

class Map {
public:
	std::vector<Continent*> Continents;
	std::vector<Territory*> Territories;
	Map();
	void addContinent(Continent* continent);
	void addTerritory(Territory* territory);
	std::string toString();
	bool validate();
	~Map();
};
