#pragma once

#include <string>
#include <list>

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
};

class Continent {
public:
	int Id;
	string Name;
	int ArmyValue;
	string Colour;
	vector<Territory*> Territories;
	Continent(int id, string name, int armyVal, string colour);
	void addTerritory(Territory* territory);
};

class Map {
public:
	vector<Continent*> Continents;
	vector<Territory*> Territories;
	Map();
	void addContinent(Continent* continent);
	void addTerritory(Territory* territory);
	string toString();
};

