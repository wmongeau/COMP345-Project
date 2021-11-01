#pragma once

#include <string>
#include <list>
#include <vector>
//#include "Player.h"


class Territory {
private:
	int Id;
	std::string Name;
	int ContinentId;
	int X;
	int Y;
	std::vector<Territory*> Borders;
	//Player* player{nullptr};
	int armyValue;
public:
	Territory(int id, std::string name, int continentId, int x, int y);
	Territory(Territory* territory);
	Territory& operator=(Territory* territory);
	//void updatePlayer(Player* newPlayer);
	void updateArmyValue(int newArmyValue);
	void addBorder(Territory* territory);
	const int getId() const;
	const std::string getName() const;
	const int getContinentId() const;
	const int getX() const;
	const int getY() const;
	//const Player* getPlayer() const;
	const int getArmyValue() const;
	const std::vector<Territory*> getBorders() const;
	const std::string toString() const;
	~Territory();
};

class Continent {
private:
	int Id;
	std::string Name;
	int ArmyValue;
	std::string Colour;
public:
	Continent(int id, std::string name, int armyVal, std::string colour);
	Continent(Continent* continent);
	Continent& operator=(Continent* continent);
	const int getId() const;
	const std::string getName() const;
	const int getArmyValue() const;
	const std::string getColour() const;
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
	void addContinent(Continent* continent);
	void addTerritory(Territory* territory);
	bool validate();
	void dfsTerritory(int Id, Territory* country, std::vector<bool> &visited);
	void dfsTerritorySubGraph(int Id, int continentId, Territory* country, std::vector<bool>& visited, std::vector<int>& subGraphCount);
	bool checkContinentCount();
	Continent* getContinentById(int ContinentId);
	Territory* getTerritoryById(int territoryId);
	void print();
	~Map();
};
