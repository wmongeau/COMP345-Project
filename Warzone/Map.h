#pragma once

#include <string>
#include <list>
#include <vector>

class Territory {
public:
	int Id;
	string Name;
	int ContinentId;
	int X;
	int Y;
	vector<Territory*> Borders;
	Territory(int id, string name, int continentId, int x, int y);
	void addBorder(Territory* territory);
	string toString();
	~Territory();
};

class Continent {
public:
	int Id;
	string Name;
	int ArmyValue;
	string Colour;
	vector<Continent*> Borders;
	Continent(int id, string name, int armyVal, string colour);
	void addTerritory(Territory* territory);
	void addBorderContinent(Continent* continent);
	string toString();
	~Continent();
};

class Map {
public:
	vector<Continent*> Continents;
	vector<Territory*> Territories;
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
