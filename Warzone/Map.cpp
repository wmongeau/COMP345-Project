/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Map.h"

//CLASS: Map
Map::Map() {
    Continents = vector<Continent*>();
};

void Map::addContinent(Continent* continent) {
    Continents.push_back(continent);
}
void Map::addTerritory(Territory* territory)
{
    Territories.push_back(territory);
}
;

void Map::print() {
    cout << endl << "-----LIST OF CONTINENTS AND THEIR BORDERS----- " << endl;
    for(Continent* var : Continents)
    {/*
        result.append(to_string(var->getId()));
        result.append(" ");
        result.append(var->getName());
        result.append(" ");
        result.append(to_string(var->getArmyValue()));
        result.append(" ");
        result.append(var->getColour());
        result.append("\n");*/
        cout << var->toString() << endl;
    }
    cout << "-----LIST OF TERRITORIES AND THEIR BORDERS----- " << endl;
    for(Territory* var : Territories) {
        cout << var->toString() << endl;
    }

}

bool Map::validate() {
    bool territoryIsGraph = false, continentIsGraph = false, singleContinent = false;;
    vector<bool> visitedTerritories(Territories.size()+1), visitedContinents(Continents.size()+1);
    dfsTerritory(Territories[0]->getId(), Territories[0], visitedTerritories);
    dfsContinent(Continents[0]->getId(), Continents[0], visitedContinents);
    int countT = 0,countC=0;
    for (int i = 0; i < Territories.size()+1; i++) {
        if (visitedTerritories[i])
            countT++;
    }
    for (int i = 0; i < Continents.size()+1; i++) {
        if (visitedContinents[i])
            countC++;
    }
    if (countT == visitedTerritories.size() - 1) {
        territoryIsGraph = true;
        cout << "Territory graph is valid!" << endl;
    }
    else
        cout << "Territory graph is invalid!" << endl;
    if (countC == visitedContinents.size() - 1) {
        continentIsGraph = true;
        cout << "Territory graph is valid!" << endl;
    }
    else
         cout << "Continent graph is invalid!" << endl;
    if (checkContinentCount())
    {
        singleContinent = true;
        cout << "All territories belong to a single continent!" << endl;
    }
    else
        cout << "1 or more territory has more than 1 contient!" << endl;
    return territoryIsGraph && continentIsGraph && singleContinent;
}

void Map::dfsTerritory(int Id,Territory* country,vector<bool> &visited) {
    visited[Id] = true;
    int adjCountry;
    for (int i = 0; i < country->Borders.size(); i++) {
        adjCountry = country->Borders[i]->getId();
        if (!visited[adjCountry])
            dfsTerritory(adjCountry, country->Borders[i], visited);
    }
}
void Map::dfsContinent(int Id, Continent* continent, vector<bool>& visited) {
    visited[Id] = true;
    int adjContinent;
    for (int i = 0; i < continent->Borders.size(); i++) {
        adjContinent = continent->Borders[i]->getId();
        if (!visited[adjContinent])
            dfsContinent(adjContinent, continent->Borders[i], visited);
    }
}

bool Map::checkContinentCount() {
    vector<int> count(Territories.size() + 1);
    for (int i = 1; i < count.size(); i++)
        count[i] = 0;
    for (int i = 0; i < Territories.size(); i++)
        count[Territories[i]->getId()]++;
    for (int i = 1; i < count.size(); i++)
        if (count[i] > 1)
            return false;
    return true;
}

Continent* Map::getContinentById(int continentId) {
    for (int i = 0; i < Continents.size(); i++)
        if (Continents[i]->getId() == continentId)
            return Continents[i];
    return NULL;
}

Territory* Map::getTerritoryById(int territoryId) {
    for (int i = 0; i < Territories.size(); i++)
        if (Territories[i]->getId() == territoryId)
            return Territories[i];
    return NULL;
}
Map::~Map() {
    for (auto p : Territories) {
        delete p;
        p = NULL;
    }
    for (auto p : Continents) {
        delete p;
        p = NULL;
    }
}

//CLASS: Continent
Continent::Continent(int id, string name, int armyVal, string colour) {
    Id = id;
    Name = name;
    Colour = colour;
    ArmyValue = armyVal;
}


void Continent::addBorderContinent(Continent* continent) {
    for (int i = 0; i < Borders.size(); i++)
        if (Borders[i]->Id == continent->Id)
            return;
    Borders.push_back(continent);
}

int Continent::getId()
{
    return Id;
}

std::string Continent::getName()
{
    return Name;
}

int Continent::getArmyValue()
{
    return ArmyValue;
}

std::string Continent::getColour()
{
    return Colour;
}

Continent::~Continent() {
    for (auto p : Borders) {
        delete p;
        p = NULL;
    }
}
string Continent::toString()
{
    string result;

    result.append(Name + " -->");
    for each (Continent * var in Borders) {
        result.append(" ");
        result.append(var->getName());
    }
    result.append("\n");
    return result;
}
//CLASS: Territory
Territory::Territory(int id, string name, int continentId, int x, int y) {
    Id = id;
    Name = name;
    ContinentId = continentId;
    X = x;
    Y = y;
}

void Territory::addBorder(Territory* territory) {
    Borders.push_back(territory);
}

int Territory::getId()
{
    return Id;
}

std::string Territory::getName()
{
    return Name;
}

int Territory::getContinentId()
{
    return ContinentId;
}

string Territory::toString()
{
    string result;

    result.append(Name+" -->");
    for (Territory* var : Borders) {
        result.append(" ");
        result.append(var->getName());
    }
    result.append("\n");
    return result;
}

Territory::~Territory() {
    for (auto p : Borders) {
        delete p;
        p = NULL;
    }
}
