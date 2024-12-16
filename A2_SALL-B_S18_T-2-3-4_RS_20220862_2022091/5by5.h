//DESCRIPTION: FIVE BY FIVE TIC TAC TOE GAME
//AUTHOR: RICHARD REMO EMMANUEL
//ID:20220862
//DATE: 12/12/2024
//VERSION: 2.0
//STATUS: COMPLETE
//COURSE:CS213
//=====================================
#ifndef FIVE_BY_FIVE_TIC_TAC_TOE_H
#define FIVE_BY_FIVE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//board implememtation
template<typename T>
class fiveTictac_Board : public Board<T>{
private:
    int check_direction(int x, int y, int dx, int dy, T symbol);
public:
    fiveTictac_Board();
    int count_three_in_row(T symbol);
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};
template <typename T>
fiveTictac_Board<T>::fiveTictac_Board(){
    this -> rows = 5;
    this -> columns = 5;
    this ->board = new T * [this->rows];
    for(int i = 0; i < this->rows; i++){
        this->board[i] = new T[this->columns];
        for(int j = 0; j <this->columns; j++){
            this->board[i][j] = '_';
        }
    }
    this->board[2][2] = '#';//middle box is bloced
}

template <typename T>
bool fiveTictac_Board<T>::update_board(int x, int y, T symbol){
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this -> board[x][y] == '_'){
        this->board[x][y] = symbol;
        ++this->n_moves;
        return true;
    } return false;
}
template< typename T>
void fiveTictac_Board<T>::display_board(){
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->columns; j++){
            cout<<"|"<<this->board[i][j];
        }
        cout<< "|"<<endl;
    }
}
template <typename T>
int fiveTictac_Board<T>::check_direction(int x, int y, int dx, int dy, T symbol){
    int count = 0;
    for (int i = 0; i < 3; ++i){
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx >= 0 && nx < this->rows && ny >= 0 && ny < this->columns && this->board[nx][ny] == symbol){
            ++count;
        }else {
            return 0;
        }
    }
    return count == 3 ? 1 : 0;
}
template <typename T>
int fiveTictac_Board<T>::count_three_in_row(T symbol){
    int count = 0;
    for(int i = 0; i < this->rows; ++i){
        for(int j = 0; j < this->columns; ++j){
            if(this->board[i][j] == symbol){
                count += check_direction(i, j, 1, 0, symbol); //vertical
                count += check_direction(i, j, 0, 1, symbol); // horizontal
                count += check_direction(i, j, 1, 1, symbol); //diagonal\
                count += check_direction(i, j, 1, -1, symbol);//diagonal/
            }
        }
    }
    return count;
}
template <typename T>
bool fiveTictac_Board<T>::is_win(){
    return false; //winning is determined by comparing scores, not a single winner
}
template <typename T>
bool fiveTictac_Board<T>::is_draw(){
    return this->n_moves == 24;
    
}
template <typename T>
bool fiveTictac_Board<T>::game_is_over(){
    return is_draw()||is_win();
}
template <typename T>
class Random_Player: public RandomPlayer<T>{
public:
    Random_Player(T symbol) : RandomPlayer<T>(symbol){
        srand(time(0));
    }
    void getmove(int& x, int& y) override{
        bool validmove = false;
        while(!validmove){
            x = rand() % 5;
            y = rand() % 5;
            if(x == 2 && y == 2) continue;
            //check if the board position is valid and empty
            if(this -> boardPtr->update_board(x, y, this->symbol)){
                validmove =true;
            }
        }
    }
};

template <typename T>
class HumanPlayer: public Player<T>{
public:
   HumanPlayer(T symbol) : Player<T>(symbol){}
   void getmove(int& x, int& y) override{
    bool validMove = false;
    while(!validMove){
        cout<<"Enter your move (row and column, 0 - indexed): ";
        cin>>x>>y;
        if(this->boardPtr->update_board(x, y, this->symbol)){
            validMove = true;
        } else{
            cout <<"Invalid move. try agaian.\n";
        }
    }
   }
};
#endif //FIVE_BY_FIVE_TIC_TAC_TOE_H