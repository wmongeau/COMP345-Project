#include <iostream>
#include <string>

using namespace std;
#include "../Headers/GameEngine.h"
#include "../Headers/CardsDriver.h"
#include "../Headers/MapDriver.h"
#include "../Headers/OrdersDriver.h"
#include "../Headers/PlayerDriver.h"
#include "../Headers/CommandProcessing.h"
#include "../Headers/MainGameLoopDriver.h"

int main1() {
	int selectmode=-1;

	while (selectmode != 0)
	{
		cout << "Select a driver:" << endl;
		cout << "[0] Quit" << endl
			<< "[1] Orders" << endl
			<< "[2] Main Game Loop" << endl;
		cin >>selectmode;
		switch (selectmode)
		{
		case 1:
			ordersDriver(); break;
		case 2:
			mainGameLoopDriver();
		default:
			break;
		}
	}
	ordersDriver();
	return 0;

}




