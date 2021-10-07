/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "Player.h"

//Temporary method used to demo the functionality of the Player class
void playerDriver(Map* map) {
	Player* player1 = new Player("Will");
	Card* card1 = new Card(CardTypeEnums::Airlift);
	Card* card2 = new Card(CardTypeEnums::Blockade);
	player1->addCardToHand(card1);
	player1->addCardToHand(card2);
	player1->issueOrder(Negotiate);
	player1->issueOrder(Bomb);

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

	cout << *player1;
 }
