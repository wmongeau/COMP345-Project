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

	return *this;
}

//Destructor for the class Player
Player::~Player()
{
	delete PlayerHand;
	PlayerHand = NULL;

	delete Orders;
	Orders = NULL;
}

//Method returning all the territories a player can attack
vector<Territory *> Player::toAttack()
{

	return CanAttack;
}

//Method returning all the territories a player can defend
vector<Territory *> Player::toDefend()
{
	return CanDefend;
}

//Method used to add a new owned territory to the players list of owned territories
void Player::addOwnedTerritory(Territory *territory)
{
	OwnedTerritories.push_back(territory);
	territory->updatePlayer(this);
}

void Player::issueOrder()
{
	int territoryChoice, territoryChoice2,cardChoice;
	int armyChoice;
	int playerInput = 0;
	int advanceChoice;
	vector<Card*> cards;
	//Deploying phase
	if (reinforcementPool != 0)
	{
		cout << "These are the territories that you can deploy armies in" << endl;
		for (int i = 0; i < OwnedTerritories.size(); i++)
		{
			cout << i << " " << OwnedTerritories[i]->getName() << " " << OwnedTerritories[i]->getArmyValue() << endl;
		}
		cout << "Which territory do you want to deploy armies to?" << endl;
		cin >> territoryChoice;
		cout << "How many armies would you like to deploy of " << reinforcementPool << " armies ?";
		cin >> armyChoice;
		//Add deploy orders to orders list new DeployOrders(this,OwnedTerritories[i],armyChoice);
		Orders->addOrder(new DeployOrder());
		return;
	}
	//Order issuing phase (Advance and Cards)
		cout << "Which action would you like to do?" << endl;
		cout << "[0] Advance [1]Play a card [2]End turn" << endl ;
		cin >> playerInput;
		if (playerInput == 0)
		{
			cout << "Would you like your advance order to Attack[0] or Defend[1]?";
			cin >> advanceChoice;
			if (advanceChoice == 0)
			{
				cout << "These are the territories that you can advance to attack" << endl;
				for (int i = 0; i < toAttack().size(); i++)
				{
					cout << i << " " << toAttack()[i]->getName() << " " << toAttack()[i]->getArmyValue() << endl;
				}
				cout << "Which territory do you want to advance armies to attack? " << endl;
				cin >> territoryChoice;
			}
			if (advanceChoice == 1)
			{
				cout << "These are the territories that you can advance to defend" << endl;
				for (int i = 0; i < toDefend().size(); i++)
				{
					cout << i << " " << toDefend()[i]->getName() << " " << toDefend()[i]->getArmyValue() << endl;
				}
				cout << "Which territory do you want to advance armies to?" << endl;
				cin >> territoryChoice;
			}
			cout << "These are the territories that you can take armies from" << endl;
			for (int i = 0; i < OwnedTerritories.size(); i++)
			{
				cout << i << " " << OwnedTerritories[i]->getName() << " " << OwnedTerritories[i]->getArmyValue() << endl;
			}
			cout << "Which territory do you want to take armies from?" << endl;
			cin >> territoryChoice2;
			cout << "How many armies would you like to advance of " << OwnedTerritories[territoryChoice2]->getArmyValue() << " armies ?";
			cin >> armyChoice;
			if (advanceChoice == 0)
			{
				// new AdvanceOrder(this,OwnedTerritories[territoryChoice2],toAttack()[territoryChoice],armyChoice)
				Orders->addOrder(new AdvanceOrder());
			}
			else if (advanceChoice == 1)
			{
				// new AdvanceOrder(this,OwnedTerritories[territoryChoice2],toDefend()[territoryChoice],armyChoice)
				Orders->addOrder(new AdvanceOrder());
			}
		}
		else if (playerInput == 1)
		{
			cout << "Here's the cards in hand:" << endl;
			cards = PlayerHand->getPlayerHand();
			for (int i = 0; i < cards.size(); i++)
			{
				cout << i << ' ' << cards[i]->getCardType();
			}
			cout << "Which card do you want to play?" << endl;
			cin >> cardChoice;
			cards[cardChoice]->setCardParameter(this);
			Orders->addOrder(cards[cardChoice]->play());
		}
		else if (playerInput == 2)
			isTurnFinish = true;
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

std::vector<Player*> Player::getEnemies()
{
	return enemies;
}

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
void Player::setCanAttack(std::vector<Territory *> territories)
{
	CanAttack = territories;
}

void Player::addTerritoryToDefend(Territory *territory)
{
	CanDefend.push_back(territory);
}

void Player::addTerritoryToAttack(Territory *territory)
{
	CanAttack.push_back(territory);
}

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

bool Player::getIsTurnFinish()
{
	return isTurnFinish;
}

void Player::setIsTurnFinish(bool val)
{
	isTurnFinish = val;
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
