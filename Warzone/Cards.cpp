/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include "./Headers/Cards.h"

using namespace std;

// ---------- Card class ---------- //
//constructor
Card::Card()
{
}
//destructor
Card::~Card()
{
}
//copy constructor
Card::Card(const Card &c)
{
    this->type = c.type;
}
//assignment operator
Card& Card::operator=(const Card& c){
    type = c.type;
    return *this;
}

//stream insertion operator
ostream& operator<<(ostream& os, const Card& c){
    os << CardTypeEnums::cardTypeEnumToString(c.type);
	return os;
}

//parametrized card constructor
Card::Card(CardTypeEnums::cardType c){
    this->type=c;
}

//method to play a card
Order* Card::play()
{
    cout << CardTypeEnums::cardTypeEnumToString(type) << " card is being played" << endl;
    switch (type)
    {
    case CardTypeEnums::Bomb:
        return new BombOrder();
        break;
    case CardTypeEnums::Reinforcement:
        return new DeployOrder();
        break;
    case CardTypeEnums::Blockade:
        return new BlockadeOrder();
        break;
    case CardTypeEnums::Airlift:
        return new AirliftOrder();
        break;
    case CardTypeEnums::Diplomacy:
        return new NegotiateOrder();
        break;
    default:
        break;
    }
    
    return NULL;
}

void Card::setCardParameter(Player* player)
{
	int territoryChoice, territoryChoice2, cardChoice, diplomatChoice;
	int armyChoice;
    switch(type)
		switch (type)
		{
		case CardTypeEnums::Bomb:
			cout << "These are the territories that you can us bomb on" << endl;
			for (int i = 0; i < player->toAttack().size(); i++)
			{
				cout << i << " " << player->toAttack()[i]->getName() << " " << player->toAttack()[i]->getArmyValue() << endl;
			}
			cout << "Which territory do you want to bomb?" << endl;
			cin >> territoryChoice;
            targetTerritory = player->toAttack()[territoryChoice];
			break;
		case CardTypeEnums::Reinforcement:
			cout << "These are the territories that you can reinforcement armies in" << endl;
			for (int i = 0; i < player->toDefend().size(); i++)
			{
				cout << i << " " << player->toDefend()[i]->getName() << " " << player->toDefend()[i]->getArmyValue() << endl;
			}
			cout << "Which territory do you want to reinforcement armies to of 3?" << endl;
			cin >> territoryChoice;
			targetTerritory = player->toDefend()[territoryChoice];
            amount = 3;
			break;
		case CardTypeEnums::Blockade:
			cout << "These are the territories that you can use blockade on" << endl;
			for (int i = 0; i < player->toDefend().size(); i++)
			{
				cout << i << " " << player->toDefend()[i]->getName() << " " << player->toDefend()[i]->getArmyValue() << endl;
			}
			cout << "Which territory do you want to add blockade?" << endl;
			cin >> territoryChoice;
            targetTerritory = player->toDefend()[territoryChoice];
			break;
		case CardTypeEnums::Airlift:
			cout << "These are the territories that you can airlift to defend" << endl;
			for (int i = 0; i < player->toDefend().size(); i++)
			{
				cout << i << " " << player->toDefend()[i]->getName() << " " << player->toDefend()[i]->getArmyValue() << endl;
			}
			cout << "Which territory do you want to airlift armies to?" << endl;
			cin >> territoryChoice;
			cout << "These are the territories that you can take armies from" << endl;
			for (int i = 0; i < player->getOwnedTerritories().size(); i++)
			{
				cout << i << " " << player->getOwnedTerritories()[i]->getName() << " " << player->getOwnedTerritories()[i]->getArmyValue() << endl;
			}
			cout << "Which territory do you want to take armies from?" << endl;
			cin >> territoryChoice2;
			cout << "How many armies would you like to airlift of " << player->getOwnedTerritories()[territoryChoice2]->getArmyValue() << " armies ?";
			cin >> armyChoice;
            sourceTerritory = player->getOwnedTerritories()[territoryChoice2];
            targetTerritory = player->toDefend()[territoryChoice];
            amount = armyChoice;
			break;
        case CardTypeEnums::Diplomacy:
            cout << "Which player do you want use diplomacy?" << endl;
			for (int i = 0; i < player->getEnemies().size(); i++)
			{
				cout << i << " " << player->getEnemies()[i]->getPlayerName() << endl;
			}
            cin >> diplomatChoice;
            targetPlayer = player->getEnemies()[diplomatChoice];
			break;
		default:
			break;
		}
}

//method to return the card type
string Card::getCardType()
{
    return CardTypeEnums::cardTypeEnumToString(type);
}

//method to convert card types to strings
string CardTypeEnums::cardTypeEnumToString(CardTypeEnums::cardType value){
	switch (value){
		case CardTypeEnums::Bomb: {
			return "Bomb" ;
	     	}
		case CardTypeEnums::Reinforcement: {
			return "Reinforcement" ;
	     	}
		case CardTypeEnums::Blockade: {
			return "Blockade" ;
	     	}
		case CardTypeEnums::Airlift: {
			return "Airlift" ;
	     	}
		case CardTypeEnums::Diplomacy: {
			return "Diplomacy" ;
	     	}
	}
	return "Error";
}
// ---------- Deck class ---------- //
//constructor to create a deck of cards
Deck::Deck()
{
CardTypeEnums::cardType typelist[] ={CardTypeEnums::Bomb,CardTypeEnums::Reinforcement,CardTypeEnums::Blockade,CardTypeEnums::Airlift,CardTypeEnums::Diplomacy};
    const int CARDS = 50;
    for (int count = 0; count < CARDS; count++)
    {
        deckOfCards.push_back(new Card(typelist[count % 5]));
    }
    cout << "A deck of " << CARDS << " cards has been created" << endl;
}

//destructor for a deck of cards
Deck::~Deck()
{
    for (auto p : deckOfCards) {
        delete p;
        p = NULL;
    }
}
//copy constructor
Deck::Deck(const Deck &d)
{
    this->deckOfCards = d.deckOfCards;
}
//assignment operator
Deck& Deck::operator=(const Deck& d){
    this->deckOfCards = d.deckOfCards;
    return *this;
}
//stream insertion operator
ostream& operator<<(ostream& os, const Deck& d){
    os << "There is " << d.deckOfCards.size() << " cards in the deck."<<endl;
	return os;
}

// method to draw a card from the deck
Card *Deck::draw()
{

    // shuffling the deck
    srand((unsigned)time(0));
    for (int i = 0; i < deckOfCards.size(); i++)
    {
        // finds a random value in the deck of card range
        int j = rand() % deckOfCards.size();
        //shuffles the two cards
        Card *temp = deckOfCards[i];
        deckOfCards[i] = deckOfCards[j];
        deckOfCards[j] = temp;
    }
    // remove the last card in the deck and returns it
    Card *lastCard = deckOfCards.back();
    Card *drawCard = new Card(*lastCard);
    deckOfCards.pop_back();
    delete lastCard;
    return drawCard;
}

// method to return the card back to the deck
void Deck::returnCardToDeck(Card *c)
{
    deckOfCards.push_back(c);
    cout << c->getCardType() << " card is back in the deck" << endl;
}

// method to show the deck
void Deck::showDeck()
{
    cout << "------- CURRENT DECK -------" << endl;
    // iterates through all the cards in the deck and prints their card type
    for (int i = 0; i < deckOfCards.size(); i++)
    {
        cout << i << " " << this->deckOfCards.at(i)->getCardType() << endl;
    }
    cout << "----------------------------" << endl;
}
// method to get the deck of cards
vector<Card*> Deck::getDeckOfCards()
{
    return deckOfCards;
}

// ---------- Hand class ---------- //
// constructor
Hand::Hand()
{
}
// destructor
Hand::~Hand()
{
    for (auto p : playersHand) {
        delete p;
        p = NULL;
    }
}
//copy constructor
Hand::Hand(const Hand &h)
{
    this->playersHand = h.playersHand;
}
//assignment operator
Hand& Hand::operator=(const Hand& h){
    this->playersHand = h.playersHand;
    return *this;
}
//stream insertion operator
ostream& operator<<(ostream& os, const Hand& h){
    os << "There is " << h.playersHand.size() << " cards in the players hand."<<endl;
	return os;
}

// method to remove card from players hand
Card *Hand::removeCardFromHand(int i)
{
    Card *c = playersHand.at(i);
    playersHand.erase(playersHand.begin() + i);
    cout << c->getCardType() << " has been removed from hand" << endl;
    return c;
}

// method to select a card and putting it in the players hand
void Hand::selectCard(Card *c)
{
    playersHand.push_back(c);
}

// method to show the players current hand
void Hand::showHand()
{
    cout << "------- CURRENT HAND -------" << endl;
    // iterates through each card in the players hand and prints it's type
    for (int i = 0; i < playersHand.size(); i++)
    {
        cout << i << " " << this->playersHand.at(i)->getCardType() << endl;
    }
    cout << "----------------------------" << endl;
}
//method to get the players hand
vector<Card*> Hand::getPlayerHand()
{
    return playersHand;
}
