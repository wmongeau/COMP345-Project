#pragma once
#include <string>
#include <vector>
#include "Orders.h"


using namespace std;
class Deck;
namespace CardTypeEnums{
//enum of card types
enum cardType {Bomb, Reinforcement, Blockade, Airlift, Diplomacy};
// method to convert card types to strings
string cardTypeEnumToString(cardType value);
}
class Card
{
public:
    Deck* deck;
    vector<Player*> playerList;
    //constructor
    Card();
    //destructor
    ~Card();
    //copy constructor
    Card(const Card &c);
    //assignment operator
    Card &operator=(const Card &c);
    //stream insertion operator
    friend ostream& operator<<(ostream& os, const Card& c);
    //parametrized card constructor
    Card(CardTypeEnums::cardType);
    //plays the card
    Order* play();
    //Setup parameter for card
    void setCardParameter(Player* player);
    //returns the card type
    string getCardType();
private:
    //card type
    CardTypeEnums::cardType type;
    Territory* targetTerritory;
    Territory* sourceTerritory;
    Player* targetPlayer;
    Player* sourcePlayer;
    int amount;
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
    //stream insertion operator
    friend ostream& operator<<(ostream& os, const Deck& d);
    // method to draw a card from the deck
    Card *draw();
    // method to return the card back to the deck
    void returnCardToDeck(Card *c);
    // method to show the deck
    void showDeck();
    // method to get the deck of cards
    vector<Card*> getDeckOfCards();
private:
    //deck of cards
    vector<Card *> deckOfCards;
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
    //stream insertion operator
    friend ostream& operator<<(ostream& os, const Hand& h);
    //method to remove the card from the hand
    Card *removeCardFromHand(int i);
    //method to select a card
    void selectCard(Card *c);
    //method to show your current hand
    void showHand();
    //method to get the players hand
    vector<Card*> getPlayerHand();
private:
    //players hand
    vector<Card*> playersHand;
};
