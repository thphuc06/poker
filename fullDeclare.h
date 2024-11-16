#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace std;

// Structure definitions
    struct Card
    {
        string suit;
        string rank;
    };

    struct Hand
    {
        Card cards[5];
    };

    struct point
    {
        map<string, int> Point;
        point();
    };

// Function declarations
void shuffle_cards(Card deck[], int n);
Hand* dealing_cards(Card desk[52], int num_players);
bool straight_flush(Hand player);
bool four_of_a_kind(Hand player);
bool full_house(Hand player);
bool flush(Hand player);
bool straight(Hand player);
bool three_of_a_kind(Hand player);
bool two_pair(Hand player);
bool one_pair(Hand player);
int compare_hand(Hand a, Hand b);
string type_of_card(int score);
pair<int, int> get_winner(Hand* players, int num_players);
void update_player_data(const string player_name, bool win, int hand_type);
void update_playerlist(const string player_name, float win_rate);
float get_win_rate(const string player_name);
int check_strength(Hand hand);
pair<int, pair<int, int>> take_pair(Hand a);

#endif