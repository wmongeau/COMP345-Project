/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include "../Headers/Orders.h"

void ordersDriver(){
	Player* player = new Player();
	Territory* territory = new Territory(1, "Amadou", 1, 0, 0);
	player->addOwnedTerritory(territory);
	// Creating an OrdersList object.
	OrdersList* ordersListDriver = new OrdersList();

	cout << "Creating our Orders using the subclasses:" << endl;

	// Creating an order of every type (each being a subclass of Order).
	DeployOrder* deployOrder = new DeployOrder(*player,*territory, 50);
	cout << "- Deploy order works!" << endl;

	AdvanceOrder* advanceOrder = new AdvanceOrder();
	cout << "- Advance order works!" << endl;

	BombOrder* bombOrder = new BombOrder();
	cout << "- Bomb order works!" << endl;

	AirliftOrder* airliftOrder = new AirliftOrder();
	cout << "- Airlift order works!" << endl;

	BlockadeOrder* blockadeOrder = new BlockadeOrder();
	cout << "- Blockade order works!" << endl;

	NegotiateOrder* negotiateOrder = new NegotiateOrder();
	cout << "- Negotiate order works!" << endl;

	// Using the addOrder function to fill our OrdersList object.
	ordersListDriver->addOrder(deployOrder);
	ordersListDriver->addOrder(advanceOrder);
	ordersListDriver->addOrder(bombOrder);
	ordersListDriver->addOrder(airliftOrder);
	ordersListDriver->addOrder(blockadeOrder);
	ordersListDriver->addOrder(negotiateOrder);
	
	cout << "----------" << endl;

	cout << "Outputting the content of the OrdersList object using the stream insertion operator:" << endl;
	cout << *ordersListDriver;

	cout << "----------" << endl;

	cout << "Testing our validate() method for every Order type:" << endl;
	//testing the validate method
	deployOrder->validate();
	advanceOrder->validate();
	bombOrder->validate();
	blockadeOrder->validate();
	airliftOrder->validate();
	negotiateOrder->validate();

	cout << "----------" << endl;

	cout << "Testing our execute() method for every Order type:" << endl;
	//testing the execute method
	deployOrder->execute();
	cout << *deployOrder;
	advanceOrder->execute();
	cout << *advanceOrder;
	bombOrder->execute();
	cout << *bombOrder;
	blockadeOrder->execute();
	cout << *blockadeOrder;
	airliftOrder->execute();
	cout << *airliftOrder;
	negotiateOrder->execute();
	cout << *negotiateOrder;

	cout << "----------" << endl;

	cout << "Testing our move() method:" << endl;
	//testing the move function
	ordersListDriver->move(1, 3);
	cout << *ordersListDriver;

	cout << "----------" << endl;

	cout << "Testing our remove() method:" << endl;
	//testing the remove function
	ordersListDriver->remove(1);
	cout << *ordersListDriver;
	
	delete ordersListDriver;
	ordersListDriver = NULL;
}
