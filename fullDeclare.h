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
    string suit;    // Stores the suit of the card (hearts, diamonds, clubs, spades)
    string rank;    // Stores the rank of the card (2-10, jack, queen, king, ace)
};

struct Hand
{
    Card cards[5];  // Array of 5 cards representing a poker hand
};

struct point
{
    map<string, int> Point;  // Maps card ranks and suits to numerical values for comparison
    point();
};

// Function declarations

/**
 * Shuffles the deck of cards randomly
 * @param deck Array of cards to shuffle
 * @param n Number of cards in the deck
 */
void shuffle_cards(Card deck[], int n);

/**
 * Deals cards to players from the deck
 * @param desk Array of 52 cards
 * @param num_players Number of players in the game
 * @return Array of Hand structures, one for each player
 */
Hand* dealing_cards(Card desk[52], int num_players);

/**
 * Poker hand evaluation functions - each returns true if the hand matches that type
 */
bool straight_flush(Hand player);   // Five cards in sequence, all of the same suit
bool four_of_a_kind(Hand player);   // Four cards of the same rank
bool full_house(Hand player);       // Three of a kind plus a pair
bool flush(Hand player);            // Any five cards of the same suit
bool straight(Hand player);         // Five cards in sequence
bool three_of_a_kind(Hand player);  // Three cards of the same rank
bool two_pair(Hand player);         // Two different pairs
bool one_pair(Hand player);         // Two cards of the same rank

/**
 * Compares two hands to determine which is stronger
 * @return Positive if hand a is stronger, negative if hand b is stronger, 0 if equal
 */
int compare_hand(Hand a, Hand b);

/**
 * Converts a numerical score to a string description of the hand type
 * @return String description (e.g., "full house", "straight flush")
 */
string type_of_card(int score);

/**
 * Determines the winner among multiple players
 * @return pair<winner_index, hand_strength>
 */
pair<pair<int,int>, int> get_winner(Hand* players, int num_players);

/**
 * Statistics and player data management functions
 */
void update_player_data(const string player_name, bool win, int hand_type);
void update_player_win_rate(const string player_name, float win_rate);
void update_player_win_game(const string player_name, int win_game);
float get_win_rate(const string player_name);
int get_win_game(const string player_name);

/**
 * Helper functions for hand evaluation
 */
int check_strength(Hand hand);  // Returns numerical value representing hand strength
pair<int, pair<int, int>> take_pair(Hand a);  // Identifies pairs in a hand

#endif