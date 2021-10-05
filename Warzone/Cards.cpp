/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include "Cards.h"

using namespace std;

const int CARDS = 5;

//Card Constructor
Card::Card()
{
}

//Card Destructor
Card::~Card()
{
}

//Constructor with a string parameter
Card::Card(string c)
{
    this->type = c;
}

//Copy constructor
Card::Card(const Card &c)
{
    this->type = c.type;
}

//method to play a card
void Card::play()
{
    cout << type << " card is being played" << endl;
}

// method to return the card type
string Card::getCardType()
{
    return type;
}

//Constructor to create a deck of cards
Deck::Deck()
{
    string type[] = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"};

    for (int count = 0; count < CARDS; count++)
    {
        deckOfCards.push_back(new Card(type[count % 5]));
    }
    cout << "A deck of " << CARDS << " cards has been created" << endl;
}

//Destructor for a deck of cards
Deck::~Deck()
{
}

// Draws card from deck
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

// method to show the current card deck
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

// returns the card back into the deck
void Deck::returnCardToDeck(Card *c)
{
    deckOfCards.push_back(c);
    cout << c->getCardType() << " card is back in the deck" << endl;
}

// hand constructor
Hand::Hand()
{
}

// hand destructor
Hand::~Hand()
{
}

// method to select a card and putting it in the players hand
void Hand::selectCard(Card *c)
{
    playersHand.push_back(c);
}

// method to remove card from players hand
Card *Hand::removeCardFromHand(int i)
{
    Card *c = playersHand.at(i);
    playersHand.erase(playersHand.begin() + i);
    cout << c->getCardType() << " has been removed from hand" << endl;
    return c;
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