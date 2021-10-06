/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "Orders.h"

// Stream insertion operator for Enum Order Types
ostream& operator<<(ostream& out, OrdersEnum orderType) {
	switch (orderType) {
	case None:
		out << "None";
		break;
	case Deploy:
		out << "Deploy";
		break;
	case Advance:
		out << "Advance";
		break;
	case Bomb:
		out << "Bomb";
		break;
	case Blockade:
		out << "Blockade";
		break;
	case Airlift:
		out << "Airlift";
		break;
	case Negotiate:
		out << "Negotiate";
		break;
	}

	return out;
}

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
bool Order::validate() {
	cout << "The order is valid!" << endl;
	return true;
}

// Getter for Order Types
OrdersEnum Order::getOrdersType()
{
	return OrdersType;
}

// If order is valid, execute order
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
DeployOrder::DeployOrder() : Order(Deploy) {

}

// Copy constructor
DeployOrder::DeployOrder(const DeployOrder& d) : Order(d){

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
	cout << "The Deploy order is valid!" << endl;
	return true;
}

// Execute Deploy order if valid
bool DeployOrder::execute() {

	if (validate()) {
		cout << "The Deploy order is executable!" << endl;
		return true;
	}
	else {
		cout << "The Deploy order cannot be executed!" << endl;
		return false;
	}

}

// ---------- End of DeployOrder class ---------- //


// ---------- AdvanceOrder class ---------- //

// Default constructor
AdvanceOrder::AdvanceOrder() : Order(Advance) {

}

// Copy constructor
AdvanceOrder::AdvanceOrder(const AdvanceOrder& a) : Order (a) {

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
	cout << "The Advance order is valid!" << endl;
	return true;
}

// Execute Advance order if valid
bool AdvanceOrder::execute() {

	if (validate()) {
		cout << "The Advance order is executable!" << endl;
		return true;
	}
	else {
		cout << "The Advance order cannot be executed!" << endl;
		return false;
	}

}

// ---------- End of AdvanceOrder class ---------- //


// ---------- BombOrder class ---------- //

// Default constructor
BombOrder::BombOrder() : Order(Bomb) {

}

// Copy constructor
BombOrder::BombOrder(const BombOrder& b) : Order(b) {

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
	cout << "The Bomb order is valid!" << endl;
	return true;
}

// Execute Bomb order if valid
bool BombOrder::execute() {

	if (validate()) {
		cout << "The Bomb order is executable!" << endl;
		return true;
	}
	else {
		cout << "The Bomb order cannot be executed!" << endl;
		return false;
	}

}

// ---------- End of BombOrder class ---------- //


// ---------- BlockadeOrder class ---------- //

// Default constructor
BlockadeOrder::BlockadeOrder() : Order(Blockade) {

}

// Copy constructor
BlockadeOrder::BlockadeOrder(const BlockadeOrder& bl) : Order(bl) {

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
	cout << "The Blockade order is valid!" << endl;
	return true;
}

// Execute Blockade order if valid
bool BlockadeOrder::execute() {

	if (validate()) {
		cout << "The Blockade order is executable!" << endl;
		return true;
	}
	else {
		cout << "The Blockade order cannot be executed!" << endl;
		return false;
	}

}

// ---------- End of BlockadeOrder class ---------- //


// ---------- AirliftOrder class ---------- //

// Default constructor
AirliftOrder::AirliftOrder() : Order(Airlift) {

}

// Copy constructor
AirliftOrder::AirliftOrder(const AirliftOrder& air) : Order(air) {

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
	cout << "The Airlift order is valid!" << endl;
	return true;
}

// Execute Airlift order if valid
bool AirliftOrder::execute() {

	if (validate()) {
		cout << "The Airlift order is executable!" << endl;
		return true;
	}
	else {
		cout << "The Airlift order cannot be executed!" << endl;
		return false;
	}

}

// ---------- End of AirliftOrder class ---------- //


// ---------- NegotiateOrder class ---------- //

// Default constructor
NegotiateOrder::NegotiateOrder() : Order(Negotiate) {

}

// Copy constructor
NegotiateOrder::NegotiateOrder(const NegotiateOrder& n) : Order(n) {

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
	cout << "The Negotiate order is valid!" << endl;
	return true;
}

// Execute Negotiate order if valid
bool NegotiateOrder::execute() {

	if (validate()) {
		cout << "The Negotiate order is executable!" << endl;
		return true;
	}
	else {
		cout << "The Negotiate order cannot be executed!" << endl;
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
		if (ol.OrdersVector[i]->getOrdersType() == Deploy) {
			OrdersVector.push_back(new DeployOrder());
		}
		else if (ol.OrdersVector[i]->getOrdersType() == Advance) {
			OrdersVector.push_back(new AdvanceOrder());
		}
		else if (ol.OrdersVector[i]->getOrdersType() == Bomb) {
			OrdersVector.push_back(new BombOrder());
		}
		else if (ol.OrdersVector[i]->getOrdersType() == Blockade) {
			OrdersVector.push_back(new BlockadeOrder());
		}
		else if (ol.OrdersVector[i]->getOrdersType() == Airlift) {
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
		out << ol.OrdersVector[i]->getOrdersType() << endl;
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
		cout << OrdersVector[i]->getOrdersType() << endl;
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

// Getter for Orders vector
vector<Order*> OrdersList::getOrdersVector()
{
	return OrdersVector;
}

// ---------- End of OrdersList class ---------- //