#pragma once

#include <iostream>
#include <list>
#include "Map.h"

using namespace std;

enum OrdersEnum
{
	None = 0,
	Deploy = 1,
	Advance = 2,
	Bomb = 3,
	Blockade = 4,
	Airlift = 5,
	Negotiate = 6
};

ostream& operator<<(ostream& out, OrdersEnum orderType);

class Order {
private:
	// Enum for Order type
	OrdersEnum OrdersType;
public:
	// Default Constructor
	Order();

	//Parameterized constructor
	Order(OrdersEnum value);

	// Copy Constructor
	Order(const Order& c);

	// Destructor
	~Order();

	// Assignment operator
	Order& operator=(const Order& o);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const Order& o);

	OrdersEnum getOrdersType();

	virtual bool execute();
	virtual bool validate();
};

// --------------- Order subclasses --------------- //

class DeployOrder : public Order {
public:	
	// Constructors
	DeployOrder();

	// Copy Constructor
	DeployOrder(const DeployOrder& d);

	// Destructor
	~DeployOrder();

	//assignment operator
	DeployOrder& operator=(const DeployOrder& d);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const DeployOrder& d);

	// If Deploy order is valid or not.
	bool validate() override;

	// If Deploy order is successfully executed or not.
	bool execute() override;
};

class AdvanceOrder : public Order {
public:
	// Constructors
	AdvanceOrder();

	// Copy Constructor
	AdvanceOrder(const AdvanceOrder& a);

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

	// Copy Constructor
	BombOrder(const BombOrder& b);

	// Destructor
	~BombOrder();

	// Assignment operator
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

	// Copy Constructor
	BlockadeOrder(const BlockadeOrder& bl);

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

	// Copy Constructor
	AirliftOrder(const AirliftOrder& air);

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

	// Copy Constructor
	NegotiateOrder(const NegotiateOrder& n);

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

	// Copy constructor
	OrdersList(const OrdersList& ol);

	// Destructor
	~OrdersList();

	//assignment operator
	OrdersList& operator=(const OrdersList& ol);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const OrdersList& ol);

	// Adding an order to an orderslist
	void addOrder(Order* order);

	//Display orders from the orderslist
	vector<Order*> showOrdersList();

	// Move an order in the list of orders
	void move(int startIndex, int endIndex);

	// Removes the order at the specified position (index)
	void remove(int index);

	vector<Order*> getOrdersVector();

private:
	vector<Order*> OrdersVector;
};
