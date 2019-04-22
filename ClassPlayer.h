#include <iostream>
#include <vector>
#include "deck.h"
#include "card.h"
#include <string>

using namespace std;

class Player {
	public:
		Deck* hand;
		string name;
		
		int score;
		Player();
		Player(string name);
		Player(Deck* hand, int score);
		Deck* getHand();
		void Knock();
		void ShowName();
		void FirstHand(Deck *deck);
		void ViewHand();
		bool CheckHand();
		void SubtractCards();	
};
