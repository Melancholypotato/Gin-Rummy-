//create a deck of 52 cards//
//There are four suits --Diamonds, Spaces, Clubs, and Hearts
//There are 13 cards of each suit
//Can store these in a vector

#include <iostream>
#include <vector>
#include "cards.h"
using namespace std;

const string Card::names[cardsPerSuit] = {"Two", "Three", "Four", "Five", 
"Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
const string Card::namesSuit[totalSuit] = {"Diamonds", "Clubs", "Hearts", "Spades"};

Card::Card(){

}
Card::Card(int value, int suit){ //this is required so major bugs dont happen
    this->value = value;
    this->suit = suit;
}
int Card::getValue(){ //getter function for the value
     return value;
}
void Card::setValue(int value){ //setter function if needed (value, returns number)
    this->value = value;
}
int Card::getSuit(){ //getter function if needed (suit, returns number)
    return suit;
}
void Card::setSuit(int suit){ //setter function if needed (sets suit as a number)
    this->suit = suit;
}
bool Card::operator<(const Card& card){ //compares if one value is less
    if(this->value < card.value)
        return true;
    else
        return false;
}
bool Card::operator>(const Card& card){ //compares if one value is greater
    if(this->value > card.value)
        return true;
    else
        return false;
}
bool Card::operator==(const Card& card){ //compares if values are equal
    if(this-> value == card.value)
        return true;
    else
        return false;
}        
ostream& operator<<(ostream& os, const Card& card){ //output text
    os << card.names[card.value] << " of " << card.namesSuit[card.suit];
    return os;
    
}
bool sameSuit(Card c1, Card c2){ //compares suits
    if(c1.getSuit() == c2.getSuit())
        return true;
    else
        return false;
}
