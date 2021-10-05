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

}

// Default constructor
Order::Order(const Order& c) {

}

// Destructor
Order::~Order() {
	delete this;
}

// Assignment operator
Order& Order::operator=(const Order& o)
{
	// TODO: insert return statement here
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
	name = "Deploy Order";
}

// Destructor
DeployOrder::~DeployOrder() {
	delete this;
}

// Assignment operator
DeployOrder& DeployOrder::operator=(const DeployOrder& d)
{
	// TODO: insert return statement here
}

// Stream insertion operator
ostream& operator<<(ostream& out, const DeployOrder& deployOrderOutStream) {
	out << "The Deploy order is being executed" << endl;
	return out;
}

// Validate Deploy order
bool DeployOrder::validate() {
	cout << "The order is valid!" << endl;
	return true;
}

// Execute Deploy order if valide
bool DeployOrder::execute() {

	if (validate()) {
		cout << "The order is executable!" << endl;
		return true;
	}
	else {
		cout << "The order cannot be executed!" << endl;
		return false;
	}

}

// ---------- End of DeployOrder class ---------- //


// ---------- AdvanceOrder class ---------- //

// Default constructor
AdvanceOrder::AdvanceOrder() {
	name = "Advance Order";
}

// Destructor
AdvanceOrder::~AdvanceOrder() {
	delete this;
}

// Assignment operator
AdvanceOrder& AdvanceOrder::operator=(const AdvanceOrder& a)
{
	// TODO: insert return statement here
}

// Stream insertion operator
ostream& operator<<(ostream& out, const AdvanceOrder& advanceOrderOutStream) {
	out << "The Advance order is being executed" << endl;
	return out;
}

// Validate Advance order
bool AdvanceOrder::validate() {
	cout << "The order is valid!" << endl;
	return true;
}

// Execute Advance order if valide
bool AdvanceOrder::execute() {

	if (validate()) {
		cout << "The order is executable!" << endl;
		return true;
	}
	else {
		cout << "The order cannot be executed!" << endl;
		return false;
	}

}

// ---------- End of AdvanceOrder class ---------- //


// ---------- BombOrder class ---------- //

// Default constructor
BombOrder::BombOrder() {
	name = "Bomb Order";
}

// Destructor
BombOrder::~BombOrder() {
	delete this;
}

// Assignment operator
BombOrder& BombOrder::operator=(const BombOrder& b)
{
	// TODO: insert return statement here
}

// Stream insertion operator
ostream& operator<<(ostream& out, const BombOrder& bombOrderOutStream) {
	out << "The Bomb order is being executed" << endl;
	return out;
}

// Validate Bomb order
bool BombOrder::validate() {
	cout << "The order is valid!" << endl;
	return true;
}

// Execute Bomb order if valide
bool BombOrder::execute() {

	if (validate()) {
		cout << "The order is executable!" << endl;
		return true;
	}
	else {
		cout << "The order cannot be executed!" << endl;
		return false;
	}

}

// ---------- End of BombOrder class ---------- //


// ---------- BlockadeOrder class ---------- //

// Default constructor
BlockadeOrder::BlockadeOrder() {
	name = "Blockade Order";
}

// Destructor
BlockadeOrder::~BlockadeOrder() {
	delete this;
}

// Assignment operator
BlockadeOrder& BlockadeOrder::operator=(const BlockadeOrder& bl)
{
	// TODO: insert return statement here
}

// Stream insertion operator
ostream& operator<<(ostream& out, const BlockadeOrder& blockadeOrderOutStream) {
	out << "The Blockade order is being executed" << endl;
	return out;
}

// Validate Blockade order
bool BlockadeOrder::validate() {
	cout << "The order is valid!" << endl;
	return true;
}

// Execute Blockade order if valide
bool BlockadeOrder::execute() {

	if (validate()) {
		cout << "The order is executable!" << endl;
		return true;
	}
	else {
		cout << "The order cannot be executed!" << endl;
		return false;
	}

}

// ---------- End of BlockadeOrder class ---------- //


// ---------- AirliftOrder class ---------- //

// Default constructor
AirliftOrder::AirliftOrder() {
	name = "Airlift Order";
}

// Destructor
AirliftOrder::~AirliftOrder() {
	delete this;
}

// Assignment operator
AirliftOrder& AirliftOrder::operator=(const AirliftOrder& air)
{
	// TODO: insert return statement here
}

// Stream insertion operator
ostream& operator<<(ostream& out, const AirliftOrder& airliftOrderOutStream) {
	out << "The Airlift order is being executed" << endl;
	return out;
}

// Validate Airlift order
bool AirliftOrder::validate() {
	cout << "The order is valid!" << endl;
	return true;
}

// Execute Airlift order if valide
bool AirliftOrder::execute() {

	if (validate()) {
		cout << "The order is executable!" << endl;
		return true;
	}
	else {
		cout << "The order cannot be executed!" << endl;
		return false;
	}

}

// ---------- End of AirliftOrder class ---------- //


// ---------- NegotiateOrder class ---------- //

// Default constructor
NegotiateOrder::NegotiateOrder() {
	name = "Negotiate Order";
}

// Destructor
NegotiateOrder::~NegotiateOrder() {
	delete this;
}

// Assignment operator
NegotiateOrder& NegotiateOrder::operator=(const NegotiateOrder& n)
{
	// TODO: insert return statement here
}

// Stream insertion operator
ostream& operator<<(ostream& out, const NegotiateOrder& negotiateOrderOutStream) {
	out << "The Negotiate order is being executed" << endl;
	return out;
}

// Validate Negotiate order
bool NegotiateOrder::validate() {
	cout << "The order is valid!" << endl;
	return true;
}

// Execute Negotiate order if valide
bool NegotiateOrder::execute() {

	if (validate()) {
		cout << "The order is executable!" << endl;
		return true;
	}
	else {
		cout << "The order cannot be executed!" << endl;
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
	delete this;
}

// Assignment operator
OrdersList& OrdersList::operator=(const OrdersList& ol)
{
	// TODO: insert return statement here
}

// Stream insertion operator
ostream& operator<<(ostream& out, const OrdersList& ol)
{
	// TODO: insert return statement here
}

// Adding an order to an orderslist
void OrdersList::addOrder(Order* order)
{
	OrdersVector.push_back(order);
}

// Displays the orders within the orderslist
vector<Order*> OrdersList::showOrdersList() {
	for (int i = 0; i < OrdersVector.size(); i++) {
		cout << OrdersVector[i]->name << endl;
	}
	return OrdersVector;

}

// Move order from the start index to the end index
void OrdersList::move(int startIndex, int endIndex) {
	iter_swap(OrdersVector.begin() + startIndex, OrdersVector.begin() + endIndex);

}

// Remove order at the specified index
void OrdersList::remove(int index) {
	OrdersVector.erase(OrdersVector.begin() + index);

}

// ---------- End of OrdersList class ---------- //