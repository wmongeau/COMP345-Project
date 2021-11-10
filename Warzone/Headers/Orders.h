#pragma once

#include <iostream>
#include <list>
#include "Map.h"
#include "LoggingObserver.h"

using namespace std;

// Enum for Order Type
enum class OrdersEnum
{
	None,
	Deploy,
	Advance,
	Bomb,
	Blockade,
	Airlift,
	Negotiate
};

ostream& operator<<(ostream& out, OrdersEnum orderType);

class Order:ILoggable,SubJect {
private:
	// Enum for Order type
	OrdersEnum OrdersType;
protected:
	// Effect of order
	string effect = "Order has not yet been executed.";
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

	// Getter for Enum Order Type
	OrdersEnum getOrdersType();

	//ILoggable function
	string stringToLog();

	// Verifies if order is valid
	virtual bool validate();

	// If order is valid, executes the order
	virtual bool execute();
};

// --------------- Order subclasses --------------- //

class DeployOrder : public Order {
public:	
	// Default Constructor
	DeployOrder();

	// Copy Constructor
	DeployOrder(const DeployOrder& d);

	// Destructor
	~DeployOrder();

	// Assignment operator
	DeployOrder& operator=(const DeployOrder& d);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const DeployOrder& d);

	// Verifies if Deploy order is valid or not
	bool validate() override;

	// If Deploy order is valid, executes order
	bool execute() override;
};

class AdvanceOrder : public Order {
public:
	// Default Constructor
	AdvanceOrder();

	// Copy Constructor
	AdvanceOrder(const AdvanceOrder& a);

	// Destructor
	~AdvanceOrder();

	// Assignment operator
	AdvanceOrder& operator=(const AdvanceOrder& a);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const AdvanceOrder& a);

	// Verifies if Advance order is valid or not
	bool validate() override;

	// If Advance order is valid, executes order
	bool execute() override;
};

class BombOrder : public Order {
public:
	// Default Constructor
	BombOrder();

	// Copy Constructor
	BombOrder(const BombOrder& b);

	// Destructor
	~BombOrder();

	// Assignment operator
	BombOrder& operator=(const BombOrder& b);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const BombOrder& b);

	// Verifies if Bomb order is valid or not
	bool validate() override;

	// If Bomb order is valid, execute order
	bool execute() override;
};

class BlockadeOrder : public Order {
public:
	// Default Constructor
	BlockadeOrder();

	// Copy Constructor
	BlockadeOrder(const BlockadeOrder& bl);

	// Destructor
	~BlockadeOrder();

	// Assignment operator
	BlockadeOrder& operator=(const BlockadeOrder& bl);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const BlockadeOrder& bl);

	// Verifies if Blockade order is valid or not
	bool validate() override;

	// If Blockade order is valid, execute order
	bool execute() override;
};

class AirliftOrder : public Order {
public:
	// Default Constructor
	AirliftOrder();

	// Copy Constructor
	AirliftOrder(const AirliftOrder& air);

	// Destructor
	~AirliftOrder();

	// Assignment operator
	AirliftOrder& operator=(const AirliftOrder& air);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const AirliftOrder& air);

	// Verifies if Airlift order is valid or not.
	bool validate() override;

	// If Airlift order is valid, execute order
	bool execute() override;
};

class NegotiateOrder : public Order {
public:
	// Default Constructor
	NegotiateOrder();

	// Copy Constructor
	NegotiateOrder(const NegotiateOrder& n);

	// Destructor
	~NegotiateOrder();

	// Assignment operator
	NegotiateOrder& operator=(const NegotiateOrder& n);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const NegotiateOrder& n);

	// Verifies if Negotiate order is valid or not
	bool validate() override;

	// If Negotiate order is valid, executed order
	bool execute() override;
};


class OrdersList:ILoggable,SubJect {
public:
	// Default Constructor
	OrdersList();

	// Copy constructor
	OrdersList(const OrdersList& ol);

	// Destructor
	~OrdersList();

	// Assignment operator
	OrdersList& operator=(const OrdersList& ol);

	// Sends order description to the output stream
	friend ostream& operator<<(ostream& out, const OrdersList& ol);

	// Adding an order to an orderslist
	void addOrder(Order* order);

	//Display orders from the orderslist
	vector<Order*> showOrdersList();

	// Move an order in the list of orders from a start index to an end index
	void move(int startIndex, int endIndex);

	// Removes the order at the specified position (index)
	void remove(int index);

	// Getter for the Orders vector
	vector<Order*> getOrdersVector();

	//ILoggable function
	string stringToLog();

private:
	vector<Order*> OrdersVector;
};
