#include <iostream>
#include <ctime>     
#include <cstdlib>   
#include <algorithm>
#include <map>
#include <fstream>
#include <vector>
#include <sstream> //stringstream

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
        Point["2"]=4;
        Point["3"]=5;
        Point["4"]=6;
        Point["5"]=7;
        Point["6"]=8;
        Point["7"]=9;
        Point["8"]=10;
        Point["9"]=11;
        Point["10"]=12;
        Point["J"]=13;
        Point["Q"]=14;
        Point["K"]=15;
        Point["A"]=16; 
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
    sort(player.cards,player.cards+5,cmp); //check card 1 2 3 4 5 case
    point p;
    if(player.cards[0].rank == "2" && player.cards[1].rank == "3" && player.cards[2].rank == "4" && player.cards[3].rank == "5" && player.cards[4].rank == "A"){
        return true;
    }
    for(int i=1;i<5;i++){ // 3 4 5 6
        if(p.Point[player.cards[i].rank]!=p.Point[player.cards[i-1].rank]+1 || p.Point[player.cards[i].suit]!=p.Point[player.cards[i-1].suit] ){
            return false;
        }
    }
    return true; 
}

bool four_of_a_kind(Hand player){ //save the value of the four_of_kind for later comparison
    map<string,int>cnt; //card type and frequency
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
    map<string,int>cnt; //save value of pair 2 and pair 3, for later comparison
    int note=0;
    for(int i=0;i<5;i++){
        cnt[player.cards[i].rank]++;
    }
    int check=0;
    for(auto x:cnt){
        if(x.second==3){
            check++;
        }
        else if(x.second==2 && note==0){ //2 doi 
            check++;
            note=1; //checkpoint
        }
    }
    if(check==2){
        return true;
    }
    return false;
}

bool flush(Hand player){
    map<string,int>cnt; //card suit and frequency
    for(int i=0;i<5;i++){
        cnt[player.cards[i].suit]++;
    }
    auto it=cnt.begin(); //iterator
    if(it->second==5){
        return true;
    }
    return false;
}

bool straight(Hand player){ 
    sort(player.cards,player.cards+5,cmp);
    point p; //1 2 3 4 5 
    for(int i=1;i<5;i++){
        if(p.Point[player.cards[i].rank]!=p.Point[player.cards[i-1].rank]+1){
            return false;
        }
    }
    return true; 
}

bool three_of_a_kind(Hand player){ //save the value of three_of_kind for later comparison
    map<string,int>cnt; //first type, second frequency
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

bool two_pair(Hand player){ //save 2 pair and save it in descending 
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

bool one_pair(Hand player){//save 1 pair
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

int compare_hand(Hand a, Hand b){ //hand array[5]
    sort(a.cards,a.cards+5,cmp); //sort hand 1
    sort(b.cards,b.cards+5,cmp); //tang dan
    point pnt;
    for(int i=4;i>=0;i--){ 
        if(pnt.Point[a.cards[i].rank] < pnt.Point[b.cards[i].rank]){ //
            return 2;
        }
        else if(pnt.Point[a.cards[i].rank] > pnt.Point[b.cards[i].rank]){
            return 1;
        }
    }
    return 0; //draw 
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

pair<int,pair<int,int>> take_pair(Hand a){
    pair <int,pair<int,int>> res = {0,{0,0}};
    map <string, int> store;
    point p;
    for(int i = 0; i < 5; i++){
        store[a.cards[i].rank]++;
    }
    for(auto x : store){
        if(x.second == 3){
            res.first = p.Point[x.first];
        }
        else if(x.second == 2 || x.second == 4){
            int tmp = res.second.first;
            if(p.Point[x.first] > res.second.first){
                res.second.second = res.second.first;
                res.second.first = p.Point[x.first];
            }
            else{
                res.second.second = p.Point[x.first];
            }
        }
    }
    return res;
}

//we must check the edge cases that the hand return same point.
//so we need to have a comparing function that trace both hand to check.
//if we reach the difference đầu tiên của 2 bộ bài về mặt rank thì so sánh cái nào lớn hơn thì win.
//nhưng nếu các rank bài y chang nhau thì là hòa.

int check_strength(Hand hand) { //tao enum o tren, xai switch case
    if (straight_flush(hand)) return 9;   
    else if (four_of_a_kind(hand)) return 8;    
    else if (full_house(hand)) return 7;    
    else if (flush(hand)) return 6;             
    else if (straight(hand)) return 5;         
    else if (three_of_a_kind(hand)) return 4;   
    else if (two_pair(hand)) return 3;          
    else if (one_pair(hand)) return 2;      
    return 1;                                 
}

pair<int,int> get_winner(Hand* players, int num_players) { //pointer to player[num_players]
    int max= 0;//luu diem cao nhat
    int winner = 0;//luu player_pos
    int strength;
    bool checktie=false; //check hoa

    for (int i = 0; i < num_players; ++i) {
        strength = check_strength(players[i]); //hand 0
        if (strength > max) {
            max = strength;
            winner = i;
            checktie=false;
        }
        else if(strength == max){
            pair <int,pair<int,int>> winner_tmp;
            pair <int,pair<int,int>> recent_player;
            
            winner_tmp = take_pair(players[winner]); //checking the pair before 
            recent_player = take_pair(players[i]);
            if(winner_tmp.first < recent_player.first){
                max = strength;
                winner = i;
                checktie = false;
                cout<<"checkdebug";
                continue;
            }
            else if(winner_tmp.second.first < recent_player.second.first){ //checking if it have full_house (pair of 3 and 2)
                max = strength;
                winner = i;
                checktie = false;
                cout<<"checkdebug";
                continue;
            }
            else if(winner_tmp.second.second < recent_player.second.second){
                max = strength;
                winner = i;
                checktie = false;
                cout<<"checkdebug";
                continue;
            }

            int checkpnt = compare_hand(players[winner],players[i]); // max truoc do vs thang hien tai

            if(checkpnt==2){ // max hien tai > max truoc do
                max=strength;
                winner=i; 
                checktie = false;
            }
            else if(checkpnt==0){
                checktie=true; // checkpoint hoa
            }
        }
    }

    if(checktie){
        return {0, max}; // pair la {0,max};
    }

    return {winner+1,max}; // {1,max}
}

void update_player_data(const string player_name, bool win, int hand_type){
    string filename = "player_" + player_name + ".txt"; //player_danh.txt
    int favorite_hand; 
    int games_played = 0, wins = 0;
    map<int, int> most_win_strategy;
    multimap<int, int, greater<int>> most_win_strategy2; //sap xep dua 
    int type, cnt;
    int have_strategy = false;

    ifstream file_in(filename); //mở file
    if(file_in){ //check coi co chua 
        file_in >> games_played >> wins; //lấy dữ liệu cũ
         //remember that winrate will automatically calculate when you call it the calculus is 1.0*(wins/game_played)*100
        while(file_in >> type >> cnt){ 
            //I will store consequently in the txt file that: cardtype1 -> cnt of previous type (largest cnt) -> cardtype2 -> cnt of previous type (second largest)...        
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
        most_win_strategy2.emplace(x.second,x.first);
    }

    games_played++;

    if(win){
        wins++;
    }

    ofstream file_out(filename);
    file_out << games_played << ' ' << wins << ' ';
    for(auto x: most_win_strategy2){
        file_out << x.second << ' ' << x.first << ' ';
    }
    file_out.close();
}

void update_playerlist(const string player_name, float win_rate){
    ifstream file_in("leadership.txt");
    multimap <float, string, greater<float>> store;
    bool check_update, check_change = false;
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
                            check_change = true;
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
    if(!check_change){
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
            cout << "Nhap ten nguoi choi " << i+1 << " :";
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
                cout<<x.suit<<" "<<x.rank<<" ";
            }
            cout<<endl;
        }

        bool wintype;

        for(int i = 0; i < number_player; i++){
            wintype = false;
            if((i + 1) == winner_pos){
                wintype = true;
            }
            else if(winner_pos == 0){
                wintype = true;
            }
            update_player_data(store_name[i], wintype, winner_strength);
            update_playerlist(store_name[i], get_win_rate(store_name[i]));
        }
        if(x.first==0){
            cout<<"TIE"<<endl;
        }
        else{
            cout<<"player "<<winner_pos<<" win"<<" "<<winner_strength<<endl;
        }
        cout<<"______________________________________________________"<<endl;
        cout<<"Play again or not (Y/N)";
        cin >> check;
    }while(check == 'Y' || check == 'y');
   

    return 0;
}
