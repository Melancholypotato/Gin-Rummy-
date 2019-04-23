#include <iostream>
#include <vector>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "player.h"
using namespace std;

Deck::Deck(){
    vector<Card> tempDeck;
    for(int i = 0; i < Card::cardsPerSuit; ++i){
        for(int j = 0; j < Card::totalSuit; ++j){
            tempDeck.push_back(Card(i, j));
            }
    }
    //assigns temp variable to deck
    decks = tempDeck;
    cout << "Deck Created full " << decks.size() << " cards"<< endl;
}
void Deck::shuffleDeck()
{ //shuffles the deck
    vector<Card> tempDeck = decks;                      // <----------Adjusted the function so that it will shuffle the cards no matter what size the deck is in play-time
    for(int i = 0; i < tempDeck.size(); ++i){
       int random = ( rand() % (tempDeck.size()) );
       Card temp = tempDeck[i];
       tempDeck[i] = tempDeck[random];
       tempDeck[random] = temp;
    }
    decks = tempDeck;
}
Card Deck::dealCard()
{ //right now all this does is output the cards
    Card temp = decks[0];
    cout << "Drawing card " << endl;
    decks.erase(decks.begin()+0);
    cout << "Deck size is now " << decks.size() << endl;

    return temp;
}

/*
int main(){
    srand(time(0)); //creates a random seed dependent on time
    Deck theDeck; //creates a new deck of 52 cards
    theDeck.shuffleDeck(); //shuffles the deck to have random values
    theDeck.dealCard(); //right now outputs all the cards
}
*/