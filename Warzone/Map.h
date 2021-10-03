#pragma once

#include <string>
#include <list>
#include <vector>

class Territory {
private:
	int Id;
	std::string Name;
	int ContinentId;
	int X;
	int Y;
public:
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
private:
	int Id;
	std::string Name;
	int ArmyValue;
	std::string Colour;
public:
	std::vector<Continent*> Borders;
	Continent(int id, std::string name, int armyVal, std::string colour);
	void addBorderContinent(Continent* continent);
	int getId();
	std::string getName();
	int getArmyValue();
	std::string getColour();
	std::string toString();
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
	void dfsTerritory(int Id, Territory* country, std::vector<bool> &visited);
	void dfsContinent(int Id, Continent* continent, std::vector<bool>& visited);
	bool checkContinentCount();
	Continent* getContinentById(int ContinentId);
	Territory* getTerritoryById(int territoryId);
	void print();
	~Map();
};
