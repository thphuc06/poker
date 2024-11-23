#include "fullDeclare.h"

// shuffle cards
void shuffle_cards(Card deck[], int n)
{
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        int r = i + rand() % (n - i); // pick randomly number from i->(n-i-1)+i
        swap(deck[i], deck[r]); //https://www.w3schools.com/cpp/cpp_howto_random_number.asp
    }
}

// dealing funtion
Hand* dealing_cards(Card desk[52], int num_players)
{
    // assuming that we have 2 players;
    Hand* hands = new Hand[num_players];
    int idx = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < num_players; j++)
        {
            hands[j].cards[i] = desk[idx];
            idx++;
        }
    }
    return hands;
}

// make a structure that store a map of strength based on card ranks & card suit
point::point()
{
    Point["spades"] = 3;
    Point["hearts"] = 2;
    Point["diamonds"] = 1;
    Point["clubs"] = 0;
    Point["2"] = 4;
    Point["3"] = 5;
    Point["4"] = 6;
    Point["5"] = 7;
    Point["6"] = 8;
    Point["7"] = 9;
    Point["8"] = 10;
    Point["9"] = 11;
    Point["10"] = 12;
    Point["jack"] = 13;
    Point["queen"] = 14;
    Point["king"] = 15;
    Point["ace"] = 16;
}
point p;

bool cmp(Card a, Card b)
{
    int rankA = p.Point[a.rank];
    int rankB = p.Point[b.rank];

    if (rankA != rankB)
    {
        return rankA < rankB;
    }

    return p.Point[a.suit] < p.Point[b.suit];
}

bool straight_flush(Hand player)
{                                              // we check this first after check straight to assure that we do not miss any error
    sort(player.cards, player.cards + 5, cmp); // check card 1 2 3 4 5 case
    if (player.cards[0].rank == "2" && player.cards[1].rank == "3" && player.cards[2].rank == "4" && player.cards[3].rank == "5" && player.cards[4].rank == "A")
    {
        return true;
    }
    for (int i = 1; i < 5; i++)
    { // 3 4 5 6
        if (p.Point[player.cards[i].rank] != p.Point[player.cards[i - 1].rank] + 1 || p.Point[player.cards[i].suit] != p.Point[player.cards[i - 1].suit])
        {
            return false;
        }
    }
    return true;
}

bool four_of_a_kind(Hand player)
{                         // save the value of the four_of_kind for later comparison
    map<string, int> cnt; // card type and frequency
    for (int i = 0; i < 5; i++)
    {
        cnt[player.cards[i].rank]++;
    }
    for (auto x : cnt)
    {
        if (x.second == 4)
        {
            return true;
        }
    }
    return false;
}

bool full_house(Hand player)
{                         // remember to check this before check the three of a kind
    map<string, int> cnt; // save value of pair 2 and pair 3, for later comparison
    int note = 0;
    for (int i = 0; i < 5; i++)
    {
        cnt[player.cards[i].rank]++;
    }
    int check = 0;
    for (auto x : cnt)
    {
        if (x.second == 3)
        {
            check++;
        }
        else if (x.second == 2 && note == 0)
        { // 2 doi
            check++;
            note = 1; // checkpoint
        }
    }
    if (check == 2)
    {
        return true;
    }
    return false;
}

bool flush(Hand player)
{
    map<string, int> cnt; // card suit and frequency
    for (int i = 0; i < 5; i++)
    {
        cnt[player.cards[i].suit]++;
    }
    auto it = cnt.begin(); // iterator
    if (it->second == 5)
    {
        return true;
    }
    return false;
}

bool straight(Hand player)
{
    sort(player.cards, player.cards + 5, cmp);
    // 1 2 3 4 5
    for (int i = 1; i < 5; i++)
    {
        if (p.Point[player.cards[i].rank] != p.Point[player.cards[i - 1].rank] + 1)
        {
            return false;
        }
    }
    return true;
}

bool three_of_a_kind(Hand player)
{                         // save the value of three_of_kind for later comparison
    map<string, int> cnt; // first type, second frequency

    for (int i = 0; i < 5; i++)
    {
        cnt[player.cards[i].rank]++;
    }
    for (auto x : cnt)
    {
        if (x.second == 3)
        {
            return true;
        }
    }
    return false;
}

bool two_pair(Hand player)
{ // save 2 pair and save it in descending
    map<string, int> cnt;

    for (int i = 0; i < 5; i++)
    {
        cnt[player.cards[i].rank]++;
    }
    int check = 0;
    for (auto x : cnt)
    {
        if (x.second == 2)
        {
            check++;
        }
    }
    if (check == 2)
    {
        return true;
    }
    return false;
}

bool one_pair(Hand player)
{ // save 1 pair
    map<string, int> cnt;

    for (int i = 0; i < 5; i++)
    {
        cnt[player.cards[i].rank]++;
    }
    int check = 0;
    for (auto x : cnt)
    {
        if (x.second == 2)
        {
            check++;
        }
    }
    if (check == 1)
    {
        return true;
    }
    return false;
}

int compare_hand(Hand a, Hand b)
{                                    // hand array[5]
    sort(a.cards, a.cards + 5, cmp); // sort hand 1
    sort(b.cards, b.cards + 5, cmp); // tang dan

    for (int i = 0; i < 5; i++)
    {
        cout << a.cards[i].rank << " ";
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << b.cards[i].rank << " ";
    }

    for (int i = 4; i >= 0; i--)
    {
        if (p.Point[a.cards[i].rank] < p.Point[b.cards[i].rank])
        { //
            return 2;
        }
        else if (p.Point[a.cards[i].rank] > p.Point[b.cards[i].rank])
        {
            return 1;
        }
    }
    return 0; // draw
}

/*
-I will make this function to ensure the edge case if 2 hand have the same card strength, and they have pairs
-The function will return a pair {pair 1, pair 2}, why it have pair 2 because I want to hold the pair of 2 and pair of 3 when full_house occur,
    if not just save as {pair1, 0} so that when compare 0 = 0 and does not affect the result.
-This function will be call when two hand card strength is equal, when the strength is:
8 : save the pair of 4
7 : save the pair of 3 and pair of 2
4 : save the pair of 3
3 : save the max of 2 pair
2 : save the value of 1 pair
-when 2 card strength is equal -> call this function to get the value of recent card for comparison (in the get_winner function, get the winner_pos for access player card)
after that
*/

pair<int, pair<int, int>> take_pair(Hand a)
{
    pair<int, pair<int, int>> res = { 0, {0, 0} };
    map<string, int> store;

    for (int i = 0; i < 5; i++)
    {
        store[a.cards[i].rank]++;
    }
    for (auto x : store)
    {
        if (x.second == 3)
        {
            res.first = p.Point[x.first];
        }
        else if (x.second == 2 || x.second == 4)
        {
            int tmp = res.second.first;
            if (p.Point[x.first] > res.second.first)
            {
                res.second.second = res.second.first;
                res.second.first = p.Point[x.first];
            }
            else
            {
                res.second.second = p.Point[x.first];
            }
        }
    }
    return res;
}

// we must check the edge cases that the hand return same point.
// so we need to have a comparing function that trace both hand to check.
// if we reach the difference dâ`u tiên cu?a 2 bô? ba`i vê` ma?t rank thi` so sa´nh ca´i na`o lo´n hon thi` win.
// nhung nê´u ca´c rank ba`i y chang nhau thi` la` ho`a.

int check_strength(Hand hand)
{ // tao enum o tren, xai switch case
    if (straight_flush(hand))
        return 9;
    else if (four_of_a_kind(hand))
        return 8;
    else if (full_house(hand))
        return 7;
    else if (flush(hand))
        return 6;
    else if (straight(hand))
        return 5;
    else if (three_of_a_kind(hand))
        return 4;
    else if (two_pair(hand))
        return 3;
    else if (one_pair(hand))
        return 2;
    return 1;
}

string type_of_card(int score)
{
    switch (score)
    {
    case 1:
        return "Normal";
    case 2:
        return "one pair";
    case 3:
        return "two pair";
    case 4:
        return "three of a kind";
    case 5:
        return "straight";
    case 6:
        return "flush";
    case 7:
        return "full house";
    case 8:
        return "four of a kind";
    case 9:
        return "straight flush";
    }
    return "";
}

pair<pair<int, int>,int> get_winner(Hand* players, int num_players)
{                   // pointer to player[num_players]
    int max = 0;    // luu diem cao nhat
    int winner = 0; // luu player_pos
    int winner_draw = 0;
    int strength;
    bool checktie = false; // check hoa

    for (int i = 0; i < num_players; ++i)
    {
        strength = check_strength(players[i]); // hand 0
        if (strength > max)
        {
            max = strength;
            winner = i;
            checktie = false;
        }
        else if (strength == max)
        {
            pair<int, pair<int, int>> winner_tmp;
            pair<int, pair<int, int>> recent_player;

            winner_tmp = take_pair(players[winner]); // checking the pair before
            recent_player = take_pair(players[i]);
            if (winner_tmp.first < recent_player.first) // Compare the three-of-a-kind first
            {
                max = strength;
                winner = i;
                checktie = false;

                cout << "checkdebug (three-of-a-kind comparison)";
            }
            else if (winner_tmp.first == recent_player.first && winner_tmp.second.first < recent_player.second.first) // Compare the first pair
            {
                max = strength;
                winner = i;
                checktie = false;

                cout << winner_tmp.second.first << " " << recent_player.second.first;
                cout << "checkdebug (first pair comparison)";
            }
            else if (winner_tmp.first == recent_player.first && winner_tmp.second.first == recent_player.second.first && winner_tmp.second.second < recent_player.second.second) // Compare the second pair
            {
                max = strength;
                winner = i;
                checktie = false;

                cout << "checkdebug (second pair comparison)";
            }
            else if (winner_tmp.first == recent_player.first && winner_tmp.second.first == recent_player.second.first && winner_tmp.second.second == recent_player.second.second)
            {

                int checkpnt = compare_hand(players[winner], players[i]); // max truoc do vs thang hien tai

                /*
                * remember if it have same pair, do not use it as a kicker for checking one more time, we must delete it out 
                * but in this code, it may be redundant but it actually covers this checking step since I have tested all test case
                */

                if (checkpnt == 2)
                { // max hien tai > max truoc do
                    max = strength;
                    winner = i;
                    cout << "outplay card at same strength";
                    checktie = false;
                }
                else if (checkpnt == 0)
                {
                    checktie = true; // checkpoint hoa
                    winner_draw = i;
                }
            }
            // thêm else ở đây vô, tránh trường hợp so sánh tiếp khi đôi trước đó lớn hơn đôi hiện tại.
        }
    }

    if (checktie)
    {
        return {{winner + 1, winner_draw + 1}, max}; // if draw get 2 position for display and update score
    }

    return { {winner + 1, -1}, max }; // make sure that pair position in the second must be -1 for further checking func
}

void update_player_data(const string player_name, bool win, int hand_type)
{
    string filename = "C:/HCMUS/vspoker/userprofile/player_" + player_name + ".txt"; // player_danh.txt
    int favorite_hand;
    int games_played = 0, wins = 0;
    map<int, int> most_win_strategy;
    multimap<int, int, greater<int>> most_win_strategy2; // sap xep dua
    int type, cnt;
    int have_strategy = false;

    ifstream file_in(filename); //
    if (file_in)
    { // check coi co chua
        file_in >> games_played >> wins;
        // remember that winrate will automatically calculate when you call it the calculus is 1.0*(wins/game_played)*100
        while (file_in >> type >> cnt)
        {
            // I will store consequently in the txt file that: cardtype1 -> cnt of previous type (largest cnt) -> cardtype2 -> cnt of previous type (second largest)...
            if (type == hand_type && win)
            {
                cnt++;
                have_strategy = true;
            }
            most_win_strategy[type] = cnt; // this will store the card type key and its value is its frequency
        }
        file_in.close();
    }

    if (win && !have_strategy)
        most_win_strategy[hand_type] = 1;

    for (auto x : most_win_strategy)
    {
        most_win_strategy2.emplace(x.second, x.first);
    }

    games_played++;

    if (win)
    {
        wins++;
    }

    ofstream file_out(filename);
    file_out << games_played << ' ' << wins << ' ';
    for (auto x : most_win_strategy2)
    {
        file_out << x.second << ' ' << x.first << ' ';
    }
    file_out.close();
}

void update_player_win_rate(const string player_name, float win_rate)
{
    ifstream file_in("C:/HCMUS/vspoker/Leaderboard/leaderboard.txt");
    multimap<float, string, greater<float>> store; //use multimap for avoiding deleting player with same winrate
    bool check_change = false;
    if (file_in)
    {
        float percent;
        string name;
        string s;

        while (getline(file_in, s))
        {
            stringstream ss(s);
            string tmp = "";
            int cnt = 1;

            //while (getline(ss, tmp, '-'))
            //{ // this mean I will store in the leadership text: name - winrate \n name - winrate ....
            //    switch (cnt)
            //    {
            //    case 1:
            //        name = tmp;
            //        if (name == player_name)
            //        {
            //            check_update = true; //if you find ...
            //        }
            //        break;
            //    case 2:
            //        if (check_update)
            //        {
            //            percent = win_rate;
            //            check_change = true; 
            //            break;
            //        }
            //        percent = stof(tmp);
            //        break;
            //    }
            //    cnt++;
            //}

            getline(ss, tmp, '-');
            name = tmp;
            if (name == player_name) {
                check_change = true;
                percent = win_rate;
                store.emplace(percent, name);
                continue;
            }
            ss >> percent;

            store.emplace(percent, name);
        }
        file_in.close();
    }
    if (!check_change)
    {
        store.emplace(win_rate, player_name);
    }

    ofstream file_out("C:/HCMUS/vspoker/Leaderboard/leaderboard.txt");
    for (auto x : store)
    {
        file_out << x.second << '-' << x.first << endl;
    }
    file_out.close();
}

void update_player_win_game(const string player_name, int win_game) { //read the file of leadership_win_game and check if it match the name update the win_game, else append in the map for sorting win_game.
    //I will store in the file:    name-wingame \n name-wingaem \n with descending order so that the top 1 will at first for easy graphic designing.
    ifstream file_in("C:/HCMUS/vspoker/Leaderboard/leaderboard_win_rate.txt");

    multimap<int, string, greater<int>>store;

    bool check_update = false;
    string s;
    string name;
    int wins;

    while (getline(file_in, s)) { //use s for catching full line
        string tmp = "";
        
        stringstream ss(s); 

        getline(ss, tmp, '-');
        name = tmp;
        
        if (name == player_name) {
            wins = win_game;

            check_update = true;

            store.emplace(wins, name);

        }
        else
        {
            ss >> wins;

            store.emplace(wins, name);
        }
    }
    file_in.close();
    if (!check_update) {
        store.emplace(win_game, player_name);
    }

    ofstream file_out("C:/HCMUS/vspoker/Leaderboard/leaderboard_win_rate.txt");
    for (auto x : store)
    {
        file_out << x.second << '-' << x.first << endl;
    }
    file_out.close();
}

float get_win_rate(const string player_name)
{
    string filename = "C:/HCMUS/vspoker/userprofile/player_" + player_name + ".txt";
    ifstream file_in(filename);
    int games_play = 0, wins = 0;
    if (file_in)
    {
        file_in >> games_play >> wins;
        file_in.close();
    }
    if (games_play == 0)
    {
        return 0.0; // Return 0% win rate if no games have been played
    }
    return (1.0 * wins / games_play) * 100;
}

int get_win_game(const string player_name)
{
    string filename = "C:/HCMUS/vspoker/userprofile/player_" + player_name + ".txt";
    ifstream file_in(filename);
    int games_play = 0, wins = 0;
    if (file_in)
    {
        file_in >> games_play >> wins;
        file_in.close();
    }
    return wins;
}