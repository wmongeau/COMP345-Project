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
	int getId();
	std::string getName();
	int getContinentId();
	std::string toString();
	~Territory();
};

class Continent {
public:
	int Id;
	std::string Name;
	int ArmyValue;
	std::string Colour;
	std::vector<Continent*> Borders;
	Continent(int id, string name, int armyVal, string colour);
	void addBorderContinent(Continent* continent);
	int getId();
	std::string getName();
	int getArmyValue();
	string toString();
	~Continent();
};

class Map {
public:
	std::vector<Continent*> Continents;
	std::vector<Territory*> Territories;
	Map();
	void addContinent(Continent* continent);
	void addTerritory(Territory* territory);
	bool validate();
	void dfsTerritory(int Id, Territory* country, vector<bool> &visited);
	void dfsContinent(int Id, Continent* continent, vector<bool>& visited);
	bool checkContinentCount();
	Continent* getContinentById(int ContinentId);
	Territory* getTerritoryById(int territoryId);
	string toString();
	~Map();
};
