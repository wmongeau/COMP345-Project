#pragma once

#include <string>
#include <vector>
#include "Map.h"

using namespace std;

vector<string> splitString(string stringToSplit);

class MapLoader {
public:
	static Map* loadMap();

private:
	static void loadContinent(string continentStr,int *continentId,Map* map);
	static void loadCountry(string country,Map* map);
	static void loadBorder(string border,Map* map);
};
