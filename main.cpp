#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;
class Card {
    const int id;
    static double noCardsCreated;
    string symbol;
    string rank;
    char* color;
    bool isFaceUp;
public:
    Card();
    Card(string,string,char*, bool);
    ~Card();
    Card(const Card&);
    Card& operator=(const Card& obj);
    friend std::ostream& operator<<(std::ostream& os, const Card& obj);
    const char* getColor() const;
    bool getIsFaceUp() const;
    string getSymbol() const ;
    string getRank() const ;
};

class Player {
    const double id;
    string name;
    int* maxScore;
    float average;
};
double Card::noCardsCreated=0;
Card::Card( string symbol,string rank,char* color, bool isFaceUp):id(++noCardsCreated){
    this->isFaceUp=isFaceUp;
    this->symbol=symbol;
    this->rank=rank;
    this->color=strcpy(new char[strlen(color)+1],color);
};
Card::Card():id(++noCardsCreated){
    isFaceUp=false;
    symbol="N/A";
    rank="N/A";
    color=strcpy(new char[4], "N/A");
}
Card::~Card() {
    delete [] color;
}
Card& Card::operator=(const Card& obj){
    if (this==&obj) return *this;
    delete[] color;

    isFaceUp=obj.isFaceUp;
    symbol=obj.symbol;
    rank=obj.rank;
    color=strcpy(new char[strlen(obj.color)+1],obj.color);
    return *this;
};
Card::Card(const Card& obj):id(++noCardsCreated){
    isFaceUp=obj.isFaceUp;
    symbol=obj.symbol;
    rank=obj.rank;
    color=strcpy(new char[strlen(obj.color)+1],obj.color);
}
std::ostream& operator<<(std::ostream& out, const Card& obj){
    if (obj.getIsFaceUp()==false) {
        out<<"(---)"<<endl;
    }
    else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleOutputCP(CP_UTF8);
        if (obj.getColor()[0]=='R') {
            SetConsoleTextAttribute(hConsole, 12);
            SetConsoleOutputCP(CP_UTF8);
            out<<"( "<<obj.getRank()<<obj.getSymbol()<<" )"<<endl;
            SetConsoleTextAttribute(hConsole, 7);
        }
        else{
            out<<"( "<<obj.getRank()<<obj.getSymbol()<<" )"<<endl;
        }
    }
    return out;
};
const char* Card::getColor() const {
    return color;
}
bool Card::getIsFaceUp() const {
    return isFaceUp;
}
string Card::getSymbol() const {
    return symbol;
}
string Card::getRank() const {
    return rank;
}
class Deck {
    int noCards;
    vector<Card> deck;
public:
    Deck();
    Deck(int noCards);
    Deck(const Deck& obj);
    Deck& operator=(const Deck& obj);
    ~Deck();
    friend std::ostream& operator<<(std::ostream& os, const Deck& obj);

};
Deck::Deck() {
    noCards=0;
};
Deck::~Deck() {

}
Deck::Deck(int noCards) {
    this->noCards= noCards;
    int startCard=(-noCards/4+13)+1;
    string symbol[]={"\u2660","\u2663","\u2665","\u2666"};
    for (int j=0;j<2;j++)
        for (int i=startCard;i<=13;i++) {
            if (i==startCard) {
                deck.push_back(Card(symbol[j],"A","B",true));
            }
            else if (i==11) {
                deck.push_back(Card(symbol[j],"J","B",true));
            }
            else if (i==12) {
                deck.push_back(Card(symbol[j],"Q","B",true));
            }
            else if (i==13) {
                deck.push_back(Card(symbol[j],"K","B",true));
            }
            else {
                deck.push_back(Card(symbol[j],to_string(i),"B",true));
            }
        }
    for (int j=2;j<4;j++)
        for (int i=startCard;i<=13;i++) {
            if (i==startCard) {
                deck.push_back(Card(symbol[j],"A","R",true));
            }
            else if (i==11) {
                deck.push_back(Card(symbol[j],"J","R",true));
            }
            else if (i==12) {
                deck.push_back(Card(symbol[j],"Q","R",true));
            }
            else if (i==13) {
                deck.push_back(Card(symbol[j],"K","R",true));
            }
            else {
                deck.push_back(Card(symbol[j],to_string(i),"R",true));
            }
        }

}
Deck::Deck(const Deck& obj) {
    noCards= obj.noCards;
    deck=obj.deck;
}
Deck& Deck::operator=(const Deck& obj) {
    if (this==&obj) return *this;
    noCards= obj.noCards;
    deck=obj.deck;
    return *this;
}
std::ostream& operator<<(std::ostream& out, const Deck& obj) {
    out<<obj.noCards<<endl;
    for (int i=0;i<obj.deck.size();i++) {
        cout<<obj.deck[i]<<"  ";
    }
    return out;
}
int main() {
    Card a("\u2665","K","R",true),b("\u2660","Q","B",true);
    Card c=b;
    Deck d(36),f(52);
    Deck r=f;
    cout<<r<<endl;
    r=d;
    cout<<r<<endl;
};
