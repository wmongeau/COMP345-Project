#include <iostream>
#include <string>
#include <fstream> 

using namespace std;
#include "Map.h"

int main(){
	ifstream file("../bigeurope.map");
	string line;
	string currentMode;
	while(getline(file, line)){
		if(line[0] == ';'){
			continue;
		}
		else if(line == "[continents]") {
			currentMode = "continents";
		}
		cout << line << endl;
		
	}
	file.close();
	return 1;
}

