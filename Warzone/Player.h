#pragma once

#include <vector>
#include <string>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Player {
private:
	std::vector<Territory*> CanDefend;
	std::vector<Territory*> CanAttack;
	std::string PlayerName;
	Hand* PlayerHand;
	OrdersList* Orders;
	std::vector<Territory*> OwnedTerritories;
public:
	Player();
	Player(std::string playerName);
	std::vector<Territory*> getOwnedTerritories() {
		return OwnedTerritories;
	}
	Hand* getPlayerHand() {
		return PlayerHand;
	}
	OrdersList* getOrders() {
		return Orders;
	}
	std::string getPlayerName() {
		return PlayerName;
	}
	void setCanDefend(std::vector<Territory*> territories) {
		CanDefend = territories;
	}
	void setCanAttack(std::vector<Territory*> territories) {
		CanAttack = territories;
	}
	std::vector<Territory*> toDefend();
	std::vector<Territory*> toAttack();
	void issueOrder();
	void addOwnedTerritory(Territory* territory);
};

Player* playerDriver(Map* map);
