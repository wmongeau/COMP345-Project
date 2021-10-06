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
	std::vector<Territory*> Borders;
public:
	Territory(int id, std::string name, int continentId, int x, int y);
	Territory(Territory* territory);
	Territory& operator=(Territory* territory);
	void addBorder(Territory* territory);
	const int getId() const;
	const std::string getName() const;
	const int getContinentId() const;
	const int getX() const;
	const int getY() const;
	const std::vector<Territory*> getBorders() const;
	std::string toString();
	~Territory();
};

class Continent {
private:
	int Id;
	std::string Name;
	int ArmyValue;
	std::string Colour;
	std::vector<Continent*> Borders;
public:
	Continent(int id, std::string name, int armyVal, std::string colour);
	Continent(Continent* continent);
	Continent& operator=(Continent* continent);
	void addBorderContinent(Continent* continent);
	const int getId() const;
	const std::string getName() const;
	const int getArmyValue() const;
	const std::string getColour() const;
	const std::vector<Continent*> getBorders() const;
	std::string toString();
	~Continent();
};

class Map {
public:
	std::vector<Continent*> Continents;
	std::vector<Territory*> Territories;
	Map();
	Map(Map* map);
	Map& operator=(Map* map);
	void copyTerritoryBorders(std::vector<Territory*> copyTerritory);
	void copyContinentBorders(std::vector<Continent*> copyContinent);
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
