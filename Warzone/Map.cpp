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
//Default constructor
Map::Map() {
    Continents = vector<Continent*>();
    Territories = vector<Territory*>();
};
//Copy constructor
Map::Map(Map* map) {
    Continents = vector<Continent*>();
    Territories = vector<Territory*>();
    for (int i = 0; i < map->Continents.size(); i++)
    {
        Continents.push_back(new Continent(map-> Continents[i]));
    }
    for (int i = 0; i < map->Territories.size(); i++)
    {
        Territories.push_back(new Territory(map->Territories[i]));
    }
    copyTerritoryBorders(map->Territories);
};
//Assignment operator
Map& Map::operator =(Map* map) {
    Continents = vector<Continent*>();
    Territories = vector<Territory*>();
    for (int i = 0; i < map->Continents.size(); i++)
    {
        Continents.push_back(new Continent(map->Continents[i]));
    }
    for (int i = 0; i < map->Territories.size(); i++)
    {
        Territories.push_back(new Territory(map->Territories[i]));
    }
    copyTerritoryBorders(map->Territories);
    return *this;
};
//Function to copy the graph layout of a Map object
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

//Function to add a Continent object to Map
void Map::addContinent(Continent* continent) {
    Continents.push_back(continent);
}
//Function to add a Territory oobject to Map
void Map::addTerritory(Territory* territory)
{
    Territories.push_back(territory);
};

//Function to print the map details
void Map::print() {
    cout << endl << "-----LIST OF CONTINENTS AND THEIR BORDERS----- " << endl;
    for(Continent* var : Continents)
    {
        cout << var->toString();
    }
    cout << "-----LIST OF TERRITORIES AND THEIR BORDERS----- " << endl;
    for(Territory* var : Territories) {
        cout << var->toString();
    }

}
//stream insertion operator
ostream& operator << (ostream& out, const Map& m)
{
    out << endl << "-----LIST OF CONTINENTS AND THEIR BORDERS----- " << endl;
    for (Continent* var : m.Continents)
    {
        out << var->toString() << endl;
    }
    out << "-----LIST OF TERRITORIES AND THEIR BORDERS----- " << endl;
    for (Territory* var : m.Territories) {
        out << var->toString() << endl;
    }
    return out;
}

//Function to validate if a map respect the requirements
bool Map::validate() {
    bool territoryIsGraph = false, continentIsGraph = true, singleContinent = false;
    vector<bool> visitedTerritories(Territories.size()+1);
    vector<int> subGraphCount(Continents.size() + 1);
    int countT = 0, countC = 0, initIndex = 0;

    //Checking if territories are a valid graph
    dfsTerritory(Territories[initIndex]->getId(), Territories[initIndex], visitedTerritories);
    for (int i = 0; i < Territories.size() + 1; i++) {
        if (visitedTerritories[i])
            countT++;

    }
    cout << "----------------------------------------------" << endl;
    if (countT == visitedTerritories.size() - 1) {
        territoryIsGraph = true;
        cout << "Territory graph is valid!" << endl;
    }
    else
        cout << "Territory graph is invalid!" << endl;

    //Checking if territories are a valid sub-graph for each Continents
    visitedTerritories = vector<bool>(Territories.size() + 1);
    for (int i = 0; i < Continents.size(); i++) {
        while (Territories[initIndex]->getContinentId() != Continents[i]->getId())
            initIndex++;
        dfsTerritorySubGraph(Territories[initIndex]->getId(), Continents[i]->getId(), Territories[initIndex], visitedTerritories, subGraphCount);
        for (int j = 0; j < Territories.size(); j++) {
            if (Territories[j]->getContinentId() == Continents[i]->getId())
                countC++;
        }
        if (countC != subGraphCount[i+1]) {
            continentIsGraph = false;
            break;
        }
        initIndex = 0;
        countC = 0;
    }
    cout << "------------------------" << endl;
    if (continentIsGraph) {
        continentIsGraph = true;
        cout << "Continent has a valid Sub-graph!" << endl;
   }
    else
         cout << "Continent has a invalid Sub-graph!" << endl;
    cout << "------------------------" << endl;

    //Checking if every territories belong to a single continent
    if (checkContinentCount())
    {
        singleContinent = true;
        cout << "All territories belong to a single continent!" << endl;
    }
    else
        cout << "1 or more territory has more than a single contient!" << endl;
    cout << "----------------------------------------------" << endl;

    return territoryIsGraph && continentIsGraph && singleContinent;
}

//Function to traverse the whole map from a chosen territory
void Map::dfsTerritory(int Id,Territory* country,vector<bool> &visited) {
    visited[Id] = true;
    int adjCountry;
    for (int i = 0; i < country->getBorders().size(); i++) {
        adjCountry = country->getBorders()[i]->getId();
        if (!visited[adjCountry])
            dfsTerritory(adjCountry, country->getBorders()[i], visited);
    }
}

//Function to traverse the whole chosen continent from a chosen territory
void Map::dfsTerritorySubGraph(int Id, int continentId, Territory* country, vector<bool>& visited, vector<int>& subGraphCount ) {
    visited[Id]=true;
    subGraphCount[continentId]++;
    int adjCountry,adjContinentId;
    for (int i = 0; i < country->getBorders().size(); i++) {
        adjCountry = country->getBorders()[i]->getId();
        adjContinentId = country->getBorders()[i]->getContinentId();
        if (!visited[adjCountry] && adjContinentId==continentId)
            dfsTerritorySubGraph(adjCountry,continentId, country->getBorders()[i], visited,subGraphCount);
    }
}

//Function to check if a territory belongs to a single continent
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
//Function to get a continent by searching its id
Continent* Map::getContinentById(int continentId) {
    for (int i = 0; i < Continents.size(); i++)
        if (Continents[i]->getId() == continentId)
            return Continents[i];
    return NULL;
}
//Function ro get a territory by searching its id
Territory* Map::getTerritoryById(int territoryId) {
    for (int i = 0; i < Territories.size(); i++)
        if (Territories[i]->getId() == territoryId)
            return Territories[i];
    return NULL;
}
//Destructor
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
//Constructor
Continent::Continent(int id, string name, int armyVal, string colour) {
    Id = id;
    Name = name;
    Colour = colour;
    ArmyValue = armyVal;
}
//Copy constructor
Continent::Continent(Continent* continent)
{
    Id = continent->getId();
    Name = continent->getName();
    Colour = continent->getColour();
    ArmyValue = continent->getArmyValue();
}
//Assignment Operator
Continent& Continent::operator =(Continent* continent)
{
    Id = continent->getId();
    Name = continent->getName();
    Colour = continent->getColour();
    ArmyValue = continent->getArmyValue();
    return *this;
}

//Funciton to get the continent id
const int Continent::getId()const
{
    return Id;
}
//Funciton to get the continent name
const std::string Continent::getName() const
{
    return Name;
}
//Funciton to get the continent army value
const int Continent::getArmyValue()const
{
    return ArmyValue;
}
//Funciton to get the continent colour
const std::string Continent::getColour()const
{
    return Colour;
}
string Continent::toString()
{
    string result;

    result.append(to_string(Id) + " ");
    result.append(Name + " ");
    result.append(to_string(ArmyValue) + " ");
    result.append(Colour);
    result.append("\n");
    return result;
}
//Stream insertion operator
ostream& operator << (ostream& out, const Continent& c)
{
    out << c.getId() << " " << c.getName() << " " << c.getArmyValue() << " " << c.getColour() << endl;
    return out;
}

//Destructor
Continent::~Continent() {
    
}

// ---------- Territory class ---------- //
//Constructor
Territory::Territory(int id, string name, int continentId, int x, int y) {
    Id = id;
    Name = name;
    ContinentId = continentId;
    X = x;
    Y = y;
}
//Copy constructor
Territory::Territory(Territory* territory)
{
    Id = territory->getId();
    Name = territory->getName();
    ContinentId = territory->getContinentId();
    X = territory->getX();
    Y = territory->getY();
}
//Assignment operator
Territory& Territory::operator = (Territory * territory)
{
    Id = territory->getId();
    Name = territory->getName();
    ContinentId = territory->getContinentId();
    X = territory->getX();
    Y = territory->getY();
    return *this;
}
//Function to add an adjacent territory
void Territory::addBorder(Territory* territory) {
    Borders.push_back(territory);
}

//Function to get the Territory id
const int Territory::getId()const
{
    return Id;
}
//Function to get the Territory name
const std::string Territory::getName()const
{
    return Name;
}
//Function to get the continent id
const int Territory::getContinentId()const
{
    return ContinentId;
}
//Function to get x
const int Territory::getX()const
{
    return X;
}
//Function to get y
const int Territory::getY()const
{
    return Y;
}
//Function to get the Territory borders
const std::vector<Territory*> Territory::getBorders() const
{
    return Borders;
}
//Function to return the Territory information
string Territory::toString()
{
    string result;
    result.append(to_string(Id) + " ");
    result.append(Name + " ");
    result.append(to_string(ContinentId) + " ");
    result.append(to_string(X) + " ");
    result.append(to_string(Y) + " ");
    result.append("\n   ");
    result.append(Name+" -->");
    for (Territory* var : Borders) {
        result.append(" ");
        result.append(var->getName());
    }
    result.append("\n");
    return result;
}
//Stream insertion operator
ostream& operator << (ostream& out, const Territory& c)
{
    out << c.getId() << " " << c.getName() << " " << c.getContinentId() << " " << c.getX() << " " << c.getY() << " " << endl;
    out <<"   " << c.getName() << " -->";
    for (Territory* var : c.getBorders()) {
        out << " " << var->getName();
    }
    out << endl;
    return out;
}
//Destructor
Territory::~Territory() {
    for (auto p : Borders) {
        delete p;
        p = NULL;
    }
}