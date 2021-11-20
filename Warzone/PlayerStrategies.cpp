#include <iostream>
	using std::cin;
	using std::cout;
#include "Headers/PlayerStrategies.h"
#include "Headers/Player.h"
#include "Headers/Orders.h"
#include "Headers/Cards.h"

PlayerStrategy::PlayerStrategy()
{
	player = NULL;
}

PlayerStrategy::PlayerStrategy(Player* player)
{
	this->player = player;
}

PlayerStrategy::~PlayerStrategy()
{
}

PlayerStrategy::PlayerStrategy(const PlayerStrategy& c)
{
	player = c.player;
}

PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& c)
{
	player = c.player;

	return *this;
}

ostream& operator<<(ostream& out, const PlayerStrategy& c)
{
	out << "Player strategy for player: " << c.player->getPlayerName();

	return out;
}

ostream& operator<<(ostream& out, const HumanPlayerStrategy& c)
{
	out << "Human player strategy for player: " << c.player->getPlayerName();
	return out;
}

ostream& operator<<(ostream& out, const CheaterPlayerStrategy& c)
{
	out << "Cheater player strategy for player: " << c.player->getPlayerName();
	return out;
}

ostream& operator<<(ostream& out, const NeutralPlayerStrategy& c)
{
	out << "Neutral player strategy for player: " << c.player->getPlayerName();
	return out;
}

ostream& operator<<(ostream& out, const AggressivePlayerStrategy& c)
{
	out << "Aggressive player strategy for player: " << c.player->getPlayerName();
	return out;
}

ostream& operator<<(ostream& out, const BenevolentPlayerStrategy& c)
{
	out << "Benevolent player strategy for player: " << c.player->getPlayerName();
	return out;
}

HumanPlayerStrategy::HumanPlayerStrategy()
{
}

HumanPlayerStrategy::HumanPlayerStrategy(Player* player): PlayerStrategy(player)
{
}

HumanPlayerStrategy::~HumanPlayerStrategy()
{
}

HumanPlayerStrategy::HumanPlayerStrategy(const PlayerStrategy& c)
{
	player = c.player;
}

HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& c)
{
	player = c.player;
	return *this;
}

void HumanPlayerStrategy::issueOrder()
{
	int territoryChoice, territoryChoice2, cardChoice;
	int armyChoice;
	int playerInput = 0;
	int advanceChoice;
	vector<Card*> cards;
	cout << "\nPlayer " << player->getPlayerName() << "'s turn" << endl;
	//Deploying phase. Shows all the territories that the user owns and can deploy to. 
	//As long as the player has armies still to deploy (see startup phase and reinforcement phase), it will issue a deploy order and no other order. 
	//Once it has deployed all its available armies, it can proceed with other kinds of orders.
	if (player->getReinforcementPool() != 0)
	{
		cout << "These are the territories that you can deploy armies in" << endl;
		for (int i = 0; i < player->getOwnedTerritories().size(); i++)
		{
			cout << i << " " << player->getOwnedTerritories()[i]->getName() << " " << player->getOwnedTerritories()[i]->getArmyValue() << endl;
		}
		cout << "Which territory do you want to deploy armies to?" << endl;
		cin >> territoryChoice;
		cout << "How many armies would you like to deploy of " << player->getReinforcementPool() << " armies ?";
		cin >> armyChoice;
		player->getOrders()->addOrder(new DeployOrder(*player, *(player->getOwnedTerritories())[territoryChoice], armyChoice));
		player->setReinforcementPool(player->getReinforcementPool() - armyChoice);
		if (player->getReinforcementPool() < 0)
			player->setReinforcementPool(0);
		return;
	}
	//Players issues advance orders to either attack their neigbouring enemies or deploy to their neighbouring owned territories
	cout << "Which action would you like to do?" << endl;
	cout << "[0] Advance [1]Play a card [2]End turn" << endl;
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
		for (int i = 0; i < player->getOwnedTerritories().size(); i++)
		{
			cout << i << " " << player->getOwnedTerritories()[i]->getName() << " " << player->getOwnedTerritories()[i]->getArmyValue() << endl;
		}
		cout << "Which territory do you want to take armies from?" << endl;
		cin >> territoryChoice2;
		cout << "How many armies would you like to advance of " << player->getOwnedTerritories()[territoryChoice2]->getArmyValue() << " armies ?";
		cin >> armyChoice;
		if (advanceChoice == 0)
		{
			player->getOrders()->addOrder(new AdvanceOrder(*player, *(player->getOwnedTerritories())[territoryChoice2], *toAttack()[territoryChoice], armyChoice));
		}
		else if (advanceChoice == 1)
		{
			player->getOrders()->addOrder(new AdvanceOrder(*player, *(player->getOwnedTerritories())[territoryChoice2], *toDefend()[territoryChoice], armyChoice));
		}
	}
	else if (playerInput == 1)
	{
		// The player uses one of the cards in their hand to issue an order that corresponds to the card in question
		cout << "Here's the cards in hand:" << endl;
		cards = player->getPlayerHand()->getPlayerHand();
		for (int i = 0; i < cards.size(); i++)
		{
			cout << i << ' ' << cards[i]->getCardType() << endl;
		}
		cout << "Which card do you want to play?" << endl;
		cin >> cardChoice;
		cards[cardChoice]->setCardParameter(player);
		if (cards[cardChoice]->getCardType() == "Diplomacy" || cards[cardChoice]->getCardType() == "Blockade")
			cards[cardChoice]->playerList = player->getEnemies();
		player->getOrders()->addOrder(cards[cardChoice]->play());
	}
	else if (playerInput == 2)
		player->setIsTurnFinish(true);
}

vector<Territory*> HumanPlayerStrategy::toAttack()
{
	return player->toAttack();
}

vector<Territory*> HumanPlayerStrategy::toDefend()
{
	return player->toDefend();
}

CheaterPlayerStrategy::CheaterPlayerStrategy()
{
}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) : PlayerStrategy(player)
{
	this->player = player;
}

CheaterPlayerStrategy::~CheaterPlayerStrategy()
{
}

CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& c)
{
	player = c.player;
}

CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& c)
{
	player = c.player;
	return *this;
}

void CheaterPlayerStrategy::issueOrder()
{
}

vector<Territory*> CheaterPlayerStrategy::toAttack()
{
	return vector<Territory*>();
}

vector<Territory*> CheaterPlayerStrategy::toDefend()
{
	return vector<Territory*>();
}

NeutralPlayerStrategy::NeutralPlayerStrategy()
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player)
{
	this->player = player;
}

NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& c)
{
	player = c.player;
}

NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& c)
{
	player = c.player;
	return *this;
}

void NeutralPlayerStrategy::issueOrder()
{
}

vector<Territory*> NeutralPlayerStrategy::toAttack()
{
	return vector<Territory*>();
}

vector<Territory*> NeutralPlayerStrategy::toDefend()
{
	return vector<Territory*>();
}

AggressivePlayerStrategy::AggressivePlayerStrategy()
{
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player)
{
	this->player = player;
}

AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& c)
{
	player = c.player;
}

AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& c)
{
	player = c.player;
	return *this;
}

void AggressivePlayerStrategy::issueOrder()
{
}

vector<Territory*> AggressivePlayerStrategy::toAttack()
{
	return vector<Territory*>();
}

vector<Territory*> AggressivePlayerStrategy::toDefend()
{
	return vector<Territory*>();
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player)
{
	this->player = player;
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& c)
{
	player = c.player;
}

BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& c)
{
	player = c.player;
	return *this;
}

void BenevolentPlayerStrategy::issueOrder()
{
}

vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
	return vector<Territory*>();
}

vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
	return vector<Territory*>();
}
