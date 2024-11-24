#include "fullDeclare2.h"

// Create Deck 52 cards 
vector<Card2> createDeck2() {
    vector<Card2> deck;
    for (int suit = HEARTS2; suit <= SPADES2; suit++) {
        for (int rank = ACE2; rank <= KING2; rank++) { // Start from TWO2 to ACE2
            deck.push_back(Card2{ static_cast<Rank2>(rank), static_cast<Suit2>(suit) });
        }
    }
    return deck;
}


// shuffle deck
void shuffleDeck2(vector<Card2>& deck) {
    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(deck.begin(), deck.end());
}

// this function computes the score of 3 cards
int calculateScore2(const vector<Card2>& hand) {
    int sum = 0;
    int tensCount = 0; // count the number of 10, J, Q, K

    for (const Card2& card : hand) {
        int value = (card.rank >= JACK2) ? 10 : card.rank;
        sum += value;
        if (value == 10 && card.rank != TEN2) {
            tensCount++;
        }
    }

    // Case "ba cao" (3 cards J, Q, K)
    if (tensCount == 3) {
        return 100; // "Ba cao" has value is 100
    }

    // Case "bu" (10, 20, 30 scores)
    if (sum % 10 == 0) { 
        return -1; // "Bu" has value is -1
    }

    return sum % 10; // Only take the unit digit of the total score.
}

// Deals the cards to players function
vector<Card2> dealHand2(vector<Card2>& deck) {
    vector<Card2> hand;
    for (int i = 0; i < 3; i++) {
        hand.push_back(deck.back());
        deck.pop_back();
    }
    return hand;
}

// Print Card function
void printCard2(const Card2& card) {
    string rankNames[] = { "", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    string suitNames[] = { "HEARTS", "DIAMONDS", "CLUBS", "SPADES" };
    cout << rankNames[card.rank] << " " << suitNames[card.suit];
}

// Playing game function
void playGame2(int playerCount)
{
    // Creats and Shuffles the deck
    vector<Card2> deck = createDeck2();
    shuffleDeck2(deck);

    vector<int> scores(playerCount); // Store score player
    int maxScore = -1;
    bool bacaoExists = false;

    // Deals card to player
    for (int i = 0; i < playerCount; i++) {
        cout << "Player " << i + 1 << " hand: ";
        vector<Card2> hand = dealHand2(deck);
        for (const Card2& card : hand) {
            printCard2(card);
            cout << " ";
        }

        // Score player
        int score = calculateScore2(hand);
        scores[i] = score;

        if (score == 100) {
            bacaoExists = true;
        }

        if (score > maxScore && score != -1) {
            maxScore = score;
        }

        cout << "- Score: ";
        if (score == -1) {
            cout << "Bust";
        }
        else if (score == 100) {
            cout << "Three Royals";
        }
        else {
            cout << score;
        }
        cout << endl;
    }

    // Determine the winner
    if (bacaoExists) {
        cout << "Result: Player(s) with 'Three Royals' win!" << endl;
        for (int i = 0; i < playerCount; i++) {
            if (scores[i] == maxScore) {
                cout << "Player " << i + 1 << " ";
            }
        }
        cout << endl;
    }
    else if (maxScore != -1) {
        cout << "Result: Player(s) with highest score " << maxScore << " win!" << endl;
        for (int i = 0; i < playerCount; i++) {
            if (scores[i] == maxScore) {
                cout << "Player " << i + 1 << " ";
            }
        }
        cout << endl;
    }
    else {
        cout << "Result: No winner, all players are 'Bust'." << endl;
    }
}