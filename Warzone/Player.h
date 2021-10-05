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
	std::vector<Territory*> getOwnedTerritories();
	Hand* getPlayerHand();
	OrderList* getOrders();
	std::string getPlayerName();
	void setCanDefend(std::vector<Territory*> territories);
	void setCanAttack(std::vector<Territory*> territories);
	std::vector<Territory*> toDefend();
	std::vector<Territory*> toAttack();
	void issueOrder();
	void addOwnedTerritory(Territory* territory);

private:
	std::vector<Territory*> CanDefend;
	std::vector<Territory*> CanAttack;
	std::string PlayerName;
	Hand* PlayerHand;
	OrderList* Orders;
	std::vector<Territory*> OwnedTerritories;
};

Player* playerDriver(Map* map);