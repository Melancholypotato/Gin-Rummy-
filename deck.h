#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector> 
#include "cards.h"
#include <ctime>
#include <stdlib.h>

class Deck{
    private:
        vector<Card> decks;
    public:
        Deck();
        int size() {return decks.size();}
        void shuffleDeck(); //shuffle deck
        Card dealCard(); //should deal a card and remove card
};

#endif