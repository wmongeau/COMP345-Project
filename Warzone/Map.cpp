/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include "Map.h"

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
    
    for each (Continent* var in Continents)
    {
        result.append(to_string(var->Id));
        result.append(" ");
        result.append(var->Name);
        result.append(" ");
        result.append(to_string(var->ArmyValue));
        result.append(" ");
        result.append(var->Colour);
        result.append("\n");
    }

    for each (Territory* var in Territories) {
        result.append(var->toString());
    }

    return result;
}

Continent::Continent(int id, string name, int armyVal, string colour) {
    Id = id;
    Name = name;
    Colour = colour;
    ArmyValue = armyVal;
}

void Continent::addTerritory(Territory* territory) {
    Territories.push_back(territory);
}

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

    result.append(to_string(Id));
    for each (Territory * var in Borders) {
        result.append(" ");
        result.append(to_string(Id));
        result.append("\n");
    }
    return result;
}


/*class Territory {
public:
    list<int*> Borders;
    int CountryNum;
    string CountryName;

    Territory(int countryNum, string countryName) {
        Borders = new list<int*>[countryNum];
        CountryNum = countryNum;
    }

    void addedge(int u, int v, bool bi) {
        Borders[u].push_back(v);
        if (bi) {
            Borders[v].push_back(u);
        }
    }

    void print() {
        for (int i = 0; i < n; i++) {
            cout << i << "-->";
            for (auto it : Borders[i]) {
                cout << it << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};*/