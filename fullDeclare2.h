#pragma once
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

// Declare the value of cards
enum Suit2 { HEARTS2, DIAMONDS2, CLUBS2, SPADES2 };
enum Rank2 { ACE2 = 1, TWO2, THREE2, FOUR2, FIVE2, SIX2, SEVEN2, EIGHT2, NINE2, TEN2, JACK2, QUEEN2, KING2 };

// structure
struct Card2 {
    Rank2 rank;
    Suit2 suit;
};

//Prototype
vector<Card2> createDeck2(); //Tao bo bai 52 la
void shuffleDeck2(vector<Card2>& deck); //Tron bo bai
int calculateScore2(const vector<Card2>& hand); //Tinh diem
vector<Card2> dealHand2(vector<Card2>& deck); //Chia bai
void printCard2(const Card2& card); //In bai
void playGame2(int playerCount); //choi game