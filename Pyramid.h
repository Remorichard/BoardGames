#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class PyramidBoard : public Board<T>{
public:
    PyramidBoard(){
        this->rows = 3;
        this->columns = 5;
        this->board = new T*[this->rows];
        for(int i = 0; i < this->rows; ++i){
            this->board[i] = new T[this->columns];
            fill(this->board[i], this->board[i] + this->columns, T());
        }
    }
    ~PyramidBoard(){
        for(int i = 0; i < this->rows; ++i){
            delete[] this->board[i];
        }
        delete[] this->board;
    }
    bool update_board(int x, int y, T symbol) override{
        if(x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != T()){
            return false;
        }
        //checking for valid pyramid position
        if((x == 0 && y != 2) || (x == 1 && (y < 1 || y > 3))){
            return false;
        }
        this->board[x][y] = symbol;
        ++this->n_moves;
        return true;
    }
    void display_board() override {
        for(int i = 0; i < this->rows; ++i){
            for(int j = 0; j < this->columns; ++j){
                if(i == 0 && j != 2) {
                    cout << " ";
                }else if (i == 1 && (j < 1 || j > 3)){
                    cout << " ";
                }else {
                    cout << this->board[i][j] << (j == this->columns - 1 ? "" : " | ");
                }
            }
            cout << endl;
            if(i != this->rows - 1){
                cout << string(this->columns * 2 - 1, '-') << endl;
            }
        }
    }
    bool is_win() override {
        return check_rows() || check_columns() || check_diagonals();
    }
    bool is_draw() override{
        return this->n_moves == 9 && !is_win();
    }
    bool game_is_over() override{
        return is_win() || is_draw();
    }
private:
    bool check_rows(){
        for(int i = 0; i < this->rows; ++i){
            if(i == 0 && this->board[i][2] != T() && this->board[i][2] == this->board[i + 1][1] && this->board[i + 1][1] == this->board[i + 2][0]) return true;
            if(i == 1 && this->board[i][1] != T() && this->board[i][1] == this->board[i][2] && this->board[i][2] == this->board[i][3]) return true;
        }
        return false;
    }    
    bool check_columns() {
        for(int i = 0; i < this->columns; ++i){
            if(i == 2 && this->board[0][2] != T() && this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2]) return true;
        }return false;
    }
    bool check_diagonals(){
        return(this->board[0][2] != T() && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]) ||
              (this->board[0][2] != T() && this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4]);
    }
};
template <typename T>
class Human_Player : public Player<T>{
public: 
    Human_Player(string name, T symbol) : Player<T>(name, symbol){}
    void getmove(int& x, int& y) override {
        cout << this->name << " (" << this->symbol << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};
template <typename T>
class Random_PlayerIm : public RandomPlayer<T> {
private: 
    bool isvalid_position(int x, int y){
        // check bounds and the pyramid structure
        return !(x < 0 || x > 2 || y < 0 || y > 4||
                 (x == 0 && y != 2) ||
                 (x == 1 && (y < 1 || y > 3)));
    }
public:    
    Random_PlayerIm(T symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int& x, int& y) override {
        do {
            x = rand() % 3;
            y = rand() % 5;
        }while(!isvalid_position(x, y));
        cout <<"RandomPlayer Placed "<<this->symbol << " at (" << x << ", " << y << ").\n";
    } 
};
