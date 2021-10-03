#include "Player.h"
/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;

//Default constructor for class Player
Player::Player() {
	PlayerName = "";
	PlayerHand = new Hand();
	Orders = new OrderList();
	OwnedTerritories = vector<Territory*>();
	CanAttack = vector<Territory*>();
	CanDefend = vector<Territory*>();
}

//Constructor taking a parameter of type string to be set as the name of the player
Player::Player(string playerName) {
	PlayerName = playerName;
	PlayerHand = new Hand();
	Orders - new OrderList();
	OwnedTerritories = vector<Territory*>();
	CanAttack = vector<Territory*>();
	CanDefend = vector<Territory*>();
}

//Method returning all the territories a player can attack
vector<Territory*> Player::toAttack() {

	return CanAttack;
}

//Method returning all the territories a player can defend
vector<Territory*> Player::toDefend() {
	return CanDefend;
}

//Method used to add a new owned territory to the players list of owned territories
void Player::addOwnedTerritory(Territory* territory) {
	OwnedTerritories.push_back(territory);
}

//Method used to create an order and add it to the players order list
 void Player::issueOrder() {
	//create order and issue order here
	//update CanAttack and OwnedTerritories
}

 
//Temporary method used to demo the functionality of the Player class
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
 }