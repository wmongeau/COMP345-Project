/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "Orders.h"

// ---------- Order class ---------- //

// Default constructor
Order::Order() {
	orderID = 0;
}

// Parametrized constructor
Order::Order(int orderID) {
	this->orderID = orderID;
}

// Default constructor
Order::Order(const Order& c) {

}

// Destructor
Order::~Order() {

}

// Overloads the stream insertion operator.
ostream& operator<<(ostream& out, const Order& orderOutStream) {
	out << "The order is being executed" << endl;
	return out;
}

// ---------- End of Order class ---------- //


// ---------- DeployOrder class ---------- //

// Default constructor
DeployOrder::DeployOrder() {

}

// Destructor
DeployOrder::~DeployOrder() {

}

// Stream insertion operator
ostream& operator<<(ostream& out, const DeployOrder& deployOrderOutStream) {
	out << "The Deploy order is being executed" << endl;
	return out;
}

// Validate Deploy order
bool DeployOrder::validate() {
	return true;
}

// Execute Deploy order if valide
bool DeployOrder::execute() {

	if (validate()) {
		return true;
	}
	else {
		return false;
	}

}

// ---------- End of DeployOrder class ---------- //


// ---------- AdvanceOrder class ---------- //

// Default constructor
AdvanceOrder::AdvanceOrder() {

}

// Destructor
AdvanceOrder::~AdvanceOrder() {

}

// Stream insertion operator
ostream& operator<<(ostream& out, const AdvanceOrder& advanceOrderOutStream) {
	out << "The Advance order is being executed" << endl;
	return out;
}

// Validate Advance order
bool AdvanceOrder::validate() {
	return true;
}

// Execute Advance order if valide
bool AdvanceOrder::execute() {

	if (validate()) {
		return true;
	}
	else {
		return false;
	}

}

// ---------- End of AdvanceOrder class ---------- //


// ---------- BombOrder class ---------- //

// Default constructor
BombOrder::BombOrder() {

}

// Destructor
BombOrder::~BombOrder() {

}

// Stream insertion operator
ostream& operator<<(ostream& out, const BombOrder& bombOrderOutStream) {
	out << "The Bomb order is being executed" << endl;
	return out;
}

// Validate Bomb order
bool BombOrder::validate() {
	return true;
}

// Execute Bomb order if valide
bool BombOrder::execute() {

	if (validate()) {
		return true;
	}
	else {
		return false;
	}

}

// ---------- End of BombOrder class ---------- //


// ---------- BlockadeOrder class ---------- //

// Default constructor
BlockadeOrder::BlockadeOrder() {

}

// Destructor
BlockadeOrder::~BlockadeOrder() {

}

// Stream insertion operator
ostream& operator<<(ostream& out, const BlockadeOrder& blockadeOrderOutStream) {
	out << "The Blockade order is being executed" << endl;
	return out;
}

// Validate Blockade order
bool BlockadeOrder::validate() {
	return true;
}

// Execute Blockade order if valide
bool BlockadeOrder::execute() {

	if (validate()) {
		return true;
	}
	else {
		return false;
	}

}

// ---------- End of BlockadeOrder class ---------- //


// ---------- AirliftOrder class ---------- //

// Default constructor
AirliftOrder::AirliftOrder() {

}

// Destructor
AirliftOrder::~AirliftOrder() {

}

// Stream insertion operator
ostream& operator<<(ostream& out, const AirliftOrder& airliftOrderOutStream) {
	out << "The Airlift order is being executed" << endl;
	return out;
}

// Validate Airlift order
bool AirliftOrder::validate() {
	return true;
}

// Execute Airlift order if valide
bool AirliftOrder::execute() {

	if (validate()) {
		return true;
	}
	else {
		return false;
	}

}

// ---------- End of AirliftOrder class ---------- //


// ---------- NegotiateOrder class ---------- //

// Default constructor
NegotiateOrder::NegotiateOrder() {

}

// Destructor
NegotiateOrder::~NegotiateOrder() {

}

// Stream insertion operator
ostream& operator<<(ostream& out, const NegotiateOrder& negotiateOrderOutStream) {
	out << "The Negotiate order is being executed" << endl;
	return out;
}

// Validate Negotiate order
bool NegotiateOrder::validate() {
	return true;
}

// Execute Negotiate order if valide
bool NegotiateOrder::execute() {

	if (validate()) {
		return true;
	}
	else {
		return false;
	}

}

// ---------- End of NegotiateOrder class ---------- //

// ---------- OrdersList class ---------- //

// Default constructor
OrdersList::OrdersList() {

}

// Destructor
OrdersList::~OrdersList() {

}

void OrdersList::addOrder(Order* order)
{
	OrdersVector.push_back(order);
}

vector<Order*> OrdersList::showOrdersList() {
	for (int i = 0; i < OrdersVector.size(); i++) {
		cout << OrdersVector[i] << endl;
	}
	return OrdersVector;

}

// Move order from the start index to the end index.
void OrdersList::move(int startIndex, int endIndex) {
	iter_swap(OrdersVector.begin() + startIndex, OrdersVector.begin() + endIndex);

}

// Remove order at the specified index.
void OrdersList::remove(int index) {
	OrdersVector.erase(OrdersVector.begin() + index);

}

// ---------- End of OrdersList class ---------- //