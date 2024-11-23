#include "fullDeclare3.h"


Hand3 makeDeck() {
    Hand3 deck;
    for (int i = 0; i < Rank.size(); ++i) {
        for (int j = 0; j < 4; ++j) {
            deck.push_back({ Rank[i], static_cast<Suit>(j) });
        }
    }
    return deck;
}

void shuffle(Hand3& deck) {
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(static_cast<unsigned>(time(0))));
}

void showHand(Hand3& hand) {
    for (int i = 0; i < hand.size(); ++i) {
        std::cout << hand[i].Rank << " of " << Suit_name[hand[i].suit_name] << " ";
    }
    std::cout << std::endl;
}

int Ranking(Hand3& hand) {
    std::vector<int> rank_Value;
    std::map<std::string, int> rank_count;
    bool is_Flush = true, is_Straight = true;
    Suit suit = hand[0].suit_name;

    for (int i = 0; i < hand.size(); ++i) {
        rank_Value.push_back(Rank_value.at(hand[i].Rank));
        ++rank_count[hand[i].Rank];
        if (hand[i].suit_name != suit) {
            is_Flush = false;
        }
    }

    sort(rank_Value.begin(), rank_Value.end());
    for (int i = 0; i < rank_Value.size() - 1; ++i) {
        if (rank_Value[i] != rank_Value[i + 1] - 1) {
            is_Straight = false;
        }
    }

    if (is_Flush && is_Straight) return 8;
    if (rank_count.size() == 2) {
        auto it = rank_count.begin();
        if (it->second == 4 || (++it)->second == 4) return 7;
        return 6;
    }
    if (is_Flush) return 5;
    if (is_Straight) return 4;
    if (rank_count.size() == 3) {
        auto it = rank_count.begin();
        if (it->second == 3 || (++it)->second == 3 || (++it)->second == 3) return 3;
        return 2;
    }
    if (rank_count.size() == 4) return 1;
    return 0;
}

Hand3 drawcard(Hand3& deck, int num) {
    Hand3 hand;
    for (int i = 0; i < num; ++i) {
        hand.push_back(deck.back());
        deck.pop_back();
    }
    return hand;
}

Hand3 getStrongest(Hand3& playerCards, Hand3& communityCards) {
    Hand3 strongest;
    int current_strongest_rank = -1;
    Hand3 all = playerCards;
    all.insert(all.end(), communityCards.begin(), communityCards.end());

    for (int i = 0; i < all.size(); ++i) {
        for (int j = i + 1; j < all.size(); ++j) {
            Hand3 checking;
            for (int k = 0; k < all.size(); ++k) {
                if (k != i && k != j) {
                    checking.push_back(all[k]);
                }
            }

            int rank_hand = Ranking(checking);
            if (rank_hand > current_strongest_rank) {
                current_strongest_rank = rank_hand;
                strongest = checking;
            }
            else if (rank_hand == current_strongest_rank) {
                sort(checking.begin(), checking.end(), [](const Card3& a, const Card3& b) {
                    return Rank_value.at(a.Rank) > Rank_value.at(b.Rank);
                    });
                sort(strongest.begin(), strongest.end(), [](const Card3& a, const Card3& b) {
                    return Rank_value.at(a.Rank) > Rank_value.at(b.Rank);
                    });

                if (std::lexicographical_compare(
                    strongest.begin(), strongest.end(),
                    checking.begin(), checking.end(),
                    [](const Card3& a, const Card3& b) {
                        return Rank_value.at(a.Rank) < Rank_value.at(b.Rank);
                    })) {
                    strongest = checking;
                }
            }
        }
    }
    return strongest;
}

std::string compareHands(std::vector<Hand3>& player_hands, std::vector<bool>& active_players) {
    int best_rank = -1;
    std::vector<int> tied_players;

    for (int i = 0; i < player_hands.size(); ++i) {
        if (!active_players[i]) continue;

        int rank = Ranking(player_hands[i]);
        if (rank > best_rank) {
            best_rank = rank;
            tied_players = { i };
        }
        else if (rank == best_rank) {
            tied_players.push_back(i);
        }
    }

    if (tied_players.empty()) return "No players remain.";
    if (tied_players.size() == 1) return "Player " + std::to_string(tied_players[0] + 1) + " wins!";

    Hand3 best_hand;
    int winning_player = -1;
    for (int i : tied_players) {
        Hand3 current_hand = player_hands[i];
        sort(current_hand.begin(), current_hand.end(), [](const Card3& a, const Card3& b) {
            return Rank_value.at(a.Rank) > Rank_value.at(b.Rank);
            });

        if (winning_player == -1 || std::lexicographical_compare(
            best_hand.begin(), best_hand.end(),
            current_hand.begin(), current_hand.end(),
            [](const Card3& a, const Card3& b) {
                return Rank_value.at(a.Rank) < Rank_value.at(b.Rank);
            })) {
            best_hand = current_hand;
            winning_player = i;
        }
    }

    return "Player " + std::to_string(winning_player + 1) + " wins with a tie-break!";
}

void showCommunityCards(Hand3& communityCards, int stage) {
    std::cout << std::endl;
    std::cout << "Community Cards: ";
    for (int i = 0; i < stage; ++i) {
        std::cout << communityCards[i].Rank << " of " << Suit_name[communityCards[i].suit_name] << " ";
    }
    std::cout << std::endl;
}

void playPoker() {
    std::vector<Card3> deck = makeDeck();
    shuffle(deck);

    std::cout << "Welcome to 3-Player Texas Hold'em Poker!" << std::endl;

    std::vector<Hand3> playerHoleCards = {
        drawcard(deck, 2),
        drawcard(deck, 2),
        drawcard(deck, 2)
    };

    Hand3 communityCards = drawcard(deck, 5);

    for (int i = 0; i < playerHoleCards.size(); ++i) {
        std::cout << std::endl << "Player " << i + 1 << "'s cards: ";
        showHand(playerHoleCards[i]);
    }

    std::vector<bool> activePlayers = { true, true, true };

    for (int stage = 3; stage <= 5; stage++) {
        if (stage == 3) std::cout << "\n--- The Flop ---\n";
        else if (stage == 4) std::cout << "\n--- The Turn ---\n";
        else std::cout << "\n--- The River ---\n";

        showCommunityCards(communityCards, stage);

        for (int i = 0; i < activePlayers.size(); ++i) {
            if (activePlayers[i]) {
                char choice;
                std::cout << "Player " << i + 1 << ", do you want to fold? (y/n): ";
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    activePlayers[i] = false;
                    std::cout << "Player " << i + 1 << " has folded." << std::endl;
                }
            }
        }

        int activeCount = std::count(activePlayers.begin(), activePlayers.end(), true);
        if (activeCount <= 1) break;
    }

    std::vector<Hand3> playerBestHands;
    for (int i = 0; i < playerHoleCards.size(); ++i) {
        if (activePlayers[i]) {
            playerBestHands.push_back(getStrongest(playerHoleCards[i], communityCards));
        }
        else {
            playerBestHands.push_back({});
        }
    }

    for (int i = 0; i < playerBestHands.size(); ++i) {
        if (activePlayers[i]) {
            std::cout << std::endl << "Player " << i + 1 << "'s best hand: ";
            showHand(playerBestHands[i]);
        }
    }

    std::cout << std::endl << compareHands(playerBestHands, activePlayers) << std::endl;
}