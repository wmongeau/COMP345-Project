#include "./Headers/strategy.h"
#include <iostream>
Human::Human()
{
	p = NULL;
}

Human::Human(Player* p)
{
	this->p = new Player(*p);
}

Human::Human(Human* human)
{
	p = new Player(*human->getPlayer());
}

Player* Human::getPlayer()
{
	return p;
}

void Human::issueOrder()
{
	int territoryChoice, territoryChoice2, cardChoice;
	int armyChoice;
	int playerInput = 0;
	int advanceChoice;
	vector<Card*> cards;
	cout << "\nPlayer " << p->getPlayerName() << "'s turn" << endl;
	//Deploying phase. Shows all the territories that the user owns and can deploy to. 
	//As long as the player has armies still to deploy (see startup phase and reinforcement phase), it will issue a deploy order and no other order. 
	//Once it has deployed all its available armies, it can proceed with other kinds of orders.
	if (p->getReinforcementPool() != 0)
	{
		cout << "These are the territories that you can deploy armies in" << endl;
		for (int i = 0; i < p->getOwnedTerritories().size(); i++)
		{
			cout << i << " " << p->getOwnedTerritories()[i]->getName() << " " << p->getOwnedTerritories()[i]->getArmyValue() << endl;
		}
		cout << "Which territory do you want to deploy armies to?" << endl;
		cin >> territoryChoice;
		cout << "How many armies would you like to deploy of " << p->getReinforcementPool() << " armies ?";
		cin >> armyChoice;
		p->getOrders()->addOrder(new DeployOrder(*p, *p->getOwnedTerritories()[territoryChoice], armyChoice));
		p->setReinforcementPool(p->getReinforcementPool()- armyChoice);
		if (p->getReinforcementPool() < 0)
			p->setReinforcementPool(0);
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
		for (int i = 0; i < p->getOwnedTerritories().size(); i++)
		{
			cout << i << " " << p->getOwnedTerritories()[i]->getName() << " " << p->getOwnedTerritories()[i]->getArmyValue() << endl;
		}
		cout << "Which territory do you want to take armies from?" << endl;
		cin >> territoryChoice2;
		cout << "How many armies would you like to advance of " << p->getOwnedTerritories()[territoryChoice2]->getArmyValue() << " armies ?";
		cin >> armyChoice;
		if (advanceChoice == 0)
		{
			p->getOrders()->addOrder(new AdvanceOrder(*p, *p->getOwnedTerritories()[territoryChoice2], *toAttack()[territoryChoice], armyChoice));
		}
		else if (advanceChoice == 1)
		{
			p->getOrders()->addOrder(new AdvanceOrder(*p, *p->getOwnedTerritories()[territoryChoice2], *toDefend()[territoryChoice], armyChoice));
		}
	}
	else if (playerInput == 1)
	{
		// The player uses one of the cards in their hand to issue an order that corresponds to the card in question
		cout << "Here's the cards in hand:" << endl;
		cards = p->getPlayerHand()->getPlayerHand();
		for (int i = 0; i < cards.size(); i++)
		{
			cout << i << ' ' << cards[i]->getCardType() << endl;
		}
		cout << "Which card do you want to play?" << endl;
		cin >> cardChoice;
		cards[cardChoice]->setCardParameter(p);
		if (cards[cardChoice]->getCardType() == "Diplomacy" || cards[cardChoice]->getCardType() == "Blockade")
			cards[cardChoice]->playerList = p->getEnemies();
		p->getOrders()->addOrder(cards[cardChoice]->play());
	}
	else if (playerInput == 2)
		p->setIsTurnFinish(true);
}

vector<Territory*> Human::toAttack()
{

}

vector<Territory*> Human::toDefend()
{

}

