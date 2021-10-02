#pragma once
#include <vector>
#include <string>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Player {
public:
	static Player* tempPlayerDriver(Map* map);
	Player();
	Player(std::string playerName);
	std::vector<Territory*> getOwnedTerritories() {
		return OwnedTerritories;
	};
	void setOwnedTerritories(std::vector<Territory*> territories) {
		OwnedTerritories = territories;
	};
	std::vector<Territory*> getCanAttack() {
		return CanAttack;
	};
	void setCanAttack(std::vector<Territory*> territories) {
		CanAttack = territories;
	};
	std::vector<Territory*> getCanDefend() {
		return CanDefend;
	};
	void setCanDefend(std::vector<Territory*> territories) {
		CanDefend = territories;
	};
	std::vector<Card*> getPlayerHand() {
		return PlayerHand;
	};
	void setPlayerHand(std::vector<Card*> cards) {
		PlayerHand = cards;
	};
	std::string getPlayerName() {
		return PlayerName;
	};
	void setPlayerName(std::string name) {
		PlayerName = name;
	};
	std::vector<Territory*> toDefend();
	std::vector<Territory*> toAttack();
	void issueOrder();
	void addCard(Card* card);
private:
	std::vector<Territory*> OwnedTerritories;
	std::vector<Territory*> CanAttack;
	std::vector<Territory*> CanDefend;
	std::vector<Card*> PlayerHand;
	std::string PlayerName;
};
