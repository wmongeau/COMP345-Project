/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "./Headers/Orders.h"
#include "./Headers/Map.h"
#include "./Headers/Player.h"

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
		effect = "This is the effect of the order.";
		return true;
	}
	else {
		cout << "The order cannot be executed!" << endl;
		return false;
	}
}

// Overloads the stream insertion operator.
ostream& operator<<(ostream& out, const Order& orderOutStream) {
	out << orderOutStream.effect << endl;
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

//Parameterized constructor
DeployOrder::DeployOrder(Player& playerIssuingOrder, Territory& targetedTerritory)
{
	this->_playerIssuingOrder = &playerIssuingOrder;
	this->_targetedTerritory = &targetedTerritory;
}

// Destructor
DeployOrder::~DeployOrder() {
	
}

// Assignment operator
DeployOrder& DeployOrder::operator=(const DeployOrder& d) 
{
	Order::operator=(d);
	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const DeployOrder& deployOrderOutStream) {
	out << deployOrderOutStream.effect << endl;
	return out;
}

// Validate Deploy order
bool DeployOrder::validate() {
	cout << "The Deploy order is valid!" << endl;
	return true;
}

// Execute Deploy order if valid
bool DeployOrder::execute() {
	cout << "Executing Deploy order..." << endl;
	if (validate()) {
		effect = "This is the effect of the order.";
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

//Parameterized constructor
AdvanceOrder::AdvanceOrder(Player& playerIssuingOrder, Territory& sourceTerritory, Territory& targetedTerritory)
{
	this->_playerIssuingOrder = &playerIssuingOrder;
	this->_sourceTerritory = &sourceTerritory;
	this->_targetedTerritory = &targetedTerritory;
}

// Destructor
AdvanceOrder::~AdvanceOrder() {

}

// Assignment operator
AdvanceOrder& AdvanceOrder::operator=(const AdvanceOrder& a)
{
	Order::operator=(a);
	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const AdvanceOrder& advanceOrderOutStream) {
	out << advanceOrderOutStream.effect << endl;
	return out;
}

// Validate Advance order
bool AdvanceOrder::validate() {
	cout << "The Advance order is valid!" << endl;
	return true;
}

// Execute Advance order if valid
bool AdvanceOrder::execute() {
	cout << "Executing Advance order..." << endl;
	if (validate()) {
		effect = "This is the effect of the order.";
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

BombOrder::BombOrder(Player& playerIssuingOrder, Player& targetedPlayer, Territory& targetedTerritory)
{
	this->_playerIssuingOrder = &playerIssuingOrder;
	this->_targetedPlayer = &targetedPlayer;
	this->_targetedTerritory = &targetedTerritory;
}

// Destructor
BombOrder::~BombOrder() {

}

// Assignment operator
BombOrder& BombOrder::operator=(const BombOrder& b)
{
	Order::operator=(b);
	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const BombOrder& bombOrderOutStream) {
	out << bombOrderOutStream.effect << endl;
	return out;
}

// Validate Bomb order
bool BombOrder::validate() {
	cout << "The Bomb order is valid!" << endl;
	return true;
}

// Execute Bomb order if valid
bool BombOrder::execute() {
	cout << "Executing Bomb order..." << endl;
	if (validate()) {
		effect = "This is the effect of the order.";
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

//Parameterized constructor
BlockadeOrder::BlockadeOrder(Player& playerIssuingOrder, Territory& targetedTerritory)
{
	this->_playerIssuingOrder = &playerIssuingOrder;
	this->_targetedTerritory = &targetedTerritory;
}

// Destructor
BlockadeOrder::~BlockadeOrder() {

}

// Assignment operator
BlockadeOrder& BlockadeOrder::operator=(const BlockadeOrder& bl)
{
	Order::operator=(bl);
	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const BlockadeOrder& blockadeOrderOutStream) {
	out << blockadeOrderOutStream.effect << endl;
	return out;
}

// Validate Blockade order
bool BlockadeOrder::validate() {
	cout << "The Blockade order is valid!" << endl;
	return true;
}

// Execute Blockade order if valid
bool BlockadeOrder::execute() {
	cout << "Executing Blockade order..." << endl;
	if (validate()) {
		effect = "This is the effect of the order.";
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

//Parameterized constructor
AirliftOrder::AirliftOrder(Player& playerIssuingOrder, Territory& sourceTerritory, Territory& targetedTerritory)
{
	this->_playerIssuingOrder = &playerIssuingOrder;
	this->_sourceTerritory = &sourceTerritory;
	this->_targetedTerritory = &targetedTerritory;
}

// Destructor
AirliftOrder::~AirliftOrder() {

}

// Assignment operator
AirliftOrder& AirliftOrder::operator=(const AirliftOrder& air)
{
	Order::operator=(air);
	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const AirliftOrder& airliftOrderOutStream) {
	out << airliftOrderOutStream.effect << endl;
	return out;
}

// Validate Airlift order
bool AirliftOrder::validate() {
	cout << "The Airlift order is valid!" << endl;
	return true;
}

// Execute Airlift order if valid
bool AirliftOrder::execute() {
	cout << "Executing Airlift order..." << endl;
	if (validate()) {
		effect = "This is the effect of the order.";
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

NegotiateOrder::NegotiateOrder(Player& playerIssuingOrder, Player& otherPlayer)
{
	this->_playerIssuingOrder = &playerIssuingOrder;
	this->_otherPlayer = &otherPlayer;
}

// Destructor
NegotiateOrder::~NegotiateOrder() {

}

// Assignment operator
NegotiateOrder& NegotiateOrder::operator=(const NegotiateOrder& n)
{
	Order::operator=(n);
	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const NegotiateOrder& negotiateOrderOutStream) {
	out << negotiateOrderOutStream.effect << endl;
	return out;
}

// Validate Negotiate order
bool NegotiateOrder::validate() {
	cout << "The Negotiate order is valid!" << endl;
	return true;
}

// Execute Negotiate order if valid
bool NegotiateOrder::execute() {
	cout << "Executing Negotiate order..." << endl;
	if (validate()) {
		effect = "This is the effect of the order.";
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
	OrdersVector = ol.OrdersVector;
}

// Destructor
OrdersList::~OrdersList() {
	for (auto p : OrdersVector) {
		delete p;
		p = NULL;
	}
}

// Assignment operator
OrdersList& OrdersList::operator=(const OrdersList& ol)
{
	OrdersVector = ol.OrdersVector;
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
	delete OrdersVector.at(index);
	OrdersVector.erase(OrdersVector.begin() + index);
}

// Getter for Orders vector
vector<Order*> OrdersList::getOrdersVector()
{
	return OrdersVector;
}
// ---------- End of OrdersList class ---------- //
