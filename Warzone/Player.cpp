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

//Copy constructor for the class Player
Player::Player(const Player& p) {
	this->PlayerName = p.PlayerName;
	this->PlayerHand = p.PlayerHand;
	this->Orders = p.Orders;
	this->OwnedTerritories = p.OwnedTerritories;
	this->CanAttack = p.CanAttack;
	this->CanDefend = p.CanDefend;
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

 //Getter method for owned territories
 std::vector<Territory*> Player::getOwnedTerritories() {
	 return OwnedTerritories;
 }

 //Getter method for the players hand of cards
 Hand* Player::getPlayerHand() {
	 return PlayerHand;
 }

 //Getter method for the players list of orders
 OrderList* Player::getOrders() {
	 return Orders;
 }

 //Getter method for the players name
 std::string Player::getPlayerName() {
	 return PlayerName;
 }

 //Temporary setter method for the territories that a player can defend
 void Player::setCanDefend(std::vector<Territory*> territories) {
	 CanDefend = territories;
 }

 //Temporary setter method for the territories that a player can attack
 void Player::setCanAttack(std::vector<Territory*> territories) {
	 CanAttack = territories;
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