#pragma once

#include <iostream>
#include <list>
#include "Map.h"

using namespace std;

class Order {
public:
	string name;

	// Default Constructor
	Order();

	// Copy Constructor
	Order(const Order& c);

	// Destructor
	~Order();

	//assignment operator
	Order& operator=(const Order& o);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const Order& o);

	virtual bool execute() = 0;
	virtual bool validate() = 0;

};

// --------------- Order subclasses --------------- //

class DeployOrder : public Order {
public:	
	// Constructors
	DeployOrder();

	// Destructor
	~DeployOrder();

	//assignment operator
	DeployOrder& operator=(const DeployOrder& d);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const DeployOrder& d);

	// If Deploy order is valid or not. If the order is valid, it will output its effect.
	bool validate() override;

	// If Deploy order is successfully executed or not.
	bool execute() override;
};

class AdvanceOrder : public Order {
public:
	// Constructors
	AdvanceOrder();

	// Destructor
	~AdvanceOrder();

	//assignment operator
	AdvanceOrder& operator=(const AdvanceOrder& a);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const AdvanceOrder& a);

	// If Advance order is valid or not. If the order is valid, it will output its effect.
	bool validate() override;

	// If Advance order is successfully executed or not.
	bool execute() override;
};

class BombOrder : public Order {
public:
	// Constructors
	BombOrder();

	// Destructor
	~BombOrder();

	//assignment operator
	BombOrder& operator=(const BombOrder& b);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const BombOrder& b);

	// If Bomb order is valid or not. If the order is valid, it will output its effect.
	bool validate() override;

	// If Bomb order is successfully executed or not.
	bool execute() override;
};

class BlockadeOrder : public Order {
public:
	// Constructors
	BlockadeOrder();

	// Destructor
	~BlockadeOrder();

	//assignment operator
	BlockadeOrder& operator=(const BlockadeOrder& bl);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const BlockadeOrder& bl);

	// If Blockade order is valid or not. If the order is valid, it will output its effect.
	bool validate() override;

	// If Blockade order is successfully executed or not.
	bool execute() override;
};

class AirliftOrder : public Order {
public:
	// Constructors
	AirliftOrder();

	// Destructor
	~AirliftOrder();

	//assignment operator
	AirliftOrder& operator=(const AirliftOrder& air);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const AirliftOrder& air);

	// If Airlift order is valid or not. If the order is valid, it will output its effect.
	bool validate() override;

	// If Airlift order is successfully executed or not.
	bool execute() override;
};

class NegotiateOrder : public Order {
public:
	// Constructors
	NegotiateOrder();

	// Destructor
	~NegotiateOrder();

	//assignment operator
	NegotiateOrder& operator=(const NegotiateOrder& n);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const NegotiateOrder& n);

	// If Negotiate order is valid or not. If the order is valid, it will output its effect.
	bool validate() override;

	// If Negotiate order is successfully executed or not.
	bool execute() override;
};


class OrdersList {
public:
	// Constructors
	OrdersList();

	// Destructor
	~OrdersList();

	//assignment operator
	OrdersList& operator=(const OrdersList& ol);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const OrdersList& ol);

	vector<Order*> OrdersVector;

	void addOrder(Order* order);

	//Display orders from the orderslist
	vector<Order*> showOrdersList();

	// Move an order in the list of orders
	void move(int startIndex, int endIndex);

	// Removes the order at the specified position (index)
	void remove(int index);
};
