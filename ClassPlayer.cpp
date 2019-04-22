#include "player.h"
#include <string>
using namespace std;

// Player
Player::Player() {
	hand= {};
	score = 0;
}

					//Initilize player with a Name
Player::Player(string nam){
	name = nam;
	hand = new Deck();
}

						//showw score
Player::Player(Deck* currentHand, int currentScore) {
	hand = currentHand;
	score = currentScore;
}

						//How many cards each player draw each new game
void Player::FirstHand(Deck *target) {
	for (int k = 0; k < 7; k++) {
		hand->addCard(target->drawCard());
	}
}

							//Show the Players cards
void Player::ViewHand() {
	hand->displayStack();
}

					//Get the player's hand
Deck* Player::getHand(){
	return hand;
}

						//Show the players name
void Player::ShowName(){
	cout << name << endl;
}

						//Checks the players hand
bool Player::CheckHand() {
	if (hand->deckSize() == 0) {
		return true;
	}
	else {
		return false;
	}
}

