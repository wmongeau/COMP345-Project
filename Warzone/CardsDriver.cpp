/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>

using namespace std;
#include "Cards.h"

int main(){
    // creates a deck of cards of all different kinds
    Deck* deck = new Deck();
    deck->showDeck();
    // hand object that is filled by drawing cards from the deck
    Hand* hand = new Hand();

    //drawing cards at random from the cards remaining in the deck
    Card* first = deck->draw();
    hand->selectCard(first);

    Card* second = deck->draw();
    hand->selectCard(second);

    Card* third = deck->draw();
    hand->selectCard(third);

    //showing the current hand
    hand->showHand();
    // showing the current deck
    deck ->showDeck();

    // playing the first card
    first ->play();
    // card is removed from the hand
    Card* check=hand->removeCardFromHand(0);
    // card is returned back to the deck
    deck->returnCardToDeck(check);
    // showing the current hand
    hand->showHand();
    // showing the deck of the current hand
    deck ->showDeck();
    }