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

string Map::toString() {
    string result;
    
    for(Continent* var : Continents)
    {
        result.append(to_string(var->Id));
        result.append(" ");
        result.append(var->Name);
        result.append(" ");
        result.append(to_string(var->ArmyValue));
        result.append(" ");
        result.append(var->Colour);
        result.append("\n");
        result.append(var->toString());
    }

    for(Territory* var : Territories) {
        result.append(var->toString());
    }

    return result;
}

bool Map::validate() {
    bool territoryIsGraph = false, continentIsGraph = false, singleContinent = false;;
    vector<bool> visitedTerritories(Territories.size()+1), visitedContinents(Continents.size()+1);
    dfsTerritory(Territories[0]->Id, Territories[0], visitedTerritories);
    dfsContinent(Continents[0]->Id, Continents[0], visitedContinents);
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
        adjCountry = country->Borders[i]->Id;
        if (!visited[adjCountry])
            dfsTerritory(adjCountry, country->Borders[i], visited);
    }
}
void Map::dfsContinent(int Id, Continent* continent, vector<bool>& visited) {
    visited[Id] = true;
    int adjContinent;
    for (int i = 0; i < continent->Borders.size(); i++) {
        adjContinent = continent->Borders[i]->Id;
        if (!visited[adjContinent])
            dfsContinent(adjContinent, continent->Borders[i], visited);
    }
}

bool Map::checkContinentCount() {
    vector<int> count(Territories.size() + 1);
    for (int i = 1; i < count.size(); i++)
        count[i] = 0;
    for (int i = 0; i < Territories.size(); i++)
        count[Territories[i]->Id]++;
    for (int i = 1; i < count.size(); i++)
        if (count[i] > 1)
            return false;
    return true;
}

Continent* Map::getContinentById(int continentId) {
    for (int i = 0; i < Continents.size(); i++)
        if (Continents[i]->Id == continentId)
            return Continents[i];
    return NULL;
}

Territory* Map::getTerritoryById(int territoryId) {
    for (int i = 0; i < Territories.size(); i++)
        if (Territories[i]->Id == territoryId)
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

Continent::~Continent() {
    for (auto p : Borders) {
        delete p;
        p = NULL;
    }
}
string Continent::toString()
{
    string result;

    result.append(to_string(Id) + " -->");
    for each (Continent * var in Borders) {
        result.append(" ");
        result.append(to_string(var->Id));
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

string Territory::toString()
{
    string result;

    result.append(Name+" -->");
    for (Territory* var : Borders) {
        result.append(" ");
        result.append(var->Name);
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
