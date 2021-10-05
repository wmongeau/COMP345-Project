#pragma once

#include <vector>
#include <string>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Player {
public:
	Player();
	Player(const Player& p);
	Player(std::string playerName);
	Player& operator =(const Player& p);
	~Player();
	std::vector<Territory*> getOwnedTerritories();
	Hand* getPlayerHand();
	OrdersList* getOrders();
	std::string getPlayerName();
	void setCanDefend(std::vector<Territory*> territories);
	void setCanAttack(std::vector<Territory*> territories);
	std::vector<Territory*> toDefend();
	std::vector<Territory*> toAttack();
	void issueOrder(string orderType);
	void addOwnedTerritory(Territory* territory);
	void addCardToHand(Card* card);

private:
	std::vector<Territory*> CanDefend;
	std::vector<Territory*> CanAttack;
	std::string PlayerName;
	Hand* PlayerHand;
	OrdersList* Orders;
	std::vector<Territory*> OwnedTerritories;
};

Player* playerDriver(Map* map);
