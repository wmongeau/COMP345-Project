#include <iostream>
using std::cin;
using std::cout;
#include "Headers/PlayerStrategies.h"
#include "Headers/Player.h"
#include "Headers/Orders.h"
#include "Headers/Cards.h"

/// <summary>
/// Default constructor for PlayerStrategy class
/// </summary>
PlayerStrategy::PlayerStrategy()
{
	player = NULL;
}

/// <summary>
/// Parameterized constructor for PlayerStrategy class taking a Player*
/// </summary>
/// <param name="player">The player this strategy belongs to</param>
PlayerStrategy::PlayerStrategy(Player *player)
{
	this->player = player;
}

/// <summary>
/// Dextructor for the PlayerStrategy class
/// </summary>
PlayerStrategy::~PlayerStrategy()
{
}

/// <summary>
/// Copy constructor for the PlayerStrategy class
/// </summary>
/// <param name="c">The PlayerStrategy being copied</param>
PlayerStrategy::PlayerStrategy(const PlayerStrategy &c)
{
	player = c.player;
}

/// <summary>
/// Overloaded = operator for the PlayerStrategy class
/// </summary>
/// <param name="c">The PlayerStrategy being assigned</param>
/// <returns>A new PlayerStrategy identical to c</returns>
PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &c)
{
	player = c.player;

	return *this;
}

/// <summary>
/// Stream insertion operator overload for the PlayerStrategy class
/// </summary>
/// <param name="out"></param>
/// <param name="c"></param>
/// <returns></returns>
ostream &operator<<(ostream &out, const PlayerStrategy &c)
{
	out << "Player strategy for player: " << c.player->getPlayerName();

	return out;
}

/// <summary>
/// Stream insertion operator overload for the HumanPlayerStrategy class
/// </summary>
/// <param name="out"></param>
/// <param name="c"></param>
/// <returns></returns>
ostream &operator<<(ostream &out, const HumanPlayerStrategy &c)
{
	out << "Human player strategy for player: " << c.player->getPlayerName();
	return out;
}

/// <summary>
/// Stream insertion operator overload for the CheaterPlayerStrategy class
/// </summary>
/// <param name="out"></param>
/// <param name="c"></param>
/// <returns></returns>
ostream &operator<<(ostream &out, const CheaterPlayerStrategy &c)
{
	out << "Cheater player strategy for player: " << c.player->getPlayerName();
	return out;
}

/// <summary>
/// Stream insertion operator overload for the NeutralPlayerStrategy class
/// </summary>
/// <param name="out"></param>
/// <param name="c"></param>
/// <returns></returns>
ostream &operator<<(ostream &out, const NeutralPlayerStrategy &c)
{
	out << "Neutral player strategy for player: " << c.player->getPlayerName();
	return out;
}

/// <summary>
/// Stream insertion operator overload for the AggressivePlayerStrategy class
/// </summary>
/// <param name="out"></param>
/// <param name="c"></param>
/// <returns></returns>
ostream &operator<<(ostream &out, const AggressivePlayerStrategy &c)
{
	out << "Aggressive player strategy for player: " << c.player->getPlayerName();
	return out;
}

/// <summary>
/// Stream insertion operator overload for the BenevolentPlayerStrategy class
/// </summary>
/// <param name="out"></param>
/// <param name="c"></param>
/// <returns></returns>
ostream &operator<<(ostream &out, const BenevolentPlayerStrategy &c)
{
	out << "Benevolent player strategy for player: " << c.player->getPlayerName();
	return out;
}

/// <summary>
/// Default constructor for HumanPlayerStrategy
/// </summary>
HumanPlayerStrategy::HumanPlayerStrategy()
{
}

/// <summary>
/// Parameterized constructor for the HumanPlayerStrategy class
/// </summary>
/// <param name="player"></param>
HumanPlayerStrategy::HumanPlayerStrategy(Player *player) : PlayerStrategy(player)
{
}

/// <summary>
/// Destructor for the HumanPlayerStrategy
/// </summary>
/// <param name="player"></param>
HumanPlayerStrategy::~HumanPlayerStrategy()
{
}

/// <summary>
/// Copy constructor for the HumanPlayerStrategy class
/// </summary>
/// <param name="c">The HumanPlayerStrategy being copied</param>
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &c)
{
	player = c.player;
}

/// <summary>
/// Overloaded = operator for the HumanPlayerStrategy class
/// </summary>
/// <param name="c">The HumanPlayerStrategy being assigned</param>
/// <returns>A new HumanPlayerStrategy identical to c</returns>
HumanPlayerStrategy &HumanPlayerStrategy::operator=(const HumanPlayerStrategy &c)
{
	player = c.player;
	return *this;
}

/// <summary>
/// Issue an order as a Human player
/// </summary>
void HumanPlayerStrategy::issueOrder()
{
	int territoryChoice, territoryChoice2, cardChoice;
	int armyChoice;
	int playerInput = 0;
	int advanceChoice;
	vector<Card *> cards;
	cout << "\nPlayer " << player->getPlayerName() << "'s turn" << endl;
	//Deploying phase. Shows all the territories that the user owns and can deploy to.
	//As long as the player has armies still to deploy (see startup phase and reinforcement phase), it will issue a deploy order and no other order.
	//Once it has deployed all its available armies, it can proceed with other kinds of orders.
	if (player->getReinforcementPool() != 0)
	{
		cout << "These are the territories that you can deploy armies in" << endl;
		for (int i = 0; i < player->getToDefend().size(); i++)
		{
			cout << i << " " << player->getToDefend()[i]->getName() << " " << player->getToDefend()[i]->getArmyValue() << endl;
		}
		cout << "Which territory do you want to deploy armies to?" << endl;
		cin >> territoryChoice;
		cout << "How many armies would you like to deploy of " << player->getReinforcementPool() << " armies ?";
		cin >> armyChoice;
		player->getOrders()->addOrder(new DeployOrder(*player, *(player->getToDefend())[territoryChoice], armyChoice));
		player->setReinforcementPool(player->getReinforcementPool() - armyChoice);
		if (player->getReinforcementPool() < 0)
			player->setReinforcementPool(0);
		return;
	}
	//Players issues advance orders to either attack their neighboring enemies or deploy to their neighboring owned territories
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
			for (int i = 0; i < player->getToAttack().size(); i++)
			{
				cout << i << " " << player->getToAttack()[i]->getName() << " " << player->getToAttack()[i]->getArmyValue() << endl;
			}
			cout << "Which territory do you want to advance armies to attack? " << endl;
			cin >> territoryChoice;
		}
		if (advanceChoice == 1)
		{
			cout << "These are the territories that you can advance to defend" << endl;
			for (int i = 0; i < player->getToDefend().size(); i++)
			{
				cout << i << " " << player->getToDefend()[i]->getName() << " " << player->getToDefend()[i]->getArmyValue() << endl;
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
			player->getOrders()->addOrder(new AdvanceOrder(*player, *(player->getOwnedTerritories())[territoryChoice2], *player->getToAttack()[territoryChoice], armyChoice));
		}
		else if (advanceChoice == 1)
		{
			player->getOrders()->addOrder(new AdvanceOrder(*player, *(player->getOwnedTerritories())[territoryChoice2], *player->getToDefend()[territoryChoice], armyChoice));
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

/// <summary>
/// Get's the territories that the Human player can attack
/// </summary>
/// <returns>The territories the player can attack</returns>
vector<Territory *> HumanPlayerStrategy::toAttack()
{
	vector<Territory *> territoryList = *new vector<Territory *>();
	player->setCanAttack(territoryList);
	for (int i = 0; i < player->getOwnedTerritories().size(); i++)
	{
		for (int j = 0; j < player->getOwnedTerritories()[i]->getBorders().size(); j++)
			if (!player->playerCanDefend(player->getOwnedTerritories()[i]->getBorders()[j]))
				if (!player->playerCanAttack(player->getOwnedTerritories()[i]->getBorders()[j]))
					player->addTerritoryToAttack(player->getOwnedTerritories()[i]->getBorders()[j]);
	}
	return player->getToAttack();
}

/// <summary>
/// Get's the territories that the Human player can defend
/// </summary>
/// <returns>The territories the player can defend</returns>
vector<Territory *> HumanPlayerStrategy::toDefend()
{
	vector<Territory *> territoryList = *new vector<Territory *>();
	player->setCanDefend(territoryList);
	for (int i = 0; i < player->getOwnedTerritories().size(); i++)
	{
		if (!player->playerCanDefend(player->getOwnedTerritories()[i]))
			player->addTerritoryToDefend(player->getOwnedTerritories()[i]);
	}
	return player->getToDefend();
}

/// <summary>
/// Default constructor for CheaterPlayerStrategy
/// </summary>
CheaterPlayerStrategy::CheaterPlayerStrategy()
{
}

/// <summary>
/// Parameterized constructor for the CheaterPlayerStrategy that takes in a player
/// </summary>
/// <param name="player">The player who belongs to this strategy</param>
CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player) : PlayerStrategy(player)
{
	this->player = player;
}

/// <summary>
/// Destructor for the CheaterPlayerStrategy
/// </summary>
CheaterPlayerStrategy::~CheaterPlayerStrategy()
{
}

/// <summary>
/// Copy constructor for the CheaterPlayerStrategy
/// </summary>
/// <param name="c">The CheaterPlayerStrategy being copied</param>
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy &c)
{
	player = c.player;
}

/// <summary>
/// Overloaded = operator for the CheaterPlayerStrategy class
/// </summary>
/// <param name="c">The CheaterPlayerStrategy being assigned</param>
/// <returns>A new CheaterPlayerStrategy identical to c</returns>
CheaterPlayerStrategy &CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy &c)
{
	player = c.player;
	return *this;
}

/// <summary>
/// Issue an order as a Cheater player
/// </summary>
void CheaterPlayerStrategy::issueOrder()
{
	cout << "\nPlayer " << player->getPlayerName() << "'s turn" << endl;
	cout << "These are the territories the cheater will steal:" << endl;
	for (int i = 0; i < player->getToAttack().size(); i++)
	{
		cout << i << " " << player->getToAttack()[i]->getName() << " " << player->getToAttack()[i]->getArmyValue() << endl;
		player->getOrders()->addOrder(new AdvanceOrder(*player, *(player->getOwnedTerritories())[0], *player->getToAttack()[i], 1));
	}
	player->setIsTurnFinish(true);
}

/// <summary>
/// Get's the territories that the Cheater player can attack
/// </summary>
/// <returns>The territories the player can attack</returns>
vector<Territory *> CheaterPlayerStrategy::toAttack()
{
	vector<Territory *> territoryList = *new vector<Territory *>();
	player->setCanAttack(territoryList);
	for (int i = 0; i < player->getOwnedTerritories().size(); i++)
	{
		for (int j = 0; j < player->getOwnedTerritories()[i]->getBorders().size(); j++)
			if (!player->playerCanDefend(player->getOwnedTerritories()[i]->getBorders()[j]))
				if (!player->playerCanAttack(player->getOwnedTerritories()[i]->getBorders()[j]))
					player->addTerritoryToAttack(player->getOwnedTerritories()[i]->getBorders()[j]);
	}
	return player->getToAttack();
}

/// <summary>
/// Get's the territories that the Cheater player can defend
/// </summary>
/// <returns>The territories the player can defend</returns>
vector<Territory *> CheaterPlayerStrategy::toDefend()
{
	vector<Territory *> territoryList = *new vector<Territory *>();
	player->setCanDefend(territoryList);
	for (int i = 0; i < player->getOwnedTerritories().size(); i++)
	{
		if (!player->playerCanDefend(player->getOwnedTerritories()[i]))
			player->addTerritoryToDefend(player->getOwnedTerritories()[i]);
	}
	return player->getToDefend();
}

/// <summary>
/// Default constructor for NeutralPlayerStrategy
/// </summary>
NeutralPlayerStrategy::NeutralPlayerStrategy()
{
}

/// <summary>
/// Parameterized constructor for the NeutralPlayerStrategy that takes in a player
/// </summary>
/// <param name="player">The player using the strategy</param>
NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) : PlayerStrategy(player)
{
	this->player = player;
}

/// <summary>
/// Destructor for the NeutralPlayerStrategy
/// </summary>
NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
}

/// <summary>
/// Copy constructor for the NeutralPlayerStrategy
/// </summary>
/// <param name="c">The NeutralPlayerStrategy being copied</param>
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &c)
{
	player = c.player;
}

/// <summary>
/// Overloaded = operator for the NeutralPlayerStrategy class
/// </summary>
/// <param name="c">The NeutralPlayerStrategy being assigned</param>
/// <returns>A new NeutralPlayerStrategy identical to c</returns>
NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &c)
{
	player = c.player;
	return *this;
}

/// <summary>
/// Issue an order as a Neutral player
/// </summary>
void NeutralPlayerStrategy::issueOrder()
{
	cout << "\nPlayer " << player->getPlayerName() << "'s turn" << endl;
	cout << "These are the territories that the neutral player owns:" << endl;
	for (int i = 0; i < player->getToDefend().size(); i++)
	{
		cout << i << " " << player->getToDefend()[i]->getName() << " " << player->getToDefend()[i]->getArmyValue() << endl;
	}
	cout << "\nPlayer " << player->getPlayerName() << "  is standing by." << endl;
	player->setIsTurnFinish(true);
}

/// <summary>
/// Get's the territories that the Neutral player can attack
/// </summary>
/// <returns>The territories the player can attack</returns>
vector<Territory *> NeutralPlayerStrategy::toAttack()
{
	return vector<Territory *>();
}

/// <summary>
/// Get's the territories that the Neutral player can defend
/// </summary>
/// <returns>The territories the player can defend</returns>
vector<Territory *> NeutralPlayerStrategy::toDefend()
{
	vector<Territory*> territoryList = *new vector<Territory*>();
	player->setCanDefend(territoryList);
	for (int i = 0; i < player->getOwnedTerritories().size(); i++)
	{
		if (!player->playerCanDefend(player->getOwnedTerritories()[i]))
			player->addTerritoryToDefend(player->getOwnedTerritories()[i]);
	}
	return player->getToDefend();
}

/// <summary>
/// Default constructor for AggressivePlayerStrategy
/// </summary>
AggressivePlayerStrategy::AggressivePlayerStrategy()
{
}

/// <summary>
/// Parameterized constructor for the AggrssivePlayerStrategy taking in a player
/// </summary>
/// <param name="player">The player using the strategy</param>
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) : PlayerStrategy(player)
{
	this->player = player;
}

/// <summary>
/// Destructor for AggressivePlayerStrategy
/// </summary>
AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
}

/// <summary>
/// Copy constructor for AggressivePlayerStrategy
/// </summary>
/// <param name="c">The AggressivePlayerStrategy being copied</param>
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &c)
{
	player = c.player;
}

/// <summary>
/// Overloaded = operator for the AggressivePlayerStrategy class
/// </summary>
/// <param name="c">The AggressivePlayerStrategy being assigned</param>
/// <returns>A new AggressivePlayerStrategy identical to c</returns>
AggressivePlayerStrategy &AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &c)
{
	player = c.player;
	return *this;
}

/// <summary>
/// Issue an order as a Aggressive player
/// </summary>
void AggressivePlayerStrategy::issueOrder()
{
	int territoryChoice, territoryChoice2, cardChoice;
	int armyChoice;
	int playerInput = 0;
	int advanceChoice;
	vector<Card *> cards;
	cout << "\nPlayer " << player->getPlayerName() << "'s turn" << endl;
	if (player->getReinforcementPool() != 0)
	{
		cout << "These are the territories that the aggressive player can deploy armies in (sorted by the strongest)" << endl;
		for (int i = 0; i < player->getToDefend().size(); i++)
		{
			cout << i << " " << player->getToDefend()[i]->getName() << " " << player->getToDefend()[i]->getArmyValue() << endl;
		}
		territoryChoice = 0;
		armyChoice = player->getReinforcementPool();
		cout << "Player chose to reinforce it's strongest territory with " << armyChoice << " armies!!" << endl;
		player->getOrders()->addOrder(new DeployOrder(*player, *(player->getToDefend())[territoryChoice], armyChoice));
		player->setReinforcementPool(player->getReinforcementPool() - armyChoice);
		if (player->getReinforcementPool() < 0)
			player->setReinforcementPool(0);
		return;
	}
	//Players issues advance orders to either attack their neighboring enemies or deploy to their neighboring owned territories
	cout << "These are the territories that the aggressive player can advance to attack:" << endl;
	territoryChoice2 = 0;
	if(player->getToAttack().size()>0){
		for (int i = 0; i < player->getToAttack().size(); i++)
		{
			cout << i << " " << player->getToAttack()[i]->getName() << " " << player->getToAttack()[i]->getArmyValue() << endl;
		}
		territoryChoice = 0;
		cout << "These are the territories that can attack (sorted by the strongest)" << endl;
		for (int i = 0; i < player->getToDefend().size(); i++)
		{
			cout << i << " " << player->getToDefend()[i]->getName() << " " << player->getToDefend()[i]->getArmyValue() << endl;
		}
		cout << "The aggressive player chose to attack " << territoryChoice << endl;
		armyChoice = player->getToDefend()[territoryChoice2]->getArmyValue();
		player->getOrders()->addOrder(new AdvanceOrder(*player, *(player->getToDefend())[territoryChoice2], *player->getToAttack()[territoryChoice], armyChoice));

	}else{
		cout << "Strongest territory has no other territory to attack." << endl;
		cout << "These are the territories that can be deployed to from the strongest" << endl;
		int maximum = player->getToDefend()[0]->getBorders()[0]->getArmyValue();
		territoryChoice = 0;
		for (int i = 0; i < player->getToDefend()[0]->getBorders().size(); i++)
		{
			cout << i << " " << player->getToDefend()[0]->getBorders()[i]->getName() << " " << player->getToDefend()[0]->getBorders()[i]->getArmyValue() << endl;
			if (player->getToDefend()[0]->getBorders()[i]->getArmyValue() > maximum)
			{
				maximum = player->getToDefend()[0]->getBorders()[i]->getArmyValue();
				territoryChoice = i;
			}
		}
		cout << "The aggressive player chose to move his army to "<< territoryChoice << endl;
		armyChoice = player->getToDefend()[territoryChoice2]->getArmyValue();
		player->getOrders()->addOrder(new AdvanceOrder(*player, *(player->getToDefend())[territoryChoice2], *player->getToDefend()[0]->getBorders()[territoryChoice], armyChoice));
	}
	player->setIsTurnFinish(true);
}

/// <summary>
/// Get's the territories that the Aggressive player can attack
/// </summary>
/// <returns>The territories the player can attack</returns>
vector<Territory *> AggressivePlayerStrategy::toAttack()
{
	vector<Territory *> territoryList = *new vector<Territory *>();
	player->setCanAttack(territoryList);
		for (int j = 0; j < player->getToDefend()[0]->getBorders().size(); j++)
			if (!player->playerCanDefend(player->getToDefend()[0]->getBorders()[j]))
				if (!player->playerCanAttack(player->getToDefend()[0]->getBorders()[j]))
					player->addTerritoryToAttack(player->getToDefend()[0]->getBorders()[j]);
	return player->getToAttack();
}

/// <summary>
/// Get's the territories that the Aggressive player can defend
/// </summary>
/// <returns>The territories the player can defend</returns>
vector<Territory *> AggressivePlayerStrategy::toDefend()
{
	vector<Territory *> territoryList = *new vector<Territory *>();
	int maximum = player->getOwnedTerritories()[0]->getArmyValue();
	for (int i = 1; i < player->getOwnedTerritories().size(); i++)
	{
		if (player->getOwnedTerritories()[i]->getArmyValue() > maximum)
			maximum = player->getOwnedTerritories()[i]->getArmyValue();
	}
	for (int i = 0; i < player->getOwnedTerritories().size(); i++)
	{
		if (player->getOwnedTerritories()[i]->getArmyValue() == maximum)
		territoryList.insert(territoryList.begin(), player->getOwnedTerritories()[i]);
		else{
		territoryList.push_back(player->getOwnedTerritories()[i]);
		}
	}
	player->setCanDefend(territoryList);
	return player->getToDefend();
}

/// <summary>
/// Default constructor for BenevolentPlayerStrategy
/// </summary>
BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{
}

/// <summary>
/// Parameterized constructor for BenevolentPlayerStrategy taking in a Player*
/// </summary>
/// <param name="player">The Player using the BenevolentPlayerStrategy</param>
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player) : PlayerStrategy(player)
{
	this->player = player;
}

/// <summary>
/// Destructor for the BenevolentPlayerStrategy
/// </summary>
BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
}

/// <summary>
/// Copy constructor for the BenevolentPlayerStrategy
/// </summary>
/// <param name="c">The BenevolentPlayerStrategy being copied</param>
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy &c)
{
	player = c.player;
}

/// <summary>
/// Overloaded = operator for the BenevolentPlayerStrategy class
/// </summary>
/// <param name="c">The BenevolentPlayerStrategy being assigned</param>
/// <returns>A new BenevolentPlayerStrategy identical to c</returns>
BenevolentPlayerStrategy &BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy &c)
{
	player = c.player;
	return *this;
}

/// <summary>
/// Issue an order as a Benevolent player
/// </summary>
void BenevolentPlayerStrategy::issueOrder()
{
	int territoryChoice;
	int armyChoice;
	cout << "\nPlayer " << player->getPlayerName() << "'s turn" << endl;
	cout << "These are the weakest territories that the benevolent player can deploy armies in" << endl;
	for (int i = 0; i < player->getToDefend().size(); i++)
	{
		cout << i << " " << player->getToDefend()[i]->getName() << " " << player->getToDefend()[i]->getArmyValue() << endl;
	}
	territoryChoice = 0;
	armyChoice = player->getReinforcementPool();
	cout << "Player chose to reinforce it's weakest territory with " << armyChoice << " armies!!" << endl;
	if(player -> getToDefend().size() > 0)
		player->getOrders()->addOrder(new DeployOrder(*player, *(player->getToDefend())[territoryChoice], armyChoice));
	player->setReinforcementPool(player->getReinforcementPool() - armyChoice);
	if (player->getReinforcementPool() < 0)
		player->setReinforcementPool(0);
	player->setIsTurnFinish(true);
}

/// <summary>
/// Get's the territories that the Benevolent player can attack
/// </summary>
/// <returns>The territories the player can attack</returns>
vector<Territory *> BenevolentPlayerStrategy::toAttack()
{
	vector<Territory *> territoryList = *new vector<Territory *>();
	player->setCanAttack(territoryList);
	return player->getToAttack();
}

/// <summary>
/// Get's the territories that the Benevolent player can defend
/// </summary>
/// <returns>The territories the player can defend</returns>
vector<Territory *> BenevolentPlayerStrategy::toDefend()
{
	vector<Territory *> territoryList = *new vector<Territory *>();
	player->setCanDefend(territoryList);
	int minimum = player->getOwnedTerritories()[0]->getArmyValue();
	for (int i = 1; i < player->getOwnedTerritories().size(); i++)
	{
		if (player->getOwnedTerritories()[i]->getArmyValue() < minimum)
			minimum = player->getOwnedTerritories()[i]->getArmyValue();
	}
	for (int i = 0; i < player->getOwnedTerritories().size(); i++)
	{
		if (!player->playerCanDefend(player->getOwnedTerritories()[i]) && player->getOwnedTerritories()[i]->getArmyValue() == minimum)
			player->addTerritoryToDefend(player->getOwnedTerritories()[i]);
	}
	return player->getToDefend();
}
