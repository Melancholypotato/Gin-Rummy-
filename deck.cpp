#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"

using namespace std;

Deck::Deck(){
    srand(time(0)); //creates a random seed dependent on time
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
Card Deck::dealCard(){ //right now all this does is output the cards
    Card temp = decks[0];
    cout << "Drawing card " << endl;
    decks.erase(decks.begin()+0);
    cout << "Deck size is now " << decks.size() << endl;
    return temp;

}
int Deck::size(){
    return decks.size();
}


