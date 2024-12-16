#ifndef _MISERE_TIC_TAC_TOE_H
#define _MISERE_TIC_TAE_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include<cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename T>
class MisereTicTacToeBoard : public Board<T>{
    public:
    MisereTicTacToeBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    int n_moves;  
};
template <typename T>
class MisereTicTacToePlayer : public Player<T>{
public:
    MisereTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol){}
    void getmove(int& x, int& y);

};
template <typename T>
class MisereTicTacToeRandomPlayer : public RandomPlayer<T>{
public:
    MisereTicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol){
        this->dimension = 3;
        this->name = "Random computer player";
        srand(static_cast<unsigned int>(time(0)));
    }
    void getmove(int& x, int& y);
};

//.............IMPLEMENTATION
template <typename T>
MisereTicTacToeBoard<T>::MisereTicTacToeBoard(){
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++){
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++){
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
bool MisereTicTacToeBoard<T>::update_board(int  x, int y, T mark){
    
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)){
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}
template <typename T>
void MisereTicTacToeBoard<T>::display_board(){
    for (int i = 0; i < this->rows; i++){
        cout <<"\n|";
        for(int j = 0; j < this->columns; j++){
            cout << "(" << i << "," << j << ")";
            cout .width(2);
            cout << this->board[i][j] << " |";
            cout.width(0);
        }
        cout << "\n------------------------------";
    }
    cout << endl;

}
template <typename T>
bool MisereTicTacToeBoard<T>::is_win(){
    for (int i = 0; i < this->rows; i++){
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0)||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)){
            return true;
        }
    }
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0)||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)){
        return true;
    }
    return false;
}
template <typename T>
bool  MisereTicTacToeBoard<T>::is_draw(){
    return (this->n_moves == 9 && !is_win());
}
template <typename T>
bool MisereTicTacToeBoard<T>::game_is_over(){
    return is_win() || is_draw();
}
template <typename T>
void MisereTicTacToePlayer<T>::getmove(int& x, int& y){
    cout << "\n Please Enter your move X and Y (o-2) : ";
    cin >> x >> y;
}
template <typename T>
void MisereTicTacToeRandomPlayer<T>::getmove(int& x, int& y){
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif// Misere