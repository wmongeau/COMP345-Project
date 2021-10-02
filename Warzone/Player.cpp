/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Player.h"

Player* Player::tempPlayerDriver(Map* map) {
	Player* player = new Player("Will");

	vector<Territory*> owned = vector<Territory*>();
	vector<Territory*> unowned = vector<Territory*>();

	for (Territory* territory : map->Territories) {
		if ((rand() % 100 + 1) > 70) {
			owned.push_back(territory);
		}
	}

	for (Territory* territory : map->Territories) {
		if ((rand() % 100 + 1) > 70) {
			unowned.push_back(territory);
		}
	}

	player->setCanDefend(owned);
	player->setCanAttack(unowned);

	return player;
}

Player::Player() {
	PlayerName = "";
	PlayerHand = vector<Card*>;
	OwnedTerritories = vector<Territory*>;
	CanAttack = vector<Territory*>;
	CanDefend = vector<Territory*>;
}

Player::Player(string playerName) {
	PlayerName = playerName;
	PlayerHand = vector<Card*>;
	OwnedTerritories = vector<Territory*>;
	CanAttack = vector<Territory*>;
	CanDefend = vector<Territory*>;
}

vector<Territory*> Player::toAttack() {

	return CanAttack;
}

vector<Territory*> Player::toDefend() {
	return OwnedTerritories;
}

void Player::addCard(Card* card) {
	PlayerHand.push_back(card);
}

 void Player::issueOrder() {
	//create order and issue order here
	//update CanAttack and OwnedTerritories
}