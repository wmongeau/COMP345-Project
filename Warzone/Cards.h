#pragma once
#include <string>
#include <vector>

using namespace std;

class Card {
    public:
        //constructor
        Card();
        //destructor
        ~Card();
        //copy constructor
        Card(const Card& c);
        //assignment operator
        Card& operator =(const Card& c);
        //stream insertion operator
        Card(string c);
        void play();
        string getCardType();
    private:
        string type;
};

class Deck {
    public:
        Deck();
        ~Deck();
        Deck(const Deck& d);
        Deck& operator = (const Deck& d);
        vector <Card*> deckOfCards;
        Card* draw();
        void returnCardToDeck(Card* c);
        void showDeck();
    
};

class Hand {
    public:
        Hand();
        ~Hand();
        Hand(const Hand& h);
        Hand& operator = (const Hand& h);
        vector <Card*> playersHand;
        Card* removeCardFromHand(int i);
        void selectCard(Card* c);
        void showHand();
};