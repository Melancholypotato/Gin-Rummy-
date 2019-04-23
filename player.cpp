#include "player.h"
#include "cards.h"
#include "deck.h"
#include <string>
using namespace std;

// Player
Player::Player() {
	hand = {};
	score = 0;
}

					//Initilize player with a Name
Player::Player(string nam){
	name = nam;
	hand = {};
}

						//showw score
Player::Player(vector<Card> currentHand, int currentScore) {
	hand = currentHand;
	score = currentScore;
}

void Player::add_card(Card c)
{
    hand.push_back(c);
}

						//How many cards each player draw each new game
/*
void Player::FirstHand(Deck *target) {
	for (int k = 0; k < 7; k++) {
		hand.push_back(target->drawCard());                 <--------------NOTE: This function is included within the 'Deck's' header file.
	}
}
*/
							//Show the Players cards
void Player::ViewHand() 
{
	/*hand->displayStack();                     <----------------- NOTE: using pointers in a code where no one else used pointers will make the pointers behave weirdly. Basically, I don't like pointers.*/
    /* Show on game board via string indexing */
}

/*
					//Get the player's hand
Deck* Player::getHand(){
	return hand;
}
*/

vector<Card> Player::getHand()
{
    return hand;
}
						//Show the players name
void Player::ShowName()
{
	cout << name << endl;
}

						//Checks the players hand
bool Player::CheckHand(/*Deck &d*/) {
	if (hand.size() == 0)
    {
		return true;
	}
	else 
    {
		return false;
	}
}