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
	case OrdersEnum::None:
		out << "None";
		break;
	case OrdersEnum::Deploy:
		out << "Deploy";
		break;
	case OrdersEnum::Advance:
		out << "Advance";
		break;
	case OrdersEnum::Bomb:
		out << "Bomb";
		break;
	case OrdersEnum::Blockade:
		out << "Blockade";
		break;
	case OrdersEnum::Airlift:
		out << "Airlift";
		break;
	case OrdersEnum::Negotiate:
		out << "Negotiate";
		break;
	}

	return out;
}

// ---------- Order class ---------- //

// Default constructor
Order::Order() {
	OrdersType = OrdersEnum::None;
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
DeployOrder::DeployOrder() : Order(OrdersEnum::Deploy) {

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
// --> If the target territory does not belong to the player that issued the order, the order is invalid
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
// --> The selected number of armies is added to the number of armies on that territory
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
AdvanceOrder::AdvanceOrder() : Order(OrdersEnum::Advance) {

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
// --> If the source territory does not belong to the player that issued the order, the order is invalid
// --> If the target territory is not adjacent to the source territory, the order is invalid
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
// --> Tells a certain number of army units to move from a source territory to a target adjacent territory
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
				//Fix remove for target player
				//_targetedTerritory->getPlayer()->removeOwnedTerritory(_targetedTerritory);
				_playerIssuingOrder->addOwnedTerritory(_targetedTerritory);
				_targetedTerritory->updateArmyValue(numOfArmies);

				effect: _playerIssuingOrder->getPlayerName() + "attacked and conquered " + _targetedTerritory->getName();
			}
			else {
				effect = _playerIssuingOrder->getPlayerName() + " lost " + to_string(attackDeath) + " army units and his ennemy on "
					+ _targetedTerritory->getName() + " lost " + to_string(defendDeath) + " army units.";
			}
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
BombOrder::BombOrder() : Order(OrdersEnum::Bomb) {

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
// --> If the target belongs to the player that issued the order, the order is invalid
// --> If the target territory is not adjacent to one of the territory owned by the player issuing the order, then the order is invalid
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
// --> Targets a territory owned by another player than the one issuing the order (removes half of the armies from this territory)
// --> Created by playing the bomb card
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
BlockadeOrder::BlockadeOrder() : Order(OrdersEnum::Blockade) {

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
// --> If the target territory belongs to an enemy player, the order is invalid
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
// --> Targets  a territory that belongs to the player issuing the order
// --> Doubles amry units on the territory and transfers ownership of the territory to the Neutral player
// --> Created by playing the blockade card
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
AirliftOrder::AirliftOrder() : Order(OrdersEnum::Airlift) {

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
// --> If the source or target does not belong to the player that issued the order, the order is invalid
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
// --> Tells a certain number of armies taken from a source territory to be moved to a target territory, 
// --> the source and the target territory being owned by the player issuing the order
// --> Created by playing the airlift card
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
NegotiateOrder::NegotiateOrder() : Order(OrdersEnum::Negotiate) {

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
// --> If the target is the player issuing the order, then the order is invalid
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
// --> Targets an enemy player
// --> Results in the target player and the player issuing the order to not be able to successfully attack each others’ territories for the remainder of the turn
// --> Created by playing the diplomacy card
bool NegotiateOrder::execute() {
	cout << "Executing Negotiate order..." << endl;
	if (validate()) {
		for (int i = 0; i < _playerIssuingOrder->getOwnedTerritories().size(); i++) {
			for (int j = 0; j < _ennemyPlayer->toAttack().size(); j++) {
				if (_playerIssuingOrder->getOwnedTerritories()[i] == _ennemyPlayer->toAttack()[j]) {
					_ennemyPlayer->removeTerritoryToAttack(_ennemyPlayer->toAttack()[j]);
					break;
				}
			}
		}

		for (int i = 0; i < _ennemyPlayer->getOwnedTerritories().size(); i++) {
			for (int j = 0; j < _playerIssuingOrder->toAttack().size(); j++) {
				if (_ennemyPlayer->getOwnedTerritories()[i] == _playerIssuingOrder->toAttack()[j]) {
					_playerIssuingOrder->removeTerritoryToAttack(_playerIssuingOrder->toAttack()[j]);
					break;
				}
			}
		}

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
	string orderString;
	switch(OrdersVector.back()->getOrdersType()){
		case OrdersEnum::None:
			orderString = "None";
			break;
		case OrdersEnum::Deploy:
			orderString =  "Deploy";
			break;
		case OrdersEnum::Advance:
			orderString = "Advance";
			break;
		case OrdersEnum::Bomb:
			orderString = "Bomb";
			break;
		case OrdersEnum::Blockade:
			orderString = "Blockade";
			break;
		case OrdersEnum::Airlift:
			orderString = "Airlift";
			break;
		case OrdersEnum::Negotiate:
			orderString = "Negotiate";
			break;
	}
	
	return "Order Issued: " + orderString +'\n';
}
// ---------- End of OrdersList class ---------- //
