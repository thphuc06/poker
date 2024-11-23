#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;

enum Suit {
    Hearts,
    Diamond,
    Clubs,
    Spades
};

const std::vector<std::string> Suit_name{
    "hearts", "diamonds", "clubs", "spades" 
};

const std::vector<std::string> Rank{
    "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "ace"
};

const std::map<std::string, int> Rank_value{
    {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8},
    {"9", 9}, {"10", 10}, {"jack", 11}, {"queen", 12}, {"king", 13}, {"ace", 14}
};

struct Card3 {
    std::string Rank;
    Suit suit_name;
};

using Hand3 = std::vector<Card3>;

Hand3 makeDeck();
void shuffle(Hand3& deck);
void showHand(Hand3& hand);
int Ranking(Hand3& hand);
Hand3 drawcard(Hand3& deck, int num);
Hand3 getStrongest(Hand3& playerCards, Hand3& communityCards);
std::string compareHands(std::vector<Hand3>& player_hands, std::vector<bool>& active_players);
void showCommunityCards(Hand3& communityCards, int stage);
void playPoker();
