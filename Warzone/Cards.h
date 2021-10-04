#pragma once
#include <string>
#include <vector>

using namespace std;
class Card
{
public:
    //constructor
    Card();
    //destructor
    ~Card();
    //copy constructor
    Card(const Card &c);
    //assignment operator
    Card &operator=(const Card &c);
    //parametrized card constructor
    Card(string c);
    //plays the card
    void play();
    //returns the card type
    string getCardType();
private:
    //card type
    string type;
};
class Deck
{
public:
    //constructor
    Deck();
    //destructor
    ~Deck();
    //copy constructor
    Deck(const Deck &d);
    //assignment operator
    Deck &operator=(const Deck &d);
    //deck of cards
    vector<Card *> deckOfCards;
    // method to draw the card
    Card *draw();
    // method to return the card back to the deck
    void returnCardToDeck(Card *c);
    // method to show the deck
    void showDeck();
};

class Hand
{
public:
    //constructor
    Hand();
    //destructor
    ~Hand();
    //copy constructor
    Hand(const Hand &h);
    //assignment operator
    Hand &operator=(const Hand &h);
    //players hand
    vector<Card *> playersHand;
    //method to remove the card from the hand
    Card *removeCardFromHand(int i);
    void selectCard(Card *c);
    void showHand();