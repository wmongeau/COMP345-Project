#include "Player.h"

#include <iostream>
#include <string>

using namespace std;

//Default constructor for class Player
Player::Player() {
	PlayerName = "";
	PlayerHand = new Hand();
	Orders = new OrdersList();
	OwnedTerritories = vector<Territory*>();
	CanAttack = vector<Territory*>();
	CanDefend = vector<Territory*>();
}

//Copy constructor for the class Player
Player::Player(const Player& p) {
	PlayerName = p.PlayerName;
	PlayerHand = p.PlayerHand;
	Orders = p.Orders;
	OwnedTerritories = p.OwnedTerritories;
	CanAttack = p.CanAttack;
	CanDefend = p.CanDefend;
}

//Constructor taking a parameter of type string to be set as the name of the player
Player::Player(string playerName) {
	PlayerName = playerName;
	PlayerHand = new Hand();
	Orders = new OrdersList();
	OwnedTerritories = vector<Territory*>();
	CanAttack = vector<Territory*>();
	CanDefend = vector<Territory*>();
}

//Assignment operator for the class Player
Player& Player::operator =(const Player& p) {
	PlayerName = p.PlayerName;
	PlayerHand = p.PlayerHand;
	Orders = p.Orders;
	OwnedTerritories = p.OwnedTerritories;
	CanAttack = p.CanAttack;
	CanDefend = p.CanDefend;

	return *this;
}

//Destructor for the class Player
Player::~Player() {
	delete PlayerHand;
	PlayerHand = NULL;

	delete Orders;
	Orders = NULL;
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
void Player::issueOrder(OrdersEnum orderType) {
	//create order and issue order here
	//update CanAttack and OwnedTerritories
	Order* order;

	switch (orderType) {
		case Deploy:
		 order = new DeployOrder();
			break;
		case Advance:
			order = new AdvanceOrder();
			break;
		case Bomb:
			order = new BombOrder();
			break;
		case Blockade:
			order = new BlockadeOrder();
			break;
		case Airlift:
			order = new AirliftOrder();
			break;
		case Negotiate:
			order = new NegotiateOrder();
			break;
		case None: 
			order = new Order();
			break;
		default:
			order = NULL;
			break;
	}
	
	 if (order == NULL)
		 return;

	 Orders->addOrder(order);
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
 OrdersList* Player::getOrders() {
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

 //Temporary method to add cards to the players' hand
 void Player::addCardToHand(Card* card) {
	 PlayerHand->selectCard(card);
 }

//Temporary method used to demo the functionality of the Player class
Player* playerDriver(Map* map) {
	Player* player1 = new Player("Will");
	Card* card1 = new Card("CardType1");
	Card* card2 = new Card("CardType2");
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

	return player1;
 }

//Stream insertion operator for the Player class. Prints all info relevant to the player.
ostream& operator <<(ostream& out, Player& player)
{
	out << "Name: " << player.getPlayerName() << endl;
	out << "Owned Territories count: " << player.getOwnedTerritories().size() << endl;
	out << "Return of toAttack(): " << endl;

	for (Territory* t : player.toAttack()) {
		out << "    " << t->getId() << " " << t->getName() << endl;
	}

	out << "Return of toDefend(): " << endl;

	for (Territory* t : player.toDefend()) {
		out << "    " << t->getId() << " " << t->getName() << endl;
	}

	out << "Hand contains these cards: " << endl;

	for (Card* c : player.getPlayerHand()->getPlayerHand()) {
		out << "    " << c->getCardType() << endl;
	}

	out << "Orders list contains these orders: " << endl;

	for (Order* o : player.getOrders()->getOrdersVector()) {
		out << "    " << o->getOrdersType() << endl;
	}

	return out;
}
