#pragma once

#include <iostream>
#include <list>
#include "Map.h"
#include "Player.h"

using namespace std;

class Order {
public:
	// Default Constructor
	Order();

	// Parameterized Constructor
	Order(int orderID);

	// Copy Constructor
	Order(const Order& c);

	// Destructor
	~Order();

	int orderID = 0;

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

	vector<Order*> OrdersVector;

	void addOrder(Order* order);

	vector<Order*> showOrdersList();

	// Move an order in the list of orders
	void move(int startIndex, int endIndex);

	// Removes the order at the specified position (index)
	void remove(int index);
};