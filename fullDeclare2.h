#pragma once
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

// Declare the value of cards for game mode 2
enum Suit2
{
    HEARTS2,
    DIAMONDS2,
    CLUBS2,
    SPADES2 //3
};

enum Rank2
{   
    ACE2 = 1,
    TWO2,
    THREE2,
    FOUR2,
    FIVE2,
    SIX2,
    SEVEN2,
    EIGHT2,
    NINE2,
    TEN2,
    JACK2,
    QUEEN2,
    KING2
};

// structure for game mode 2
struct Card2
{
    Rank2 rank;
    Suit2 suit;
};

// Prototype functions for game mode 2
vector<Card2> createDeck2();
void shuffleDeck2(vector<Card2>& deck);
int calculateScore2(const vector<Card2>& hand);
vector<Card2> dealHand2(vector<Card2>& deck);
void printCard2(const Card2& card);
void playGame2(int playerCount);

