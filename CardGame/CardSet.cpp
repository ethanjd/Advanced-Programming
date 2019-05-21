/**********************************************
* CardSet.cpp - Contains implementation of class CardSet
* <Ethan Joseph Dsouza>
***********************************************/

#include <iostream>
#include <cstdlib>
#include "CardSet.h"
using namespace std;

//Default constructor
CardSet::CardSet()
{
    nCards = 0;
    Card = new int[nCards];
}

//Parameterized constructor taking an int which sets the number of cards in
//the deck
CardSet::CardSet(int x)
{
    nCards = x;
    Card = new int[nCards];

    for(int i = 0; i < nCards; i++)
    {
        Card[i] = i % 51;
    }
    this->Shuffle();
}

//Class destructor
CardSet::~CardSet()
{
    delete [] Card;
    Card = NULL;
}

int CardSet::Size() const
{
    return nCards;
}

//Public bool function that returns true if nCards is empty or false if not
bool CardSet::IsEmpty() const
{
    return(!nCards);
}

//Public function that shuffles the current object's deck without adding or
//removing any values
void CardSet::Shuffle()
{
    int j, temp;

    for(int i = 0; i < nCards; i++)
    {
        j = rand() % nCards;
        if(i != j)
        {
            temp = Card[i];
            Card[i] = Card[j];
            Card[j] = temp;
        }
    }
}

//Public function that returns the first card in the current deck as an
//integer value and sets the Card array to null if the deck is empty after
//dealing the last card
int CardSet::Deal()
{
    int res;
    if(!nCards)
    {
        cerr << "The set is empty" << endl;
        exit(1);
    }
    if(nCards == 1)
    {
        res = Card[0];
        delete [] Card;
        Card = NULL;
        return res;
    }

    res = Card[0];
    int* temp = new int[--nCards];

    for(int i = 0; i < nCards; i++)
    {
        temp[i] = Card[i+1];
    }

    delete [] Card;
    *&Card = temp;
    temp = NULL;

    return res;
}

//Public function that deals 'num' number of cards to two different objects
//that are passed by reference (deck1 & deck2) and exits the program if the
//current deck doesn't have enough cards to complete the deal
void CardSet::Deal(int num,CardSet& deck1,CardSet& deck2)
{
    if(this->Size() < (num*2))
    {
        cerr << "The deck doesn't have enough cards to complete the deal!";
        exit(1);
    }

    for(int i = 0; i < num; i++)
    {
        deck1.AddCard(this->Deal());
        deck2.AddCard(this->Deal());
    }
}

//Public function that deals 'num' number of cards to four different objects
//that are passed by reference (deck1, deck2, deck3 & deck4) and exits the
//program if the current deck doesn't have enough cards to complete the deal
void CardSet::Deal(int num, CardSet& deck1, CardSet& deck2, CardSet& deck3, CardSet& deck4)
{
    if(this->Size() < (num*4))
    {
        cerr << "The deck doesn't have enough cards to complete the deal!";
        exit(1);
    }

    for(int i = 0; i < num; i++)
    {
        deck1.AddCard(this->Deal());
        deck2.AddCard(this->Deal());
        deck3.AddCard(this->Deal());
        deck4.AddCard(this->Deal());

    }
}

//Public function that takes an int as input and inputs that number to the
//beginning of the array
void CardSet::AddCard(int c)
{
    int* temp = new int[++nCards];

    temp[0] = c;

    for(int i = 1; i < nCards; i++)
    {
        temp[i] = Card[i - 1];
    }

    delete [] Card;
    *&Card = temp;
    temp = NULL;
}


//Public function that takes a CardSet object and merges the passed deck
//and the current deck alternatively and stores the combined deck in the current
//object while setting the passed object to null
void CardSet::MergeShuffle(CardSet& deck)
{
    if(deck.IsEmpty())
    {
        cerr << "The deck has no cards to merge!\n";
        return;
    }
    int deckSize = nCards + deck.Size();
    int* temp = new int[deckSize];

    for(int i = 0; i < deckSize;)
    {
        if(this->Size() > 0)
        {
            temp[i++] = this->Deal();
        }
        if(deck.Size() > 0)
        {
            temp[i++] = deck.Deal();
        }
    }
    delete [] Card;
    *&Card = temp;
    temp = NULL;
    nCards = deckSize;
}

//Public function that iterates through all the cards in the Card array and
//invokes the PrintCard function on each one.
void CardSet::Print() const
{
    for (int i = 0; i < nCards; i++)
    {
        if (i % 5 == 0 && i != 0)
            cout << endl;
        PrintCard(Card[i]);
        cout << " ";
    }
    cout << endl;
}


// Private function to print out usual representation of playing card.
// Input is integer from 0 to 51.  There is no error checking.

void CardSet::PrintCard(int c) const
{
	int Rank = c%13;
	int Suit = c/13;
	const char NameSuit[5] = "SCDH";
	const char NameRank[14] = "23456789XJQKA";
	cout << NameRank[Rank] << NameSuit[Suit];
}
