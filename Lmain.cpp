#include <iostream>
#include <algorithm>
#include "deck.h"
#include "player.h"
#include <cstdlib>
#include "cards.h"
#include <vector>
#include <unistd.h>

using namespace std;

template<class T>
void Vec_RemoveAll(vector<T>& vec, T val)
{
    vec.erase(remove(vec.begin(), vec.end(), val), vec.end());
}


class Table
{
    public:
        Table(Player playerOne,Player comp, Deck drawStack, vector<Card> discardStack);
        void drawCard(Player* currentPlayer);
        void turn(Player* currentPlayer);
        void drawDiscard(Player* currentPlayer);
        void displayTable(/*Player* currentPlayer*/);
        void playChoice(Player* currentPlayer);
        void turnDiscard(Player* currentPlayer);
        void placeNewSet(Player* currentPlayer);
        Card selectCard(Player* currentPlayer);
        int handFollowsRules(vector<Card> selectCard);
        void removeCards(Card cards, Player* currentPlayer);
		void addToSet(Player* currentPlayer);
		void pileMaker(Player* currentPlayer);
		void playGame();
		void printBoard();
    private:
        vector<Card> discardPile;
        Player player;
        Player Computer;
        Deck drawPile;
		/*
			__________________________________________________________________________________________
			|						DO NOT TOUCH THE GAMEBOARD STRING VECTOR.						 |
			|				IF YOU MESS WITH THE GAMEBOARD VECTOR, THE BOARD/GAME WILL 			     |
			|	 LITERALLY BREAK ITSELF. IT WAS STRING-INDEXED PERFECTLY ALREADY. DONT TOUCH IT.     |
			└────────────────────────────────────────────────────────────────────────────────────────┘
		*/
vector<string> gameBoard ={"_________________________________________________________________________________________________________________________________________",
                          "| ┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐  |",
                          "| | n        || n        || n        || n        || n        || n        || n        || n        || n        || n        || n        |  |",
                          "| | d        || d        || d        || d        || d        || d        || d        || d        || d        || d        || d        |  |",
                          "| |          ||          ||          ||          ||          ||          ||          ||          ||          ||          ||          |  |",
                          "| |     d    ||    d     ||    d     ||    d     ||    d     ||    d     ||    d     ||    d     ||    d     ||    d     ||    d     |  |",
                          "| |          ||          ||          ||          ||          ||          ||          ||          ||          ||          ||          |  |",
                          "| |        n ||        n ||        n ||        n ||        n ||        n ||        n ||        n ||        n ||        n ||        n |  |",
                          "| |        d │|        d ||        d ||        d ||        d ||        d ||        d ||        d ||        d ||        d ||        d |  |",
                          "│ └──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘  |",
                          "│                                                                     Computer                                                          │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                               ┌─────────┐          ┌─────────┐                                                                        |",
                          "|                               |xxxxxxxxx|          | n       |                                                                        |",
                          "|                               |xxxxxxxxx|          | d       |                                                                        |",
                          "|                               |xxxxxxxxx|          |         |                                                                        |",
                          "|                               |xxxxxxxxx|          |    d    |                                                                        |",
                          "|                               |xxxxxxxxx|          |         │                                                                        |",
                          "|                               |xxxxxxxxx|          |       n |                                                                        |",
                          "|                               |xxxxxxxxx|          |       d |                                                                        |",
                          "|                               └─────────┘          └─────────┘                                                                        |",
                          "│                                  Deck                DiscPile                                                                         │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                                                                                                       │",
                          "│                                                   Player                                                                              │",
                          "| ┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐┌──────────┐  |",
                          "| | n        || n        || n        || n        || n        || n        || n        || n        || n        || n        || n        |  |",
                          "| | d        || d        || d        || d        || d        || d        || d        || d        || d        || d        || d        |  |",
                          "| |          ||          ||          ||          ||          ||          ||          ||          ||          ||          ||          |  |",
                          "| |     d    ||    d     ||    d     ||    d     ||    d     ||    d     ||    d     ||    d     ||    d     ||    d     ||    d     |  |",
                          "| |          ||          ||          ||          ||          ||          ||          ||          ||          ||          ||          |  |",
                          "| |        n ||        n ||        n ||        n ||        n ||        n ||        n ||        n ||        n ||        n ||        n |  |",
                          "| |        d │|        d ||        d ||        d ||        d ||        d ||        d ||        d ||        d ||        d ||        d |  |",
                          "│ └──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘└──────────┘  |",
                          "└───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘" };
        //int cardsOnBoard;
};

//If the table is already known
Table::Table(Player playerOne, Player comp, Deck drawStack, vector<Card> discardStack) 
{
	player = playerOne;
	Computer = comp;
	drawPile = drawStack;
	discardPile = discardStack;
	//cardsOnBoard = drawStack.size() + ;     new Pile();
}

// draw card for the turn, given the player it will prompt that player where they would like to draw a card from
void Table::drawCard(Player* currentPlayer){

	//Decide whether to take top discard or top draw pile
	//displayTable(currentPlayer);
	cout << "Take new card or draw from the discard pile?" << endl;
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
	switch (choice) {
		case 1:{		
			currentPlayer->add_card(drawPile.dealCard());
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
	//currentPlayer->showHand();
	drawCard(currentPlayer);	
	displayTable(/*currentPlayer*/);
	playChoice(currentPlayer);
	turnDiscard(currentPlayer);
}

// funciton for placing a meld or sequence
void Table::placeNewSet(Player* currentPlayer){
	vector<Card> selectedCards;
	bool selecting = true;
	char answer;
	do{
		selectedCards.push_back((selectCard(currentPlayer)));
		cout << "Continue? (Y or N)" << endl;
		cin >> answer;
		selecting =  (answer == 'Y' || answer == 'y');
	}while(selecting);

		int ruleFollowed = handFollowsRules(selectedCards);
		char id;
		switch(ruleFollowed){
			case 1:
				id = 'm';
				//cardsOnBoard->addToPile(selectedCards, id, currentPlayer);	
				for(int i=0; i<( selectedCards.size() ); i++)		
				{
					removeCards(selectedCards[i], currentPlayer);
				}
				displayTable(/*currentPlayer*/);
				playChoice(currentPlayer);
				break;
			case 2:
				id = 's';
				//cardsOnBoard->addToPile(selectedCards, id, currentPlayer);
				for(int i=0; i<( selectedCards.size() ); i++)		
				{
					removeCards(selectedCards[i], currentPlayer);
				}
				displayTable(/*currentPlayer*/);
				playChoice(currentPlayer);
				break;
			default:
				cout << "Your hand does not follow the rules please try again" << endl;
				sleep(1);
				selectedCards.clear();
				displayTable(/*currentPlayer*/);
				playChoice(currentPlayer);
			break;
	}
}

// utility funciton to remove cards from a players hand
void Table::removeCards(Card cards, Player* currentPlayer){
	for(int i = 0; i < currentPlayer->hand.size(); i++){
		Vec_RemoveAll(currentPlayer->hand,cards);
	}
}

// funciton for adding cards to an existing pile - player must seletc the pile they wish to add their card too
void Table::addToSet(Player* currentPlayer){
	cout << "Please select a pile to add your card to:" << endl;
	//cardsOnBoard->displayPiles();
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
		return playChoice(currentPlayer);
	}else{
		selection = stoi(selectionInput);
	}
	selection--; // changes value from 0-(size-1) 
	if(!(selection >= 0 && selection < discardPile.size())){
		cout << "Invalid Selection please try again." << endl;
		pileMaker(currentPlayer);
	}else{
		// I need to know what this next line does
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
			//??????
			cardsOnBoard->addCardToExist(selectedCards.at(selectedCards.size()-1), selection, currentPlayer);
			/*currentPlayer->hand->*/removeCards(selectedCards.at(selectedCards.size()-1),currentPlayer);
			displayTable(/*currentPlayer*/);
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
		displayTable(/*currentPlayer*/);
		cout << "Would you like to add cards to an existing pile (Y or N)" << endl;
		cin >> answer;
		if(answer == 'y' || answer == 'Y'){
			//ruleModifier = 2;				<-----What does this do?
			addToSet(currentPlayer);
		}
		else{
			//ruleModifier = 0;				<-----What does this do?
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
	//currentPlayer->showHand();
	displayTable(/*currentPlayer*/);
	if(currentPlayer->hand.size() == 0){// violate must discard a card rule
		// add all cards from most recent pile
		cout << "You must be able to discard a card" << endl;
		sleep(2);
		// ???????
		int pile = cardsOnBoard->getPile().size()-1;
		cout << pile << endl;
		for(int i = 0; i < cardsOnBoard->getPile().at(pile)->deckSize(); i++){
			// add cards back to hand
			cardsOnBoard->getPile().at(pile)->getCards().at(i).displayCard();
			//????
			currentPlayer->hand->addCard(cardsOnBoard->getPile().at(pile)->getCards().at(i));
		}
		cardsOnBoard->removeRecent();
		displayTable(currentPlayer);
		playChoice(currentPlayer);
	}else{
		cout << "Now you must discard a card please select a card to discard (Enter the value, then H,C,D,S for the suit)" << endl;

	}
	Card dis(selectCard(currentPlayer));
	discardPile.push_back(dis);
	removeCards(dis,currentPlayer);
}

//Selects Card utility funciton.
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
		return selectCard(currentPlayer);

	}
	Card target(realInput, suit);

	// search for cards in given players hand
	bool found = false;
	int i = 0;
	if(currentPlayer->hand.size() == 1){
		found = true;
		return currentPlayer->hand->getCards().at(0);
	}
	for(i = 0; i < currentPlayer->hand.size(); i++){
		if(target == currentlPlayer->hand->getCards().at(i)){
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

		areTheySame &= selectedCards[i].getValue() == selectedCards[i-1].getValue();
	}
	if(areTheySame == true){
		return 1;
	}

	areTheySame = true;
	for(int i = 1; i < selectedCards.size(); i++){
		areTheySame &= selectedCards[i].getSuit() == selectedCards[i-1].getSuit();
	}
	if(areTheySame == true){
		for(int i = 1; i < selectedCards.size(); i++){
			areTheySame &= selectedCards[i].getValue() == selectedCards[i-1].getValue()+1;
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
	int playerScore = this->player.score;
	int computerScore = this->Computer.score;
	while(playerScore < 100 && Computer.score < 100){
		while(playerWonRound == false) {
			//Player 1's turn
			if(drawPile.size() == 0){
				// add all cards from discard back to deck then reshuffle
				cout << "Reshuffling" << endl;
				for(int i = 0; i < discardPile.size()-1;i++){
					drawPile->addCard(discardPile->getCards().at(i));
				}
				Card topCard(discardPile->getCards().at(discardPile->deckSize()-1));
				discardPile->clear();
				discardPile->addCard(topCard);
				drawPile->shuffleDeck();
			}
			if (player == 1) {
				turn(player);
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
		drawPile.decks.clear();
		Deck newDeck;
		drawPile = newDeck;
		drawPile.shuffleDeck();
		playerScore += player.score;
		computerScore += Computer.score;
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
	if(player.score >= 100){
		cout << "The player has won! with: "<< player.score << " points!" << endl;
	}else if(Computer.score >= 100){
		cout << "The computer has won :( with "<< Computer.score << " points.." << endl;
	}else{
		if(player.score > computerScore){
			cout << "The player has won! with: "<< player1->score << " points!" << endl;
		}else if(Computer.score > player.score){
			cout << "The computer has won :( with "<< Computer.score << " points.." << endl;
		}else{
			cout << "It is  a tie with: " << player.score << " points" << endl;
		}
	}

}

void Table::printBoard()
{
	for(int i=0; i<gameBoard.size(); i++)
    {
        cout << gameBoard[i] << endl;
    }
}

//Displays Table
void Table::displayTable(/*Player *currentPlayer*/) {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	for(int i=0; i<gameBoard.size(); i++)
    {
        if(i==2||i==3||i==42||i==43)
        {// top of card
            for(int j=0; j<gameBoard[2].length(); j++)
            {
                //if((j==4||j==16||j==28||j==40||j==52||j==64||j==76||j==88||j==100||j==112)&&
				if(i==42)
                {	//values
					if(j==4 && (player.hand.size() <= 1)) {gameBoard[i].at(j) = player.hand[0].getValue();}
					if(j==16 && (player.hand.size() <= 2)) {gameBoard[i].at(j) = player.hand[1].getValue();}
					if(j==28 && (player.hand.size() <= 3)) {gameBoard[i].at(j) = player.hand[2].getValue();}
					if(j==40 && (player.hand.size() <= 4)) {gameBoard[i].at(j) = player.hand[3].getValue();}
					if(j==52 && (player.hand.size() <= 5)) {gameBoard[i].at(j) = player.hand[4].getValue();}
					if(j==64 && (player.hand.size() <= 6)) {gameBoard[i].at(j) = player.hand[5].getValue();}
					if(j==76 && (player.hand.size() <= 7)) {gameBoard[i].at(j) = player.hand[6].getValue();}
					if(j==88 && (player.hand.size() <= 8)) {gameBoard[i].at(j) = player.hand[7].getValue();}
					if(j==100 && (player.hand.size() <= 9)) {gameBoard[i].at(j) = player.hand[8].getValue();}
					if(j==112 && (player.hand.size() <= 10)) {gameBoard[i].at(j) = player.hand[9].getValue();}
                }
				if(i==2)
				{
					if(j==4 && (Computer.hand.size() <= 1)) {gameBoard[i].at(j) = Computer.hand[0].getValue();}
					if(j==16 && (Computer.hand.size() <= 2)) {gameBoard[i].at(j) = Computer.hand[1].getValue();}
					if(j==28 && (Computer.hand.size() <= 3)) {gameBoard[i].at(j) = Computer.hand[2].getValue();}
					if(j==40 && (Computer.hand.size() <= 4)) {gameBoard[i].at(j) = Computer.hand[3].getValue();}
					if(j==52 && (Computer.hand.size() <= 5)) {gameBoard[i].at(j) = Computer.hand[4].getValue();}
					if(j==64 && (Computer.hand.size() <= 6)) {gameBoard[i].at(j) = Computer.hand[5].getValue();}
					if(j==76 && (Computer.hand.size() <= 7)) {gameBoard[i].at(j) = Computer.hand[6].getValue();}
					if(j==88 && (Computer.hand.size() <= 8)) {gameBoard[i].at(j) = Computer.hand[7].getValue();}
					if(j==100 && (Computer.hand.size() <= 9)) {gameBoard[i].at(j) = Computer.hand[8].getValue();}
					if(j==112 && (Computer.hand.size() <= 10)) {gameBoard[i].at(j) = Computer.hand[9].getValue();}
				}
                if(i==43)
                {//suits
					if(j==4 && (player.hand.size() <= 1)) {gameBoard[i].at(j) = player.hand[0].getSuit();}
					if(j==16 && (player.hand.size() <= 2)) {gameBoard[i].at(j) = player.hand[1].getSuit();}
					if(j==28 && (player.hand.size() <= 3)) {gameBoard[i].at(j) = player.hand[2].getSuit();}
					if(j==40 && (player.hand.size() <= 4)) {gameBoard[i].at(j) = player.hand[3].getSuit();}
					if(j==52 && (player.hand.size() <= 5)) {gameBoard[i].at(j) = player.hand[4].getSuit();}
					if(j==64 && (player.hand.size() <= 6)) {gameBoard[i].at(j) = player.hand[5].getSuit();}
					if(j==76 && (player.hand.size() <= 7)) {gameBoard[i].at(j) = player.hand[6].getSuit();}
					if(j==88 && (player.hand.size() <= 8)) {gameBoard[i].at(j) = player.hand[7].getSuit();}
					if(j==100 && (player.hand.size() <= 9)) {gameBoard[i].at(j) = player.hand[8].getSuit();}
					if(j==112 && (player.hand.size() <= 10)) {gameBoard[i].at(j) = player.hand[9].getSuit();}
                }
				if(i==3)
				{
					if(j==4 && (Computer.hand.size() <= 1)) {gameBoard[i].at(j) = Computer.hand[0].getSuit();}
					if(j==16 && (Computer.hand.size() <= 2)) {gameBoard[i].at(j) = Computer.hand[1].getSuit();}
					if(j==28 && (Computer.hand.size() <= 3)) {gameBoard[i].at(j) = Computer.hand[2].getSuit();}
					if(j==40 && (Computer.hand.size() <= 4)) {gameBoard[i].at(j) = Computer.hand[3].getSuit();}
					if(j==52 && (Computer.hand.size() <= 5)) {gameBoard[i].at(j) = Computer.hand[4].getSuit();}
					if(j==64 && (Computer.hand.size() <= 6)) {gameBoard[i].at(j) = Computer.hand[5].getSuit();}
					if(j==76 && (Computer.hand.size() <= 7)) {gameBoard[i].at(j) = Computer.hand[6].getSuit();}
					if(j==88 && (Computer.hand.size() <= 8)) {gameBoard[i].at(j) = Computer.hand[7].getSuit();}
					if(j==100 && (Computer.hand.size() <= 9)) {gameBoard[i].at(j) = Computer.hand[8].getSuit();}
					if(j==112 && (Computer.hand.size() <= 10)) {gameBoard[i].at(j) = Computer.hand[9].getSuit();}
				}
            }
        }
        if(i==5||i==45)
        { // middle of card
            for(int j=0; j<gameBoard[2].length(); j++)
            {
				if(i==5)
				{
                    if(j==8 && (Computer.hand.size() <= 1)) {gameBoard[i].at(j) = Computer.hand[0].getSuit();}
					if(j==19 && (Computer.hand.size() <= 2)) {gameBoard[i].at(j) = Computer.hand[1].getSuit();}
					if(j==31 && (Computer.hand.size() <= 3)) {gameBoard[i].at(j) = Computer.hand[2].getSuit();}
					if(j==43 && (Computer.hand.size() <= 4)) {gameBoard[i].at(j) = Computer.hand[3].getSuit();}
					if(j==55 && (Computer.hand.size() <= 5)) {gameBoard[i].at(j) = Computer.hand[4].getSuit();}
					if(j==67 && (Computer.hand.size() <= 6)) {gameBoard[i].at(j) = Computer.hand[5].getSuit();}
					if(j==79 && (Computer.hand.size() <= 7)) {gameBoard[i].at(j) = Computer.hand[6].getSuit();}
					if(j==91 && (Computer.hand.size() <= 8)) {gameBoard[i].at(j) = Computer.hand[7].getSuit();}
					if(j==103 && (Computer.hand.size() <= 9)) {gameBoard[i].at(j) = Computer.hand[8].getSuit();}
					if(j==115 && (Computer.hand.size() <= 10)) {gameBoard[i].at(j) = Computer.hand[9].getSuit();}
				}
				if(i==45)
				{
					if(j==8 && (player.hand.size() <= 1)) {gameBoard[i].at(j) = player.hand[0].getSuit();}
					if(j==19 && (player.hand.size() <= 2)) {gameBoard[i].at(j) = player.hand[1].getSuit();}
					if(j==31 && (player.hand.size() <= 3)) {gameBoard[i].at(j) = player.hand[2].getSuit();}
					if(j==43 && (player.hand.size() <= 4)) {gameBoard[i].at(j) = player.hand[3].getSuit();}
					if(j==55 && (player.hand.size() <= 5)) {gameBoard[i].at(j) = player.hand[4].getSuit();}
					if(j==67 && (player.hand.size() <= 6)) {gameBoard[i].at(j) = player.hand[5].getSuit();}
					if(j==79 && (player.hand.size() <= 7)) {gameBoard[i].at(j) = player.hand[6].getSuit();}
					if(j==91 && (player.hand.size() <= 8)) {gameBoard[i].at(j) = player.hand[7].getSuit();}
					if(j==103 && (player.hand.size() <= 9)) {gameBoard[i].at(j) = player.hand[8].getSuit();}
					if(j==115 && (player.hand.size() <= 10)) {gameBoard[i].at(j) = player.hand[9].getSuit();}
				}
            }
        }
        if(i==7||i==8||i==47||i==48)
        {// bottom half of card
            for(int j=0; j<gameBoard[2].length(); j++)
            {
				if(i==7)
				{
					if(j==11 && (Computer.hand.size() <= 1)) {gameBoard[i].at(j) = Computer.hand[0].getValue();}
					if(j==23 && (Computer.hand.size() <= 2)) {gameBoard[i].at(j) = Computer.hand[1].getValue();}
					if(j==35 && (Computer.hand.size() <= 3)) {gameBoard[i].at(j) = Computer.hand[2].getValue();}
					if(j==47 && (Computer.hand.size() <= 4)) {gameBoard[i].at(j) = Computer.hand[3].getValue();}
					if(j==59 && (Computer.hand.size() <= 5)) {gameBoard[i].at(j) = Computer.hand[4].getValue();}
					if(j==71 && (Computer.hand.size() <= 6)) {gameBoard[i].at(j) = Computer.hand[5].getValue();}
					if(j==83 && (Computer.hand.size() <= 7)) {gameBoard[i].at(j) = Computer.hand[6].getValue();}
					if(j==95 && (Computer.hand.size() <= 8)) {gameBoard[i].at(j) = Computer.hand[7].getValue();}
					if(j==107 && (Computer.hand.size() <= 9)) {gameBoard[i].at(j) = Computer.hand[8].getValue();}
					if(j==119 && (Computer.hand.size() <= 10)) {gameBoard[i].at(j) = Computer.hand[9].getValue();}
				}
				if(i==47)
				{
					if(j==11 && (player.hand.size() <= 1)) {gameBoard[i].at(j) = player.hand[0].getValue();}
					if(j==23 && (player.hand.size() <= 2)) {gameBoard[i].at(j) = player.hand[1].getValue();}
					if(j==35 && (player.hand.size() <= 3)) {gameBoard[i].at(j) = player.hand[2].getValue();}
					if(j==47 && (player.hand.size() <= 4)) {gameBoard[i].at(j) = player.hand[3].getValue();}
					if(j==59 && (player.hand.size() <= 5)) {gameBoard[i].at(j) = player.hand[4].getValue();}
					if(j==71 && (player.hand.size() <= 6)) {gameBoard[i].at(j) = player.hand[5].getValue();}
					if(j==83 && (player.hand.size() <= 7)) {gameBoard[i].at(j) = player.hand[6].getValue();}
					if(j==95 && (player.hand.size() <= 8)) {gameBoard[i].at(j) = player.hand[7].getValue();}
					if(j==107 && (player.hand.size() <= 9)) {gameBoard[i].at(j) = player.hand[8].getValue();}
					if(j==119 && (player.hand.size() <= 10)) {gameBoard[i].at(j) = player.hand[9].getValue();}
				}
				if(i==8)
				{
                    if(j=11 && (Computer.hand.size() <= 1)) {gameBoard[i].at(j) = Computer.hand[0].getSuit();}
					if(j==23 && (Computer.hand.size() <= 2)) {gameBoard[i].at(j) = Computer.hand[1].getSuit();}
					if(j==35 && (Computer.hand.size() <= 3)) {gameBoard[i].at(j) = Computer.hand[2].getSuit();}
					if(j==47 && (Computer.hand.size() <= 4)) {gameBoard[i].at(j) = Computer.hand[3].getSuit();}
					if(j==59 && (Computer.hand.size() <= 5)) {gameBoard[i].at(j) = Computer.hand[4].getSuit();}
					if(j==71 && (Computer.hand.size() <= 6)) {gameBoard[i].at(j) = Computer.hand[5].getSuit();}
					if(j==83 && (Computer.hand.size() <= 7)) {gameBoard[i].at(j) = Computer.hand[6].getSuit();}
					if(j==95 && (Computer.hand.size() <= 8)) {gameBoard[i].at(j) = Computer.hand[7].getSuit();}
					if(j==107 && (Computer.hand.size() <= 9)) {gameBoard[i].at(j) = Computer.hand[8].getSuit();}
					if(j==119 && (Computer.hand.size() <= 10)) {gameBoard[i].at(j) = Computer.hand[9].getSuit();}
				}
				if(i==48)
				{
					if(j==11 && (player.hand.size() <= 1)) {gameBoard[i].at(j) = player.hand[0].getSuit();}
					if(j==23 && (player.hand.size() <= 2)) {gameBoard[i].at(j) = player.hand[1].getSuit();}
					if(j==35 && (player.hand.size() <= 3)) {gameBoard[i].at(j) = player.hand[2].getSuit();}
					if(j==47 && (player.hand.size() <= 4)) {gameBoard[i].at(j) = player.hand[3].getSuit();}
					if(j==59 && (player.hand.size() <= 5)) {gameBoard[i].at(j) = player.hand[4].getSuit();}
					if(j==71 && (player.hand.size() <= 6)) {gameBoard[i].at(j) = player.hand[5].getSuit();}
					if(j==83 && (player.hand.size() <= 7)) {gameBoard[i].at(j) = player.hand[6].getSuit();}
					if(j==95 && (player.hand.size() <= 8)) {gameBoard[i].at(j) = player.hand[7].getSuit();}
					if(j==107 && (player.hand.size() <= 9)) {gameBoard[i].at(j) = player.hand[8].getSuit();}
					if(j==119 && (player.hand.size() <= 10)) {gameBoard[i].at(j) = player.hand[9].getSuit();}
				}
            }
        }
        if(i==22)
        {// top of discPile's value
            gameBoard[i].at(55) = (discardPile[discardPile.size()-1]).getValue();
        }
        if(i==23)
        {// top of discPile's suit
            gameBoard[i].at(55) = (discardPile[discardPile.size()-1]).getSuit();
        }
        if(i==25)
        {// middle of discPile's value
            gameBoard[i].at(58) = (discardPile[discardPile.size()-1]).getValue();
        }
        if(i==27)
        {// bottom of discPile's value
            gameBoard[i].at(61) =  (discardPile[discardPile.size()-1]).getValue();
        }
        if(i==28)
        {// bottom of discPile's suit
            gameBoard[i].at(61) = (discardPile[discardPile.size()-1]).getSuit();
        }
		printBoard();
    }

 /*	cout << "\033[2J\033[1;1H"; //"Clear Screen"
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
	//player2->showHand();*/
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

int main()
{
	string pname;
	cout << "What is your name?\n";
	cin >> pname;

	Player playr(pname);
	Player computer;
	Deck gameDeck;
	vector<Card> discPile;

	Table GinRummy(playr, computer, gameDeck, discPile);

	GinRummy.playGame();

	return 0;
}