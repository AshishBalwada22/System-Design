// template method pattern
// game -> play() , all other functions are implemented by inherited class, fixed number of steps.
// defines the skeleton of an algorithm in an operation, deferring some steps to subclasses

#include<bits/stdc++.h>
using namespace std;

class game{
    public:
    virtual ~game() = default;
    void play(){
        init();
        while(!isGameOver()){
            makeMove();
        }
        showResult();
    }
    virtual void init() = 0;
    virtual bool isGameOver() = 0;
    virtual void makeMove() = 0;
    virtual void showResult() = 0;
};

class ticTacToe : public game{
    int move;
    const int maxMove = 6;
    public:
    void init() override{
        cout<<"tictactoe game is started"<<endl;
        move=0;
    }
    bool isGameOver() override{
        if(move>=maxMove) return true;
        return false;
    }
    void makeMove() override{
        move++;
        cout<<"player did move : "<<move<<endl;
    }
    void showResult() override{
        cout<<"game is over"<<endl;
    }
};

int main(){
    unique_ptr<game> gameObj = make_unique<ticTacToe>();
    gameObj->play();
}