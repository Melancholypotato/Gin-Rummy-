#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"

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
void Deck::shuffleDeck(){ //shuffles the deck
   for(int i = 0; i < 52; ++i){
       int random = (rand() % 52);
       Card temp = decks[i];
       decks[i] = decks[random];
       decks[random] = temp;

   }
}
void Deck::dealCard(){ //right now all this does is output the cards
    for(int i = 0; i < 52; ++i){
        cout << this->decks[i] << endl;
    }

}
int main(){
    srand(time(0)); //creates a random seed dependent on time
    Deck theDeck; //creates a new deck of 52 cards
    theDeck.shuffleDeck(); //shuffles the deck to have random values
    theDeck.dealCard(); //right now outputs all the cards

}

