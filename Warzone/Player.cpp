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
	return OwnedTerritories;
}

void Player::addCard(Card* card) {
	PlayerHand.push_back(card);
}

 void Player::issueOrder() {
	//create order and issue order here
	//update CanAttack and OwnedTerritories
}