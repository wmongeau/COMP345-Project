/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "Player.h"

Player::Player() {
	PlayerName = "";
	PlayerHand = NULL;
	OwnedTerritories = NULL;
	CanAttack = NULL;
}

Player::toAttack() {
	return CanAttack;
}

Player::toDefend() {
	return OwnedTerritories;
}

Player::issueOrder() {
	//create order and issue order here
}