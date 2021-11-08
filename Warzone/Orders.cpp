/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "./Headers/Orders.h"

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

//ILoggable function
string Order::stringToLog()
{
	return "Order executed: "+effect + '\n';
}

// If order is valid, execute order
bool Order::execute()
{
		notify(this);
		return true;
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
DeployOrder::DeployOrder(Player& playerIssuingOrder, Territory& targetedTerritory, int _numOfArmies)
{
	this->_playerIssuingOrder = &playerIssuingOrder;
	this->_targetedTerritory = &targetedTerritory;
	this->numOfArmies = _numOfArmies;
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
	for (int i = 0; i < _playerIssuingOrder->getOwnedTerritories().size(); i++) {
		if (_playerIssuingOrder->getOwnedTerritories()[i]->getId() == _targetedTerritory->getId()) {
			cout << "The Deploy order is valid!" << endl;
			return true;
		}
	}
	cout << "The Deploy order is invalid!" << endl;
	return false;
}

// Execute Deploy order if valid
bool DeployOrder::execute() {
	cout << "Executing Deploy order..." << endl;
	if (validate()) {
		_targetedTerritory->addToArmy(numOfArmies);
		effect = "Player " + _playerIssuingOrder->getPlayerName() + " has deployed " + to_string(numOfArmies) + " in " + _targetedTerritory->getName();
		Order::execute();
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
AdvanceOrder::AdvanceOrder(Player& playerIssuingOrder, Territory& sourceTerritory, Territory& targetedTerritory, int _numOfArmies)
{
	this->_playerIssuingOrder = &playerIssuingOrder;
	this->_sourceTerritory = &sourceTerritory;
	this->_targetedTerritory = &targetedTerritory;
	this->numOfArmies = _numOfArmies;
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
	bool isValidSourceTerritory = false;
	bool isValidTargetTerritory = false;

	for (int i = 0; i < _playerIssuingOrder->getOwnedTerritories().size(); i++) {
		if (_playerIssuingOrder->getOwnedTerritories()[i]->getId() == _sourceTerritory->getId()) {
			isValidSourceTerritory = true;
			break;
		}
		else {
			isValidSourceTerritory = false;
		}
	}

	for (int i = 0; i < _targetedTerritory->getBorders().size(); i++) {
		if (_targetedTerritory->getBorders()[i]->getId() == _sourceTerritory->getId()) {
			isValidTargetTerritory = true;
			break;
		}
		else {
			isValidTargetTerritory = true;
		}
	}

	if (isValidSourceTerritory && isValidTargetTerritory) {
		cout << "The Advance order is valid!" << endl;
		return true;
	}
	else {
		cout << "The Advance order is invalid!" << endl;
		return false;
	}

	
	
}

// Execute Advance order if valid
bool AdvanceOrder::execute() {
	cout << "Executing Advance order..." << endl;
	if (validate()) {
		bool isTerritoryOwned = false;
		for (int i = 0; i < _playerIssuingOrder->getOwnedTerritories().size(); i++) {
			if (_playerIssuingOrder->getOwnedTerritories()[i]->getId() == _targetedTerritory->getId()) {
				isTerritoryOwned = true;
				break;
			}
		}
		if (_sourceTerritory->getArmyValue() < numOfArmies);
			numOfArmies = _sourceTerritory->getArmyValue();
		if (isTerritoryOwned) {
			_sourceTerritory->removeFromArmy(numOfArmies);
			_targetedTerritory->addToArmy(numOfArmies);
			effect = _playerIssuingOrder->getPlayerName() + " has moved " + to_string(numOfArmies) + " army unit(s) from " + _sourceTerritory->getName() + " to " + _targetedTerritory->getName();
		}
		else {
			int attackingChance = rand() % 100 + 1;
			int attackDeath = 0;
			int defendingChance = rand() % 100 + 1;
			int defendDeath = 0;
			for (int i = 0; i < numOfArmies; i++) {
				attackingChance = rand() % 100 + 1;
				if (attackingChance <= 60) {
					attackDeath++;
				}
			}

			for (int i = 0; i < _targetedTerritory->getArmyValue(); i++) {
				defendingChance = rand() % 100 + 1;
				if (defendingChance <= 70) {
					defendDeath++;
				}
			}
			_sourceTerritory->removeFromArmy(attackDeath);
			_targetedTerritory->removeFromArmy(defendDeath);
			if (_targetedTerritory->getArmyValue() == 0) {
				_targetedTerritory->removePlayer();
				_playerIssuingOrder->addOwnedTerritory(_targetedTerritory);

			}

			effect = _playerIssuingOrder->getPlayerName() + " advanced and attacked " + _targetedTerritory->getName();
		}


		Order::execute();
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
	bool isTargetTerritory = false;
	bool isTargetBorderOwned = false;
	for (int i = 0; i < _playerIssuingOrder->getOwnedTerritories().size(); i++) {
		if (_playerIssuingOrder->getOwnedTerritories()[i]->getId() == _targetedTerritory->getId()) {
			isTargetTerritory = true;
			break;
		}
	}

	for (int i = 0; i < _targetedTerritory->getBorders().size(); i++) {
		for (int j = 0; j < _playerIssuingOrder->getOwnedTerritories().size(); j++) {
			if (_targetedTerritory->getBorders()[i]->getId() == _playerIssuingOrder->getOwnedTerritories()[j]->getId()) {
				isTargetBorderOwned = true;
				break;
			}	
		}
		if (isTargetBorderOwned) {
			break;
		}
	}

	if (!isTargetTerritory && isTargetBorderOwned) {
		cout << "The Bomb order is valid!" << endl;
		return true;
	}
	else {
		return false;
	}
}

// Execute Bomb order if valid
bool BombOrder::execute() {
	cout << "Executing Bomb order..." << endl;
	if (validate()) {
		_targetedTerritory->updateArmyValue((_targetedTerritory->getArmyValue()) / 2);
		int newArmyValue = _targetedTerritory->getArmyValue();

		effect = "The number of army units has been cut by half, and is now at " + to_string(newArmyValue);
		Order::execute();
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
	bool isOwnedTerritory = false;
	for (int i = 0; i < _playerIssuingOrder->getOwnedTerritories().size(); i++) {
		if (_playerIssuingOrder->getOwnedTerritories()[i]->getId() == _targetedTerritory->getId()) {
			isOwnedTerritory = true;
		}
	}

	if (isOwnedTerritory) {
		cout << "The Blockade order is valid!" << endl;
		return true;
	}
	else {
		cout << "The Blockade order is invalid!" << endl;
		return false;
	}
	
}

// Execute Blockade order if valid
bool BlockadeOrder::execute() {
	cout << "Executing Blockade order..." << endl;
	if (validate()) {
		_targetedTerritory->updateArmyValue((_targetedTerritory->getArmyValue()) * 2);
		int newArmyValue = _targetedTerritory->getArmyValue();
		//_targetedTerritory->setPlayer(new Player("Neutral"));
		//check if Neutral player already exists
		
		effect = "The number of army units on the targeted territory has been double, and is now at " + to_string(newArmyValue);
		Order::execute();
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
AirliftOrder::AirliftOrder(Player& playerIssuingOrder, Territory& sourceTerritory, Territory& targetedTerritory, int _numOfArmies)
{
	this->_playerIssuingOrder = &playerIssuingOrder;
	this->_sourceTerritory = &sourceTerritory;
	this->_targetedTerritory = &targetedTerritory;
	this->numOfArmies = _numOfArmies;
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
	bool isValidSource = false;
	bool isValidTarget = false;

	for (int i = 0; i < _playerIssuingOrder->getOwnedTerritories().size(); i++) {
		if (_playerIssuingOrder->getOwnedTerritories()[i]->getId() == _sourceTerritory->getId()) {
			isValidSource = true;
			break;
		}
	}

	for (int i = 0; i < _playerIssuingOrder->getOwnedTerritories().size(); i++) {
		if (_playerIssuingOrder->getOwnedTerritories()[i]->getId() == _targetedTerritory->getId()) {
			isValidTarget = true;
			break;
		}
	}

	if (isValidSource && isValidTarget) {
		cout << "The Airlift order is valid!" << endl;
		return true;
	}
	else {
		cout << "The Airlift order is invalid!" << endl;
		return false;
	}
}

// Execute Airlift order if valid
bool AirliftOrder::execute() {
	cout << "Executing Airlift order..." << endl;
	if (validate()) {
		_sourceTerritory->updateArmyValue(_sourceTerritory->getArmyValue() - numOfArmies);
		_targetedTerritory->updateArmyValue(_sourceTerritory->getArmyValue() + numOfArmies);
		effect = "Player " + _playerIssuingOrder->getPlayerName() + " has moved " + to_string(numOfArmies) + " army unit(s) from " + _sourceTerritory->getName() + " to " + _targetedTerritory->getName();
		Order::execute();
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

NegotiateOrder::NegotiateOrder(Player& playerIssuingOrder, Player& ennemyPlayer)
{
	this->_playerIssuingOrder = &playerIssuingOrder;
	this->_ennemyPlayer = &ennemyPlayer;
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
	if (_playerIssuingOrder == _ennemyPlayer) {
		cout << "The Negotiate order is invalid!" << endl;
		return false;
	}
	else {
		cout << "The Negotiate order is valid!" << endl;
		return true;
	}
}

// Execute Negotiate order if valid
bool NegotiateOrder::execute() {
	cout << "Executing Negotiate order..." << endl;
	if (validate()) {
		//Wait for code..

		effect = _playerIssuingOrder->getPlayerName() + " and " + _ennemyPlayer->getPlayerName() + " cannot attack each other for the remainder of the turn.";
		Order::execute();
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
	notify(this);
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

//ILoggable function
string OrdersList::stringToLog()
{
	return "Order Issued:" + to_string(OrdersVector.back()->getOrdersType())+'\n';
}
// ---------- End of OrdersList class ---------- //
