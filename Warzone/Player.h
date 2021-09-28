#pragma once
#include <vector>
#include <string>
#include "Map.H"
#include "Cards.h"
#include "Orders.h"

class Player {
public:
	Player();
	Player(string playerName) { PlayerName = playerName; };
	vector<Territory*> OwnedTerritories;
	vector<Territory*> CanAttack;
	vector<Card*> PlayerHand;
	string PlayerName;
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	Order* issueOrder();
};