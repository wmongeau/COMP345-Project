#pragma once

#include <vector>
#include <string>

using namespace std;

class Territory;
class Hand;
class OrdersList;
class Card;
enum OrdersEnum;
//Class declaration for the Player class
class Player {
public:
	Player();
	Player(const Player& p);
	Player(string playerName);
	Player& operator =(const Player& p);
	~Player();
	vector<Territory*> getOwnedTerritories();
	Hand* getPlayerHand();
	OrdersList* getOrders();
	string getPlayerName();
	void setCanDefend(vector<Territory*> territories);
	void setCanAttack(vector<Territory*> territories);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder(OrdersEnum orderType);
	void addOwnedTerritory(Territory* territory);
	void addCardToHand(Card* card);
	friend ostream& operator <<(ostream& out, Player& player);

private:
	vector<Territory*> CanDefend;
	vector<Territory*> CanAttack;
	string PlayerName;
	Hand* PlayerHand;
	OrdersList* Orders;
	vector<Territory*> OwnedTerritories;
};

ostream& operator <<(ostream& out, Player& player);
