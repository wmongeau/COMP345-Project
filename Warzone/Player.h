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
	std::vector<Territory*> OwnedTerritories;
	std::vector<Territory*> CanAttack;
	std::vector<Card*> PlayerHand;
	std::string PlayerName;
	std::vector<Territory*> CanDefend;
	std::vector<Territory*> toDefend();
	std::vector<Territory*> toAttack();
	void issueOrder();
	void addCard(Card* card);
};
