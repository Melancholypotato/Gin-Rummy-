#ifndef PLAYER_H
#define PLAYER_H  //Added appropriate Header files to compile (1:17am)

#include <iostream>
#include <vector>
#include "deck.h"
#include "cards.h"
#include <string>
using namespace std;

class Player {
	public:
		vector<Card> hand;                         // NOTE: Changed to card vector (1:40am)
		string name;

		int score;
		Player();
		Player(string name);
		Player(vector<Card> h, int score); //changed Deck* to vector<Card>
		//Deck* getHand();                        <--------NOTE: Unsure what this was meant to do. (Commented out 1:15am)
		vector<Card> getHand();                    // NOTE: added function as a replacement for 'Deck* getHand();' since we're using vectors now. (9:08am)
        int handSize() {return hand.size();}
		void Knock();
		void ShowName();
		//void FirstHand(Deck *deck);             <--------NOTE: This function is included in 'deck's' header file. (Commented out 9:15am)
		void ViewHand();
		bool CheckHand(/*Deck &d*/);              // NOTE: Changed to check whether or not there are cards in hand
        void add_card(Card c);            // NOTE: added a way to add cards to the 'hand' vector (3:48pm)
		void SubtractCards();	
};

#endif