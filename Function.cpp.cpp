#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <unistd.h>

 using namespace std;

{

private:
string suit;
  
int cards;
  
int cardVal;
  
int deletecard;

public:
Card ();
  
void getSuit ();
  
void getCardVal ();
  
void setCard (int in_suit, int in_val);
  
void showhand (vector < Card > player);
  
friend ostream & operator << (ostream & os, Card & obj);
  
    //Card& operator =(Card otherin);
    Card (const Card & otherin);
  
void meld (Card & playercard, Card & playercard1, Card & playercard2);
  
void run (Card & playercard, Card & playercard1, Card & playercard2);
  
void pass (Card & playercard);
  
void deletethecard (Card & card, char &yn);

 
};


 
void drawCardp1 (vector < Card > &deck, vector < Card > &player1);

void showhand (vector < Card > player);

void gamestart (vector < Card > deck);

void pickcards (vector < Card > &deck, vector < Card > &player1);

void checkdelete (vector < Card > &player);

 
void
checkdelete (vector < Card > &player)
{
  
for (int i = 0; i < player.size (); i++)
    {
      
Card check;
      
char yn = 'n';
      
check = player[i];
      
check.deletethecard (check, yn);
      
if (yn == 'y')
	{
	  
 
cout << player[i] << " discarded" << endl;
	  
player.erase (player.begin () + i);
	  
i = i - 1;
	
}
    
}

 
}


 
void
Card::deletethecard (Card & card, char &yn)
{
  
if (card.deletecard == 1)
    {
      
yn = 'y';
    
}
  
  else
    {
      
yn = 'n';
    
}

}


 
void
Card::pass (Card & playercard)
{
  
playercard.deletecard = 0;

} 
 
void

Card::meld (Card & playercard, Card & playercard1, Card & playercard2)
{
  
if (playercard.cardVal == playercard1.cardVal
       && playercard1.cardVal == playercard2.cardVal)
    {
      
cout << "Meld possible" << endl;
      
playercard.deletecard = 1;
      
playercard1.deletecard = 1;
      
playercard2.deletecard = 1;
    
}
  
  else
    {
      
cout << "Numbers do not match. Turn skipped" << endl;
    
}

}


 
void
Card::run (Card & playercard, Card & playercard1, Card & playercard2)
{
  
if (playercard.suit == playercard1.suit
       && playercard1.suit == playercard2.suit)
    {
      
cout << "Run possible" << endl;
      
playercard.deletecard = 1;
      
playercard1.deletecard = 1;
      
playercard2.deletecard = 1;
    
}
  
  else
    {
      
cout << "Suits do not match. Turn skipped" << endl;
    
}

 
}


 
void
drawCardp1 (vector < Card > &deck, vector < Card > &player1)
{
  
cout << "Drawing Card..." << endl << endl;
  
 
player1.push_back (deck[0]);
  
 
 
deck.erase (deck.begin (), deck.begin () + 1);

 
 
 
} 
 
 
void

showhand (vector < Card > player)
{
  
cout << "Here are the cards in your hand: " << endl;
  
for (int i = 0; i < player.size (); i++)
    {
      
cout << i << ": ";
      
 
cout << player[i];
    
 
} 
cout << endl;

 
} 
 
void

pickcards (vector < Card > &deck, vector < Card > &player1)
{
  
int input;
  
cout << "Pick the cards that you wish to run or meld." << endl;
  
 
cout << "A run is when three cards are of the same suit" << endl;
  
 
cout << "A meld is a set of three of the same numbers" << endl;
  
cout << "What do you wish to do? (1=run, 2=meld, 3=pass)" << endl;
  
cin >> input;
  
if (input == 1)
    {
      
int cardselect = 14, cardselect1 = 14, cardselect2 = 14;
      
cout << "Run selected. Which 3 cards do you pick?" << endl;
      
cin >> cardselect;
      
cin >> cardselect1;
      
cin >> cardselect2;
      
if (cardselect == 14 || cardselect1 == 14 || cardselect2 == 14)
	{
	  
cout << "Incorrect amount of cards inputted" << endl;
	  
exit (0);
	
}
      
      else
	{
	  
Card run;
	  
run.run (player1[cardselect], player1[cardselect1],
		    player1[cardselect2]);
	
}
    
}
  
if (input == 2)
    {
      
int cardselect = 14, cardselect1 = 14, cardselect2 = 14;
      
cout << "Meld selected. Which 3 cards do you pick?" << endl;
      
cin >> cardselect;
      
cin >> cardselect1;
      
cin >> cardselect2;
      
if (cardselect == 14 || cardselect1 == 14 || cardselect2 == 14)
	{
	  
cout << "Incorrect amount of cards inputted" << endl;
	  
exit (0);
	
}
      
      else
	{
	  
Card meld;
	  
meld.meld (player1[cardselect], player1[cardselect1],
		      player1[cardselect2]);
	
}
    
}
  
if (input == 3)
    {
      
cout << "Pass selected... Next player turn." << endl;
      
 
Card pass;
      
pass.pass (player1[player1.size () - 1]);
    
}

}
