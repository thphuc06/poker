#include <iostream>
#include <ctime>     
#include <cstdlib>   
#include <algorithm>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Card {
    string suit;  
    string rank;  
};

struct Hand{
    Card cards[5];
};

void swap(Card &a, Card &b) {
    Card tmp = a;
    a = b;
    b = tmp;
}

void shuffle_cards(Card deck[], int n) {
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        int r = i + rand() % (n - i);  //hàm này có nghĩa là chọn ngẫu nhiên 1 số đi từ i->(n-i-1)+i
        swap(deck[i], deck[r]); 
    }
}

Hand *dealing_cards(Card desk[52], int num_players){
    //assuming that we have 2 players;
    Hand *hands=new Hand[num_players];
    int idx=0;
    for(int i=0; i<5;i++){
        for(int j=0;j<num_players;j++){
            hands[j].cards[i]=desk[idx];
            idx++;
        }
    }
    return hands;
}

struct point{
    map<string,int>Point;
    point(){
        Point["Spades"]=3;
        Point["Hearts"]=2;
        Point["Diamonds"] = 1;
        Point["Clubs"]=0;
        Point["3"]=4;
        Point["4"]=5;
        Point["5"]=6;
        Point["6"]=7;
        Point["7"]=8;
        Point["8"]=9;
        Point["9"]=10;
        Point["10"]=11;
        Point["J"]=12;
        Point["Q"]=13;
        Point["K"]=14;
        Point["A"]=15;
        Point["2"]=16;
    }
}; 


bool cmp(Card a, Card b){
    point p;
    if(p.Point[a.rank]==p.Point[b.rank]){
        return p.Point[a.suit]<p.Point[b.suit];
    }
    return p.Point[a.rank]<p.Point[b.rank];
}

bool straight_flush(Hand player){ //we check this first after check straight to assure that we do not miss any error
    sort(player.cards,player.cards+5,cmp);
    point p;
    for(int i=1;i<5;i++){
        if(p.Point[player.cards[i].rank]!=p.Point[player.cards[i-1].rank]+1 || p.Point[player.cards[i].suit]!=p.Point[player.cards[i-1].suit] ){
            return false;
        }
    }
    return true; 
}

bool four_of_a_kind(Hand player){
    map<string,int>cnt;
    for(int i=0;i<5;i++){
        cnt[player.cards[i].rank]++;
    }
    for(auto x:cnt){
        if(x.second==4){
            return true;
        }
    }
    return false;
}

bool full_house(Hand player){ //remember to check this before check the three of a kind
    map<string,int>cnt;
    int note=0;
    for(int i=0;i<5;i++){
        cnt[player.cards[i].rank]++;
    }
    int check=0;
    for(auto x:cnt){
        if(x.second==3){
            check++;
        }
        else if(x.second==2 && note==0){
            check++;
            note=1;
        }
    }
    if(check==2){
        return true;
    }
    return false;
}

bool flush(Hand player){
    map<string,int>cnt;
    for(int i=0;i<5;i++){
        cnt[player.cards[i].suit]++;
    }
    auto it=cnt.begin();
    if(it->second==5){
        return true;
    }
    return false;
}

bool straight(Hand player){ 
    sort(player.cards,player.cards+5,cmp);
    point p;
    for(int i=1;i<5;i++){
        if(p.Point[player.cards[i].rank]!=p.Point[player.cards[i-1].rank]+1){
            return false;
        }
    }
    return true; 
}

bool three_of_a_kind(Hand player){
    map<string,int>cnt;
    point p;
    for(int i=0;i<5;i++){
        cnt[player.cards[i].rank]++;
    }
    for(auto x:cnt){
        if(x.second==3){
            return true;
        }
    }
    return false;
}

bool two_pair(Hand player){
    map<string,int>cnt;
    point p;
    for(int i=0;i<5;i++){
        cnt[player.cards[i].rank]++;
    }
    int check=0;
    for(auto x:cnt){
        if(x.second==2){
            check++;
        }
    }
    if(check==2){
        return true;
    }
    return false;
}

bool one_pair(Hand player){
    map<string,int>cnt;
    point p;
    for(int i=0;i<5;i++){
        cnt[player.cards[i].rank]++;
    }
    int check=0;
    for(auto x:cnt){
        if(x.second==2){
            check++;
        }
    }
    if(check==1){
        return true;
    }
    return false;
}

int compare_hand(Hand a, Hand b){
    sort(a.cards,a.cards+5,cmp);
    sort(b.cards,b.cards+5,cmp);
    for(int i=4;i>=0;i--){
        if(a.cards[i].rank<b.cards[i].rank){
            return 2;
        }
        else if(a.cards[i].rank>b.cards[i].rank){
            return 1;
        }
    }
    return 0;
}

//we must check the edge cases that the hand return same point.
//so we need to have a comparing function that trace both hand to check.
//if we reach the difference đầu tiên của 2 bộ bài về mặt rank thì so sánh cái nào lớn hơn thì win.
//nhưng nếu các rank bài y chang nhau thì là hòa.

int check_strength(Hand hand) {
    if (straight_flush(hand)) return 9;   
    else if (four_of_a_kind(hand)) return 8;    
    else if (full_house(hand)) return 7;    
    else if (flush(hand)) return 6;             
    else if (straight(hand)) return 5;         
    else if (three_of_a_kind(hand)) return 4;   
    else if (two_pair(hand)) return 3;          
    else if (one_pair(hand)){ cout << "One Pair detected, returning 2 points." << endl;return 2;}        
    return 1;                                 
}

pair<int,int> get_winner(Hand* players, int num_players) {
    int max= 0;
    int winner = 0;
    int strength;
    bool checktie=false;

    for (int i = 0; i < num_players; ++i) {
        strength = check_strength(players[i]);
        if (strength > max) {
            max = strength;
            winner = i;
            checktie=false;
        }
        else if(strength == max){
            int checkpnt = compare_hand(players[winner],players[i]);
            if(checkpnt==2){
                max=strength;
                winner=i;
            }
            else if(checkpnt==0){
                checktie=true;
            }
        }
    }
    if(checktie){
        return {0,0};
    }

    return {winner,max}; 
}

void update_player_data(const string player_name, bool win, int hand_type){
    string filename = "player_" + player_name + ".txt";
    int favorite_hand; 
    int games_played = 0, wins = 0;
    map<int, int> most_win_strategy;
    map<int, int, greater<int>> most_win_strategy2;
    int type;
    int have_strategy = false;

    ifstream file_in(filename);
    if(file_in){
        file_in >> games_played >> wins;
         //remember that winrate will automatically calculate when you call it the calculus is 1.0*(wins/game_played)*100
        while(file_in >> type){
            int cnt;
            file_in >> cnt; //I will store consequently in the txt file that: cardtype1 -> cnt of previous type (largest cnt) -> cardtype2 -> cnt of previous type (second largest)...
            if(type == hand_type && win){
                cnt++;
                have_strategy = true;
            }
            most_win_strategy[type] = cnt; // this will store the card type key and its value is its frequency
        }
        file_in.close();
    }

    if(win && !have_strategy) most_win_strategy[hand_type] = 1;
    

    for(auto x: most_win_strategy){
        most_win_strategy2[x.second] = x.first;
    }

    games_played++;

    if(win){
        wins++;
    }

    ofstream file_out(filename);
    file_out << games_played << ' ' << wins << ' ';
    for(auto x: most_win_strategy2){
        file_out << x.second << ' ' << x.first;
    }
    file_out.close();
}

void update_playerlist(const string player_name, float win_rate){
    ifstream file_in("leadership.txt");
    multimap <float, string, greater<float>> store;
    bool check_update;
    if(file_in){
        float percent;
        string name;
        string s;
        
        while(getline(file_in, s)){
            check_update = false;
            stringstream ss(s);
            string tmp;
            int cnt = 1;
            while(getline(ss,tmp, '-')){  //this mean I will store in the leadership text: name - winrate \n name - winrate ....
                switch(cnt){
                    case 1:
                        name = tmp;
                        if(name == player_name){
                            check_update = true;
                        }
                        break;
                    case 2:
                        if(check_update){
                            percent = win_rate;
                            break;
                        }
                        percent = stof(tmp);                        
                        break;
                }
                cnt++;
            }
            store.emplace(percent, name);
        }
        file_in.close();
    }
    if(!check_update){
        store.emplace(win_rate, player_name);
    }

    ofstream file_out("leadership.txt");
    for(auto x: store){
        file_out << x.second << '-' << x.first << endl;
    }
    file_out.close();
}

float get_win_rate(const string player_name){
    string filename = "player_" + player_name + ".txt";
    ifstream file_in(filename);
    int games_play = 0, wins = 0;
    if(file_in){
        file_in >> games_play >> wins;
        file_in.close();
    }
    if (games_play == 0) {
        return 0.0; // Return 0% win rate if no games have been played
    }
    return (1.0*wins/games_play)*100;
}

int main() {
    int number_player;
    
    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    Card deck[52]; 
    char check;
    
    do {
        cout<<"NHAP SO LUONG NGUOI CHOI";

        cin>>number_player;
        cin.ignore();
        vector <string> store_name;
        //initializing name for n players
        for (int i = 0; i < number_player; i++){
            string name;
            getline(cin, name);
            store_name.push_back(name);
            //check if the name that exist in the datafile or not
            //if not exist -> write the name into the datafile name
            //make a file that named as a player name that can store the winrate, count the frequency of a player (n games), and also the favorite strategy.
            //the datafile name should have the rank of each person and if some one win the game update its winrate and compare with the largest rank and decrease one by one until reach the suitable rank (function)
        }

        int index = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 13; ++j) {
                deck[index].suit = suits[i];
                deck[index].rank = ranks[j];
                ++index;
            }
        }

        shuffle_cards(deck, 52);

        Hand *p=dealing_cards(deck,number_player); //tra ve vi tri cua hand cua moi nguoi
        auto x=get_winner(p,number_player);
        int winner_pos=x.first;
        int winner_strength=x.second;

        for(int i=0;i<number_player;i++){
            for(auto x:p[i].cards){
                cout<<x.suit<<" "<<x.rank<<endl;
            }
            cout<<"NEXT"<<endl;
        }
        if(x.first==0 && x.second==0){
            cout<<"TIE"<<endl;
            return 0;
        }

        bool wintype;

        for(int i = 0; i < number_player; i++){
            wintype = false;
            if(i == winner_pos){
                wintype = true;
            }
            update_player_data(store_name[i], wintype, winner_strength);
            update_playerlist(store_name[i], get_win_rate(store_name[i]));
        }
        cout<<"player "<<winner_pos+1<<" win"<<" "<<winner_strength<<endl;
        cout<<"______________________________________________________"<<endl;
        cout<<"Play again or not (Y/N)";
        cin >> check;
    }while(check == 'Y' || check == 'y');
   

    return 0;
}
