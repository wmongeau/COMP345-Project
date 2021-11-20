#include "./Headers/Player.h"
#include "./Headers/Cards.h"
#include "./Headers/Map.h"
#include "./Headers/Orders.h"
#include <iostream>
#include <string>
using namespace std;

//Default constructor for class Player
Player::Player()
{
	PlayerName = "";
	PlayerHand = new Hand();
	Orders = new OrdersList();
	OwnedTerritories = vector<Territory *>();
	CanAttack = vector<Territory *>();
	CanDefend = vector<Territory *>();
	reinforcementPool = 0;
	playerType = PlayerType::human;
	ps = new HumanPlayerStrategy(this);
}

//Copy constructor for the class Player
Player::Player(const Player &p)
{
	PlayerName = p.PlayerName;
	PlayerHand = p.PlayerHand;
	Orders = p.Orders;
	OwnedTerritories = p.OwnedTerritories;
	CanAttack = p.CanAttack;
	CanDefend = p.CanDefend;
	reinforcementPool = p.reinforcementPool;
	playerType = p.playerType;
	ps = p.ps;
}

//Constructor taking a parameter of type string to be set as the name of the player
Player::Player(string playerName)
{
	PlayerName = playerName;
	PlayerHand = new Hand();
	Orders = new OrdersList();
	OwnedTerritories = vector<Territory *>();
	CanAttack = vector<Territory *>();
	CanDefend = vector<Territory *>();
	reinforcementPool = 0;
	playerType = PlayerType::human;
	ps = new HumanPlayerStrategy(this);
}

Player::Player(string playerName, PlayerType playerType) 
{
	PlayerName = playerName;
	PlayerHand = new Hand();
	Orders = new OrdersList();
	OwnedTerritories = vector<Territory*>();
	CanAttack = vector<Territory*>();
	CanDefend = vector<Territory*>();
	reinforcementPool = 0;
	this->playerType = playerType;
	switch (playerType) 
	{
	case PlayerType::human:
		ps = new HumanPlayerStrategy(this);
		break;
	case PlayerType::cheater:
		ps = new CheaterPlayerStrategy(this);
		break;
	case PlayerType::benevolent:
		ps = new BenevolentPlayerStrategy(this);
		break;
	case PlayerType::neutral:
		ps = new NeutralPlayerStrategy(this);
		break;
	case PlayerType::aggressive:
		ps = new AggressivePlayerStrategy(this);
		break;
	}
}

//Assignment operator for the class Player
Player &Player::operator=(const Player &p)
{
	PlayerName = p.PlayerName;
	PlayerHand = p.PlayerHand;
	Orders = p.Orders;
	OwnedTerritories = p.OwnedTerritories;
	CanAttack = p.CanAttack;
	CanDefend = p.CanDefend;
	reinforcementPool = p.reinforcementPool;
	playerType = p.playerType;

	return *this;
}

//Destructor for the class Player
Player::~Player()
{
	delete PlayerHand;
	PlayerHand = NULL;

	delete Orders;
	Orders = NULL;

	delete ps;
	ps = NULL;
}

//Method returning all the territories a player can attack
vector<Territory *> Player::toAttack()
{
	//IMPORTANT
	//when we replace this with the strategy pattern we must make sure to call adjustPlayerStrategy()
	//this will ensure that if the players type has been changed it will use the correct strategy
	return CanAttack;
}

//Method returning all the territories a player can defend
vector<Territory *> Player::toDefend()
{
	//IMPORTANT
	//when we replace this with the strategy pattern we must make sure to call adjustPlayerStrategy()
	//this will ensure that if the players type has been changed it will use the correct strategy
	return CanDefend;
}

//Method used to add a new owned territory to the players list of owned territories
void Player::addOwnedTerritory(Territory *territory)
{
	OwnedTerritories.push_back(territory);
	removeTerritoryToAttack(territory);
	addTerritoryToDefend(territory);
	territory->updatePlayer(this);
}

// Method used to issue order. Players issue orders and place them in their order list through a call to this method.
// This method is called in a round-robin fashion in the issueOrdersPhase()
void Player::issueOrder()
{
	adjustPlayerStrategy();

	ps->issueOrder();
}

void Player::adjustPlayerStrategy() 
{
	if (playerType == PlayerType::human && typeid(ps).name() != "HumanPlayerStrategy")
	{
		delete ps;
		ps = new HumanPlayerStrategy(this);
		return;
	}
	else if (playerType == PlayerType::neutral && typeid(ps).name() != "NeutralPlayerStrategy")
	{
		delete ps;
		ps = new NeutralPlayerStrategy(this);
		return;
	}
	else if (playerType == PlayerType::benevolent && typeid(ps).name() != "BenevolentPlayerStrategy")
	{
		delete ps;
		ps = new BenevolentPlayerStrategy(this);
		return;
	}
	else if (playerType == PlayerType::cheater && typeid(ps).name() != "CheaterPlayerStrategy")
	{
		delete ps;
		ps = new CheaterPlayerStrategy(this);
		return;
	}
	else if (playerType == PlayerType::aggressive && typeid(ps).name() != "AggressivePlayerStrategy")
	{
		delete ps;
		ps = new AggressivePlayerStrategy(this);
		return;
	}
}

//Method used to removed owned territory
void Player::removeOwnedTerritory(Territory* territory)
{
	removeTerritoryToDefend(territory);
	addTerritoryToAttack(territory);
	int index = 0;
	for (vector<Territory*>::iterator it = OwnedTerritories.begin(); it != OwnedTerritories.end(); ++it)
	{
		if (OwnedTerritories[index]->getId() == territory->getId()) {
			OwnedTerritories.erase(it);
			break;
		}
		index++;
	}
}

//Method used to create an order and add it to the players order list
void Player::issueOrder(OrdersEnum orderType)
{
	//create order and issue order here
	//update CanAttack and OwnedTerritories
	Order *order;

	switch (orderType)
	{
	case OrdersEnum::Deploy:
		order = new DeployOrder();
		break;
	case OrdersEnum::Advance:
		order = new AdvanceOrder();
		break;
	case OrdersEnum::Bomb:
		order = new BombOrder();
		break;
	case OrdersEnum::Blockade:
		order = new BlockadeOrder();
		break;
	case OrdersEnum::Airlift:
		order = new AirliftOrder();
		break;
	case OrdersEnum::Negotiate:
		order = new NegotiateOrder();
		break;
	case OrdersEnum::None:
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
std::vector<Territory *> Player::getOwnedTerritories()
{
	return OwnedTerritories;
}

//Getter method for the players hand of cards
Hand *Player::getPlayerHand()
{
	return PlayerHand;
}

//Getter method for the players list of orders
OrdersList *Player::getOrders()
{
	return Orders;
}

//Getter method for the players name
std::string Player::getPlayerName()
{
	return PlayerName;
}

// Method to get enemies
std::vector<Player*> Player::getEnemies()
{
	return enemies;
}

// Method to set enemies
void Player::setEnemies(vector<Player*> enemies)
{
	this->enemies = enemies;
}

//Temporary setter method for the territories that a player can defend
void Player::setCanDefend(std::vector<Territory *> territories)
{
	CanDefend = territories;
}

//Temporary setter method for the territories that a player can attack
void Player::setCanAttack()
{
	for (int i = 0; i < OwnedTerritories.size(); i++) {
		for (int j = 0; j < OwnedTerritories[i]->getBorders().size(); j++)
			if (!playerCanDefend(OwnedTerritories[i]->getBorders()[j]))
				if (!playerCanAttack(OwnedTerritories[i]->getBorders()[j]))
					addTerritoryToAttack(OwnedTerritories[i]->getBorders()[j]);
	}
}

//Method to add territory to defend
void Player::addTerritoryToDefend(Territory *territory)
{
	CanDefend.push_back(territory);
}

// Method to add territory to attack
void Player::addTerritoryToAttack(Territory *territory)
{
	CanAttack.push_back(territory);
}

// Method to remove territory to defend
void Player::removeTerritoryToDefend(Territory *territory)
{
	int index = 0;
	for (vector<Territory *>::iterator it = CanDefend.begin(); it != CanDefend.end(); ++it)
	{
		if (CanDefend[index]->getId() == territory->getId())
		{
			CanDefend.erase(it);
			break;
		}
		index++;
	}
}

// Method to remove territory to attack
void Player::removeTerritoryToAttack(Territory *territory)
{
	int index = 0;
	for (vector<Territory *>::iterator it = CanAttack.begin(); it != CanAttack.end(); ++it)
	{
		if (CanAttack[index]->getId() == territory->getId())
		{
			CanAttack.erase(it);
			break;
		}
		index++;
	}
}

// Boolean to show if the player can attack that specific territory
bool Player::playerCanAttack(Territory *territory)
{
	int index = 0;
	for (vector<Territory *>::iterator it = CanAttack.begin(); it != CanAttack.end(); ++it)
	{
		if (CanAttack[index]->getId() == territory->getId())
			return true;
		index++;
	}
	return false;
}
// Boolean to show if the player can defend that specific territory
bool Player::playerCanDefend(Territory* territory)
{
	int index = 0;
	for (vector<Territory*>::iterator it = CanDefend.begin(); it != CanDefend.end(); ++it)
	{
		if (CanDefend[index]->getId() == territory->getId())
			return true;
		index++;
	}
	return false;
}

//Temporary method to add cards to the players' hand
void Player::addCardToHand(Card *card)
{
	PlayerHand->selectCard(card);
}

//Method to set the size of the reinforcementPool of the player
void Player::setReinforcementPool(int pool)
{
	reinforcementPool = pool;
}

//Method to get the size of the reinforcement pool
int Player::getReinforcementPool()
{
	return reinforcementPool;
}

// Method to get if the users turn is finished
bool Player::getIsTurnFinish()
{
	return isTurnFinish;
}

// Method to set if the users turn is finished
void Player::setIsTurnFinish(bool val)
{
	isTurnFinish = val;
}

PlayerType Player::getPlayerType()
{
	return playerType;
}

void Player::changePlayerType(PlayerType newType)
{
	playerType = newType;
}

//Stream insertion operator for the Player class. Prints all info relevant to the player.
ostream &operator<<(ostream &out, Player &player)
{
	out << "Name: " << player.getPlayerName() << endl;
	out << "Owned Territories count: " << player.getOwnedTerritories().size() << endl;
	out << "Return of toAttack(): " << endl;

	for (Territory *t : player.toAttack())
	{
		out << "    " << t->getId() << " " << t->getName() << endl;
	}

	out << "Return of toDefend(): " << endl;

	for (Territory *t : player.toDefend())
	{
		out << "    " << t->getId() << " " << t->getName() << endl;
	}

	out << "Hand contains these cards: " << endl;

	for (Card *c : player.getPlayerHand()->getPlayerHand())
	{
		out << "    " << c->getCardType() << endl;
	}

	out << "Orders list contains these orders: " << endl;

	for (Order *o : player.getOrders()->getOrdersVector())
	{
		out << "    " << o->getOrdersType() << endl;
	}

	return out;
}
