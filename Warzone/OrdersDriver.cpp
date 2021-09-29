/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include "Orders.h"

void test();

int main(){

	test();


	return 1;
	//contains a main function that creates a list of orders and demonstrates that the OrdersList implemented
}

void test(){
	OrdersList* orderListsDriver = new OrdersList();

	DeployOrder* deployOrder = new DeployOrder();
	cout << "Deploy order works!" << endl;

	AdvanceOrder* advanceOrder = new AdvanceOrder();
	cout << "Advance order works!" << endl;

	BombOrder* bombOrder = new BombOrder();
	cout << "Bomb order works!" << endl;

	AirliftOrder* airliftOrder = new AirliftOrder();
	cout << "Airlift order works!" << endl;

	BlockadeOrder* blockadeOrder = new BlockadeOrder();
	cout << "Blockade order works!" << endl;

	NegotiateOrder* negotiateOrder = new NegotiateOrder();
	cout << "Negotiate order works!" << endl;

	orderListsDriver->addOrder(dynamic_cast<Order*>(deployOrder));
	orderListsDriver->addOrder(dynamic_cast<Order*>(advanceOrder));
	orderListsDriver->addOrder(dynamic_cast<Order*>(bombOrder));
	orderListsDriver->addOrder(dynamic_cast<Order*>(airliftOrder));
	orderListsDriver->addOrder(dynamic_cast<Order*>(blockadeOrder));
	orderListsDriver->addOrder(dynamic_cast<Order*>(negotiateOrder));
	
	orderListsDriver->showOrdersList();
}