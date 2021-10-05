/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include<stdio.h> 
#include <vector>

using namespace std;
#include "Map.h"

// ---------- Map class ---------- //
Map::Map() {
    Continents = vector<Continent*>();
    Territories = vector<Territory*>();
};

Map::Map(Map* map) {
    Continents = vector<Continent*>();
    Territories = vector<Territory*>();
    for (int i = 0; i < map->Continents.size(); i++)
    {
        Continents.push_back(new Continent(map-> Continents[i]));
    }
    copyContinentBorders(map->Continents);
    for (int i = 0; i < map->Territories.size(); i++)
    {
        Territories.push_back(new Territory(map->Territories[i]));
    }
    copyTerritoryBorders(map->Territories);
};

Map& Map::operator =(Map* map) {
    return *this;
};

void Map::copyTerritoryBorders(std::vector<Territory*> copyTerritories) {
    int copyId = 0;
    for (int i = 0; i < Territories.size(); i++) {
        for (int j = 0; j < copyTerritories[i]->getBorders().size(); j++)
        {
            copyId = copyTerritories[i]->getBorders()[j]->getId();
            Territories[i]->addBorder(getTerritoryById(copyId));
        }
    }
}

void Map::copyContinentBorders(std::vector<Continent*> copyContinent) {
    int copyId = 0;
    for (int i = 0; i < Continents.size(); i++) {
        for (int j = 0; j < copyContinent[i]->getBorders().size(); j++)
        {
            copyId = copyContinent[i]->getBorders()[j]->getId();
            Continents[i]->addBorderContinent(getContinentById(copyId));
        }
    }
}

void Map::addContinent(Continent* continent) {
    Continents.push_back(continent);
}

void Map::addTerritory(Territory* territory)
{
    Territories.push_back(territory);
};

void Map::print() {
    cout << endl << "-----LIST OF CONTINENTS AND THEIR BORDERS----- " << endl;
    for(Continent* var : Continents)
    {
        cout << var->toString() << endl;
    }
    cout << "-----LIST OF TERRITORIES AND THEIR BORDERS----- " << endl;
    for(Territory* var : Territories) {
        cout << var->toString() << endl;
    }

}
ostream& operator << (ostream& out, const Map& c)
{
    out << endl << "-----LIST OF CONTINENTS AND THEIR BORDERS----- " << endl;
    for (Continent* var : c.Continents)
    {
        out << var->toString() << endl;
    }
    out << "-----LIST OF TERRITORIES AND THEIR BORDERS----- " << endl;
    for (Territory* var : c.Territories) {
        out << var->toString() << endl;
    }
    return out;
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
        cout << "1 or more territory has more than a single contient!" << endl;
    return territoryIsGraph && continentIsGraph && singleContinent;
}

void Map::dfsTerritory(int Id,Territory* country,vector<bool> &visited) {
    visited[Id] = true;
    int adjCountry;
    for (int i = 0; i < country->getBorders().size(); i++) {
        adjCountry = country->getBorders()[i]->getId();
        if (!visited[adjCountry])
            dfsTerritory(adjCountry, country->getBorders()[i], visited);
    }
}

void Map::dfsContinent(int Id, Continent* continent, vector<bool>& visited) {
    visited[Id] = true;
    int adjContinent;
    for (int i = 0; i < continent->getBorders().size(); i++) {
        adjContinent = continent->getBorders()[i]->getId();
        if (!visited[adjContinent])
            dfsContinent(adjContinent, continent->getBorders()[i], visited);
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

// ---------- Continent class ---------- //
Continent::Continent(int id, string name, int armyVal, string colour) {
    Id = id;
    Name = name;
    Colour = colour;
    ArmyValue = armyVal;
}

Continent::Continent(Continent* continent)
{
    Id = continent->getId();
    Name = continent->getName();
    Colour = continent->getColour();
    ArmyValue = continent->getArmyValue();
}

Continent& Continent::operator =(Continent* continent)
{
    Id = continent->getId();
    Name = continent->getName();
    Colour = continent->getColour();
    ArmyValue = continent->getArmyValue();
    return *this;
}

void Continent::addBorderContinent(Continent* continent) {
    for (int i = 0; i < Borders.size(); i++)
        if (Borders[i]->Id == continent->Id)
            return;
    Borders.push_back(continent);
}

const int Continent::getId()const
{
    return Id;
}

const std::string Continent::getName() const
{
    return Name;
}

const int Continent::getArmyValue()const
{
    return ArmyValue;
}

const std::string Continent::getColour()const
{
    return Colour;
}

const std::vector<Continent*> Continent::getBorders()const
{
    return Borders;
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
    for(Continent* var : Borders) {
        result.append(" ");
        result.append(var->getName());
    }
    result.append("\n");
    return result;
}

ostream& operator << (ostream& out, const Continent& c)
{
    out << c.getName() << " -->";
    for (Continent* var : c.getBorders()) {
        out << " "<< var->getName();
    }
    out << endl;
    return out;
}

// ---------- Territory class ---------- //
Territory::Territory(int id, string name, int continentId, int x, int y) {
    Id = id;
    Name = name;
    ContinentId = continentId;
    X = x;
    Y = y;
}

Territory::Territory(Territory* territory)
{
    Id = territory->getId();
    Name = territory->getName();
    ContinentId = territory->getContinentId();
    X = territory->getX();
    Y = territory->getY();
}

Territory& Territory::operator = (Territory * territory)
{
    Id = territory->getId();
    Name = territory->getName();
    ContinentId = territory->getContinentId();
    X = territory->getX();
    Y = territory->getY();
    return *this;
}

void Territory::addBorder(Territory* territory) {
    Borders.push_back(territory);
}

const int Territory::getId()const
{
    return Id;
}

const std::string Territory::getName()const
{
    return Name;
}

const int Territory::getContinentId()const
{
    return ContinentId;
}

const int Territory::getX()const
{
    return X;
}

const int Territory::getY()const
{
    return Y;
}

const std::vector<Territory*> Territory::getBorders() const
{
    return Borders;
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
ostream& operator << (ostream& out, const Territory& c)
{
    out << c.getName() << " -->";
    for (Territory* var : c.getBorders()) {
        out << " " << var->getName();
    }
    out << endl;
    return out;
}

Territory::~Territory() {
    for (auto p : Borders) {
        delete p;
        p = NULL;
    }
}