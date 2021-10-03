#include "Player.h"
/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;

#include "Player.h"

Player::Player() {
	PlayerName = "";
	PlayerHand = new vector<Card*>;
	OwnedTerritories = new vector<Territory*>;
	CanAttack = new vector<Territory*>;
	CanDefend = new vector<Territory*>;
}

Player::Player(string playerName) {
	PlayerName = playerName;
	PlayerHand = new vector<Card*>;
	OwnedTerritories = new vector<Territory*>;
	CanAttack = new vector<Territory*>;
	CanDefend = new vector<Territory*>;
}

vector<Territory*> Player::toAttack() {

	return CanAttack;
}

vector<Territory*> Player::toDefend() {
	return CanDefend;
}

void Player::addCard(Card* card) {
	PlayerHand.push_back(card);
}

void Player::addOwnedTerritory(Territory* territory) {
	OwnedTerritories.push_back(territory);
}

 void Player::issueOrder() {
	//create order and issue order here
	//update CanAttack and OwnedTerritories
}

 /*
Player* playerDriver(Map* map) {
	Player* player1 = new Player("Will");

	vector<Territory*> owned = vector<Territory*>();
	vector<Territory*> unowned = vector<Territory*>();

	for (Territory* territory : map->Territories) {
		if ((rand() % 100 + 1) > 70) {
			owned.push_back(territory);
			player1->addOwnedTerritory(territory);
		}
	}

	for (Territory* territory : map->Territories) {
		if ((rand() % 100 + 1) > 70) {
			unowned.push_back(territory);
		}
	}

	player1->setCanDefend(owned);
	player1->setCanAttack(unowned);

	return player1;
 }*/