#pragma once
#include <vector>
#include <string>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Player {
public:
	Player();
	Player(std::string playerName) { PlayerName = playerName; };
	std::vector<Territory*> getOwnedTerritories() {
		return OwnedTerritories;
	}
	std::vector<Card*> getPlayerHand() {
		return PlayerHand;
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
	void addCard(Card* card);
	void addOwnedTerritory(Territory* territory);
private:
	std::vector<Territory*> CanDefend;
	std::vector<Territory*> CanAttack;
	std::string PlayerName;
	std::vector<Card*> PlayerHand;
	std::vector<Territory*> OwnedTerritories;
};

Player* playerDriver(Map* map);
