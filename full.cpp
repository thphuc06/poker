#include <iostream>
#include <ctime>     
#include <cstdlib>   
#include <algorithm>
#include <map>

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

Hand *dealing_cards(Card desk[52]){
    //assuming that we have 2 players;
    Hand *hands=new Hand[2];
    int idx=0;
    for(int i=0; i<5;i++){
        for(int j=0;j<2;j++){
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
        Point["2"]=15;
    }
};


bool cmp(Card a, Card b){
    point p;
    if(a.rank==b.rank){
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
    for(int i=0;i<5;i++){
        cnt[player.cards[i].rank]++;
    }
    int check=0;
    for(auto x:cnt){
        if(x.second==3){
            check++;
        }
        else if(x.second==2){
            check++;
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

//we must check the edge cases that the hand return same point.
//so we need to have a comparing function that trace both hand to check.
//if we reach the difference đầu tiên của 2 bộ bài về mặt rank thì so sánh cái nào lớn hơn thì win.
//nhưng nếu các rank bài y chang nhau thì là hòa.

int check_strength(Hand hand) {
    if (straight_flush(hand)) return 9;   
    if (four_of_a_kind(hand)) return 8;    
    if (full_house(hand)) return 7;    
    if (flush(hand)) return 6;             
    if (straight(hand)) return 5;         
    if (three_of_a_kind(hand)) return 4;   
    if (two_pair(hand)) return 3;          
    if (one_pair(hand)) return 2;          
    return 1;                                 
}

pair<int,int> get_winner(Hand* players, int num_players) {
    int max= 0;
    int winner = 0;
    int strength;

    for (int i = 0; i < num_players; ++i) {
        strength = check_strength(players[i]);
        if (strength > max) {
            max = strength;
            winner = i;
        }
    }

    return {winner,strength}; 
}


int main() {
    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    Card deck[52]; 

    int index = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            deck[index].suit = suits[i];
            deck[index].rank = ranks[j];
            ++index;
        }
    }
    shuffle_cards(deck, 52);

    Hand *p=dealing_cards(deck); //tra ve vi tri cua hand cua moi nguoi
    auto x=get_winner(p,2);
    int winner_pos=x.first;
    int winner_strength=x.second;

    for(int i=0;i<2;i++){
        for(auto x:p[i].cards){
            cout<<x.suit<<" "<<x.rank<<endl;
        }
        cout<<"NEXT"<<endl;
    }

    cout<<"player "<<winner_pos+1<<" win"<<" "<<winner_strength<<endl;

    return 0;
}
