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
	OrdersType = None;
}

// Parameterized constructor
Order::Order(OrdersEnum value)
{
	OrdersType = value;
}

// Copy constructor
Order::Order(const Order& c) {
	OrdersType = c.OrdersType;
}

// Destructor
Order::~Order() {
	
}

// Assignment operator
Order& Order::operator=(const Order& o) {
	return *this;
}

// Verify if order is valid
bool Order::validate()
{
	cout << "The order is valid!" << endl;
	return true;
}

// If order is valid, verify if it is executable
bool Order::execute()
{
	if (validate()) {
		cout << "The order is executable!" << endl;
		return true;
	}
	else {
		cout << "The order cannot be executed!" << endl;
		return false;
	}
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
	OrdersType = Deploy;
}

// Copy constructor
DeployOrder::DeployOrder(const DeployOrder& d) {
	OrdersType = d.OrdersType;
}

// Destructor
DeployOrder::~DeployOrder() {
	
}

// Assignment operator
DeployOrder& DeployOrder::operator=(const DeployOrder& d)
{
	return *this;
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
	OrdersType = Advance;
}

// Copy constructor
AdvanceOrder::AdvanceOrder(const AdvanceOrder& a) {
	OrdersType = a.OrdersType;
}

// Destructor
AdvanceOrder::~AdvanceOrder() {

}

// Assignment operator
AdvanceOrder& AdvanceOrder::operator=(const AdvanceOrder& a)
{
	return *this;
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
	OrdersType = Bomb;
}

// Copy constructor
BombOrder::BombOrder(const BombOrder& b) {
	OrdersType = b.OrdersType;
}

// Destructor
BombOrder::~BombOrder() {

}

// Assignment operator
BombOrder& BombOrder::operator=(const BombOrder& b)
{
	return *this;
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
	OrdersType = Blockade;
}

// Copy constructor
BlockadeOrder::BlockadeOrder(const BlockadeOrder& bl) {
	OrdersType = bl.OrdersType;
}

// Destructor
BlockadeOrder::~BlockadeOrder() {

}

// Assignment operator
BlockadeOrder& BlockadeOrder::operator=(const BlockadeOrder& bl)
{
	return *this;
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
	OrdersType = Airlift;
}

// Copy constructor
AirliftOrder::AirliftOrder(const AirliftOrder& air) {
	OrdersType = air.OrdersType;
}

// Destructor
AirliftOrder::~AirliftOrder() {

}

// Assignment operator
AirliftOrder& AirliftOrder::operator=(const AirliftOrder& air)
{
	return *this;
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
	OrdersType = Negotiate;
}

// Copy constructor
NegotiateOrder::NegotiateOrder(const NegotiateOrder& n) {
	OrdersType = n.OrdersType;
}

// Destructor
NegotiateOrder::~NegotiateOrder() {

}

// Assignment operator
NegotiateOrder& NegotiateOrder::operator=(const NegotiateOrder& n)
{
	return *this;
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

// Copy constructor
OrdersList::OrdersList(const OrdersList& ol) {
	OrdersVector = vector<Order*>();

	for (int i = 0; i < ol.OrdersVector.size(); i++) {
		if (ol.OrdersVector[i]->OrdersType == Deploy) {
			OrdersVector.push_back(new DeployOrder());
		}
		else if (ol.OrdersVector[i]->OrdersType == Advance) {
			OrdersVector.push_back(new AdvanceOrder());
		}
		else if (ol.OrdersVector[i]->OrdersType == Bomb) {
			OrdersVector.push_back(new BombOrder());
		}
		else if (ol.OrdersVector[i]->OrdersType == Blockade) {
			OrdersVector.push_back(new BlockadeOrder());
		}
		else if (ol.OrdersVector[i]->OrdersType == Airlift) {
			OrdersVector.push_back(new AirliftOrder());
		}
		else 
			OrdersVector.push_back(new NegotiateOrder());
	}

}

// Destructor
OrdersList::~OrdersList() {

}

// Assignment operator
OrdersList& OrdersList::operator=(const OrdersList& ol)
{
	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const OrdersList& ol)
{
	for (int i = 0; i < ol.OrdersVector.size(); i++) {
		out << ol.OrdersVector[i]->OrdersType << endl;
	}
	return out;
}

// Adding an order to an orderslist
void OrdersList::addOrder(Order* order)
{
	OrdersVector.push_back(order);
}

// Displays the orders within the orderslist
vector<Order*> OrdersList::showOrdersList() {
	for (int i = 0; i < OrdersVector.size(); i++) {
		cout << OrdersVector[i]->OrdersType << endl;
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