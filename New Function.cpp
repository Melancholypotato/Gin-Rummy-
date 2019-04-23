#include <iostream>
#include <algorithm>
#include "ClassPlayer.h"
#include "deck.h"
#include "player.h"
#include "cards.h"
#include "pile.h"
#include <vector>
#include <unistd.h>


//If the table is already known
Table::Table(Player* playerOne, Computer* playerTwo, Deck* drawStack, Deck* discardStack) {
	player1 = playerOne;
	player2 = playerTwo;
	drawPile = drawStack;
	discardPile = discardStack;
	cardsOnBoard = new Pile();
	ruleModifier = 0;
}

// draw card for the turn, given the player it will prompt that player where they would like to draw a card from
void Table::drawCard(Player* currentPlayer){

	//Decide whether to take top discard or top draw pile
	displayTable(currentPlayer);
	cout << "Take new card or draw from the discard pile?" <<endl;
	cout << "1. Draw new card from the Draw Pile" << endl;
	cout << "2. Take a card from the Discard Pile" << endl;

	// corrects for invlaid entry
	string choiceInput;
	cin >> choiceInput;
	int choice;
	bool fullNum;
	for(int i = 0; i < choiceInput.length(); i++){
		fullNum = isdigit(choiceInput.at(i));
	}
	if(!fullNum){
		cout << "Invalid Entry please try again" << endl;
	}else{
		choice = stoi(choiceInput);
	}
	string answer;
	switch (choice) {
		case 1:{		
			currentPlayer->hand->addCard(drawPile->drawCard());
			return;
			break;
		}
		case 2:
			drawDiscard(currentPlayer);
			return;
			break;
		default:
			cout << "Please choose an available option" << endl;
			drawCard(currentPlayer);
			break;

	}
}

//Each players turn sequence
void Table::turn(Player* currentPlayer) {
	currentPlayer->showHand();
	drawCard(currentPlayer);	
	displayTable(currentPlayer);
	playChoice(currentPlayer);
	turnDiscard(currentPlayer);
}

// funciton for placing a meld or sequence
void Table::placeNewSet(Player* currentPlayer){
	vector<Card> selectedCards;
	bool selecting = true;
	char answer;
	do{
		selectedCards.push_back(selectCard(currentPlayer));
		cout << "Continue? (Y or N)" << endl;
		cin >> answer;
		selecting =  (answer == 'Y' || answer == 'y');
	}while(selecting);
	int ruleFollowed = handFollowsRules(selectedCards);
	char id;
	switch(ruleFollowed){
		case 1:
			id = 'm';
			cardsOnBoard->addToPile(selectedCards, id, currentPlayer);			
			removeCards(selectedCards, currentPlayer);
			displayTable(currentPlayer);
			playChoice(currentPlayer);
			break;
		case 2:
			id = 's';
			cardsOnBoard->addToPile(selectedCards, id, currentPlayer);
			removeCards(selectedCards, currentPlayer);
			displayTable(currentPlayer);
			playChoice(currentPlayer);
			break;
		default:
			cout << "Your hand does not follow the rules please try again" << endl;
			sleep(1);
			selectedCards.clear();
			displayTable(currentPlayer);
			playChoice(currentPlayer);
			break;
	}
}

// utility funciton to remove cards from a players hand
void Table::removeCards(vector<Card> cards, Player* currentPlayer){
	for(int i = 0; i < cards.size(); i++){
		currentPlayer->hand->removeCard(cards.at(i));
	}
}

// funciton for adding cards to an existing pile - player must seletc the pile they wish to add their card too
void Table::addToSet(Player* currentPlayer){
	cout << "Please select a pile to add you card to:" << endl;
	cardsOnBoard->displayPiles();
	vector<Card> selectedCards;
	string selectionInput;
	// corrects for invalid input
	int selection;
	cin >> selectionInput;
	bool fullNum;
	for(int i = 0; i < selectionInput.length(); i++){
		fullNum = isdigit(selectionInput.at(i));
	}
	if(!fullNum){
		cout << "Invalid Entry please try again" << endl;
		playChoice(currentPlayer);
	}else{
		selection = stoi(selectionInput);
	}
	selection--; // changes value from 0-(size-1) 
	if(!(selection >= 0 && selection < cardsOnBoard->getPile().size())){
		cout << "Invalid Selection please try again." << endl;
		pileMaker(currentPlayer);
	}else{
		for(int i = 0; i < cardsOnBoard->getPile().at(selection)->deckSize(); i++){
			selectedCards.push_back(cardsOnBoard->getPile().at(selection)->getCards().at(i));
		}
		cout << "Please select a card you wish to add. " << endl;
		selectedCards.push_back(selectCard(currentPlayer));
	}
	int ruleFollowed = handFollowsRules(selectedCards);
	switch (ruleFollowed){
		case 1:
		case 2:
		case 3:
		case 4:
			cardsOnBoard->addCardToExist(selectedCards.at(selectedCards.size()-1), selection, currentPlayer);
			currentPlayer->hand->removeCard(selectedCards.at(selectedCards.size()-1));
			displayTable(currentPlayer);
			playChoice(currentPlayer);
			break;
		default:
			cout << "The card you have entered and the pile does not follow a rule please try again. " << endl;
			sleep(1);
			selectedCards.clear();
			playChoice(currentPlayer);
	}
}



//Edits piles and makes new piles funciton
void Table::pileMaker(Player* currentPlayer) {
		char answer ='m';
		displayTable(currentPlayer);
		cout << "Would you like to add cards to an existing pile (Y or N)" << endl;
		cin >> answer;
		if(answer == 'y' || answer == 'Y'){
			ruleModifier = 2;
			addToSet(currentPlayer);
		}
		else{
			ruleModifier = 0;
			placeNewSet(currentPlayer);
		}
}

//Asks player if they want to put anything down
void Table::playChoice(Player *currentPlayer) {
	cout << "Play cards or End Turn? (Y to Place, N to end turn) " << endl;
	char answer = 'm';
	cin >> answer;
	switch (answer){
		case 'Y':
		case 'y':
			pileMaker(currentPlayer);
			break;
		case 'N':
		case 'n':
			break;
		default:
			cout << "Invalid entry please try again" << endl;
			playChoice(currentPlayer);
	}

}

//Dsicard Card at end of turn
void Table::turnDiscard(Player* currentPlayer) {
	currentPlayer->showHand();
	displayTable(currentPlayer);
	if(currentPlayer->hand->deckSize() == 0){// violate must discard a card rule
		// add all cards from most recent pile
		cout << "You must be able to discard a card" << endl;
		sleep(2);
		int pile = cardsOnBoard->getPile().size()-1;
		cout << pile << endl;
		for(int i = 0; i < cardsOnBoard->getPile().at(pile)->deckSize(); i++){
			// add cards back to hand
			cardsOnBoard->getPile().at(pile)->getCards().at(i).displayCard();
			player1->hand->addCard(cardsOnBoard->getPile().at(pile)->getCards().at(i));
		}
		cardsOnBoard->removeRecent();
		displayTable(currentPlayer);
		playChoice(currentPlayer);
	}else{
		cout << "Now you must discard a card please select a card to discard (Enter the value, then H,C,D,S for the suit)" << endl;

	}
	Card dis(selectCard(currentPlayer));
	discardPile->addCard(dis);
	currentPlayer->hand->removeCard(dis);
}


//Selects Card utility funciton

/// Might need to change this real quick since Brian mentioned he used numbers instead of Characters 
Card Table::selectCard(Player* currentPlayer){
	cout << "Select a card (Enter the value (1-13), then H,C,D,S for the suit" << endl;
	string playerInput;
	string suitIn;
	string suit;
	cout << "The Number: ";
	cin >> playerInput;
	cout << "The suit (H,C,S,D): ";
	cin >> suitIn;
	int realInput;
	bool realNUm = true;
	for (int i = 0; i < playerInput.length(); ++i)
	{
		realNUm &= isdigit(playerInput.at(i)); 
		/* code */
	}
	if(playerInput == "A" || playerInput == "a"){
		realInput = 1;
	}else if(playerInput == "J" || playerInput == "j"){
		realInput = 11;
	}else if(playerInput == "Q" || playerInput == "q"){
		realInput = 12;
	}else if(playerInput == "K" || playerInput == "k"){
		realInput = 13;
	}else if(realNUm){
		realInput = stoi(playerInput);
	}else{
		cout << "Invalid entry" << endl;
		return selectCard(currentPlayer);
	}

	if(suitIn[0] == 'h' || suitIn[0] =='H'){
		suit = "Hearts";
	}else if(suitIn[0] == 'c' || suitIn[0] =='C'){
		suit = "Clubs";
	}else if(suitIn[0] == 'd' || suitIn[0] =='D'){
		suit = "Diamonds";
	}else if(suitIn[0] == 's' || suitIn[0] =='S'){
		suit = "Spades";
	}else{
		cout << "Invalid Entry" << endl;
		selectCard(currentPlayer);

	}
	Card target(realInput, suit);
	// search for cards in given players hand
	bool found = false;
	int i = 0;
	if(player1->hand->deckSize() == 1){
		found = true;
		return player1->hand->getCards().at(0);
	}
	for(i = 0; i < player1->hand->deckSize(); i++){
		if(target == player1->hand->getCards().at(i)){
			found = true;
			break;
		}
	}
	if(!found){
		cout << "That card was not found please try again." << endl;
		return selectCard(currentPlayer);
	}
	//displayTable(currentPlayer);
	return currentPlayer->hand->getCards().at(i);
}

// check to see if a given vectur of cards follows the rules
/*
	return
		-1 - no rules followed
		1 - is a meld
		2 - is a sequence
*/
int Table::handFollowsRules(vector<Card> selectedCards){
	sort(selectedCards.begin(), selectedCards.end());
	if(selectedCards.size() < 3){
		return -1;
	}

	bool areTheySame = true;
	for(int i = 1; i < selectedCards.size(); i++){

		areTheySame &= selectedCards[i].number == selectedCards[i-1].number;
	}
	if(areTheySame == true){
		return 1;
	}

	areTheySame = true;
	for(int i = 1; i < selectedCards.size(); i++){
		areTheySame &= selectedCards[i].suit == selectedCards[i-1].suit;
	}
	if(areTheySame == true){
		for(int i = 1; i < selectedCards.size(); i++){
			areTheySame &= selectedCards[i].number == selectedCards[i-1].number+1;
	}
	if(areTheySame == true){
		return 2;
		}
	}
	return -1;
}




//Controls how many rounds are played. and loops through all the players turns until 1 has no cards in hand hten loops till 1 hits 500 points
void Table::playGame() {
	//Number of rounds and first player
	int rounds = 5;
	int player = 1;
	bool playerWonRound = false;
	int playerScore = player1->score;
	int computerScore = player2->score;
	while(player1->score < 100 && player2->score < 100){
		while(playerWonRound == false) {
			//Player 1's turn
			if(drawPile->deckSize() == 0){
				// add all cards from discard back to deck then reshuffle
				cout << "Reshuffling" << endl;
				for(int i = 0; i < discardPile->deckSize()-1;i++){
					drawPile->addCard(discardPile->getCards().at(i));
				}
				Card topCard(discardPile->getCards().at(discardPile->deckSize()-1));
				discardPile->clear();
				discardPile->addCard(topCard);
				drawPile->shuffleDeck();
			}
			if (player == 1) {
				turn(player1);
				playerWonRound = player1->checkHand();
				player = 2;
			}
			else {
				player2->takeTurn();
				playerWonRound = player2->checkHand();
				player = 1;
			}
		}

		//Subtract points from leftover cards and resets the game
		if(player1->checkHand()){
			player2->subtractCards();
		}else{
			player1->subtractCards();
		}
		// reset board
		cardsOnBoard->clear();
		drawPile->clear();
		drawPile->newDeck();
		drawPile->shuffleDeck();
		playerScore += player1->score;
		computerScore += player2->score;
		discardPile->clear();
		player1->hand->clear();
		player2->hand->clear();
		cout << "\t\tNext Round" << endl;
		sleep(2);
		player1->firstHand(drawPile);
		player2->firstHand(drawPile);
		playerWonRound = false;
	}

	// win output statements
	if(player1->score >= 100){
		cout << "The player has won! with: "<< player1->score << " points!" << endl;
	}else if(player2->score >= 100){
		cout << "The computer has won :( with "<< player2->score << " points.." << endl;
	}else{
		if(player1->score > computerScore){
			cout << "The player has won! with: "<< player1->score << " points!" << endl;
		}else if(player2->score > player1->score){
			cout << "The computer has won :( with "<< player2->score << " points.." << endl;
		}else{
			cout << "It is  a tie with: " << player1->score << " points" << endl;
		}
	}

}

//Displays Table
void Table::displayTable(Player *currentPlayer) {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";	
 	cout << "\033[2J\033[1;1H"; //"Clear Screen"
 	cout << player1->name <<"'s Score: " << player1->score << "\t Computer Score: " << player2->score << endl;
	cout << "Played Cards" << endl;
	cardsOnBoard->displayPiles();
	cout << "Draw Pile" << endl;
	cout << "-------" << endl;
	cout << "|?    |" << endl;
	cout << "|     |" << endl;
	cout << "|     |" << endl;
	cout << "|    ?|" << endl;
	cout << "-------" << endl;
	cout << "Discard Pile" << endl;
	discardPile->displayStack();
	cout << "Computers cards" << endl;
	player2->displayComputer();
	cout << "Your Hand" << endl;
	currentPlayer->showHand();
	//Debugging Puposes
	//player2->showHand();
}

//Draws card from Discard Pile
void Table::drawDiscard(Player *currentPlayer) {
	int size = currentPlayer->hand->deckSize();
	int currentScore = currentPlayer->score;
	int num = -1;
	
	
	if (discardPile->deckSize() != 0) {
		while (num == -1) {
			displayTable(currentPlayer);
			cout << "Please select which card you would like to take: (Enter card number with 1 being on the left, counting up)" << endl;	
			cin >> num;
			int disSize = discardPile->deckSize();
			if (num <= discardPile->deckSize()) {
				for (int i = (num-1); i < disSize; i++) {
					currentPlayer->hand->addCard(discardPile->getCards().at(i));
					
				}
				int difference = size - currentPlayer->hand->deckSize();
				for(int i = currentPlayer->hand->deckSize(); i > size; i--){
					discardPile->popCard();
				}
				displayTable(currentPlayer);
				pileMaker(currentPlayer);
				if (currentPlayer->score == currentScore) {
					// remove drawn cards form hand and add back to discard
					for(int i = currentPlayer->hand->deckSize()-1; i >= size; i--){
						Card change = currentPlayer->hand->getCards().at(i);
						currentPlayer->hand->removeCard(change);
						discardPile->addCard(change);
					}
					cout << "You must make, or alter, a pile with the bottom card drawn" << endl;
					sleep(3);
					drawCard(currentPlayer);
				}
			}
			else {
				num = -1;
			}
		}	
	}
	else {
		cout << "Discard Pile is empty" << endl;
		drawCard(currentPlayer);
	}	
	
}