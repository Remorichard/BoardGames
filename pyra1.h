#ifndef PYRAMID_TIC_TAC_TOE_H
#define PYRAMID_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//class represent the pyramid tic tac board
class Pyramid_board: public Board<char>{
private:
    vector <vector<char>>board; // pyramid structure of the board
    bool check3_inrow(int x1, int y1,int x2, int y2, int x3, int y3, char sym) const; 
public:
    Pyramid_board();
    ~Pyramid_board();
    void display_board() override;
    bool update_board(int x, int y, char sym) override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

};

// class representing a huyman  player in pyramid tic tac toe
class Pyramid_player : public Player<char>{
public:
    Pyramid_player(const string& name, char sym) : Player<char>(name, sym) {}
    void getmove(int& x, int& y) override;
};

//class for a random a1 player in pyramid 
class Pyramid_ramdomPlayer : public RandomPlayer<char>{
public:
   Pyramid_ramdomPlayer(const string& name, char sym) : RandomPlayer<char>(sym){}
   void getmove(int& x, int& y) override;
};

//Implementation of pyramid board methods
Pyramid_board::Pyramid_board() {
    int row = 5;
    int column = 5;
    board = {
        {' '},
        {' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '}
    };
}
Pyramid_board::~Pyramid_board(){
    board.clear();
}

void Pyramid_board:: display_board(){
    for(int i = 0; i < board.size(); ++i){
        for(int j = 0; j < board[i].size(); ++j){
            cout << board[i][j];
            if(j < board[i].size() - 1) cout << " | ";
        }
        cout << endl;
        if (i < board.size() - 1) cout << string(4 * (board[i].size() - 1), '-')<<endl;
    }
}

bool Pyramid_board::update_board(int x, int y, char sym){
    if (x >= 0 && x < board.size() && y >= 0 && y < board[x].size() && board[x][y]==' '){
        board[x][y] = sym;
        n_moves++;
        return true;
    }
    return false;
}

bool Pyramid_board::is_win(){
    //check for win conditions in pyramid 
    char symbols[] = {'X', 'O'};
    for(char sym : symbols){
        if(check3_inrow(0, 0, 1, 1, 2, 2, sym) ||
           check3_inrow(0, 1, 1, 2, 2, 3, sym) ||
           check3_inrow(1, 0, 2, 1, 3, 2, sym) ||
           check3_inrow(1, 1, 2, 2, 3, 3, sym) ||
           check3_inrow(2, 0, 3, 1, 4, 2, sym) ||
           check3_inrow(2, 1, 3, 2, 4, 3, sym) ||
           check3_inrow(2, 2, 3, 3, 4, 4, sym)){
            return true;
        }
        return false;
    }
}

bool Pyramid_board::is_draw(){
    for (const auto& row : board){
        for(char cell : row){
            if (cell == ' ')return false;
        }
    }
    return true;
}

bool Pyramid_board::game_is_over(){
    return is_win() || is_draw();
}

bool Pyramid_board::check3_inrow(int x1, int y1, int x2, int y2, int x3, int y3, char sym) const {
    return board[x1][y1] == sym && board[x2][y2] == sym && board[x3][y3] == sym;
}

//pyramid player methods
void Pyramid_player::getmove(int& x, int& y){
    cout<<getname()<< "enter your move (level and postion)";
    cin>>x>>y;
    x--; y--;
}


// implemntation of pyramid random player methhods
void Pyramid_ramdomPlayer::getmove(int& x, int& y){
    do{
        x = rand() % 5;
        y = rand() % (x + 1); // Ensure valid position within the pyramid
    } while (!boardPtr->update_board(x, y, getsymbol()));
}    
#endif // PYRAMID_TIC_TAC_TOE_H

