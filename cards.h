//create a deck of 52 cards//
//There are four suits --Diamonds, Spaces, Clubs, and Hearts
//There are 13 cards of each suit
//Can store these in a vector
#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <vector>
using namespace std;


class Card{
    private:
        int suit; //H (Hearts), S (Spades), D (diamonds), C (clubs) 
        int value; 
    public:
        static const int totalSuit = 4; //There are four suits
        static const int cardsPerSuit = 13; //There are 13 cards per suit

        static const string names[cardsPerSuit]; //Defines card name for os operator
        static const string namesSuit[totalSuit]; //Defines card suit for os operator

        Card(int value, int suit); //constructor 
        Card(); //default constructor for superclass

        int getValue();  //getter function 
        void setValue(int value);  //setter function 

        int getSuit(); 
        void setSuit(int suit);
    

        bool operator<(const Card& card); //setting up comparision operators
        bool operator>(const Card& card); //All virtual to allow for polymorphism
        bool operator==(const Card& card); //there will be a class for each suit

    friend ostream& operator<<(ostream& os, const Card& card);
};
#endif