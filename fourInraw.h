#ifndef _FOUR_IN_A_ROW_H
#define _FOUR_IN_A_ROW_H


#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename T>
class FourInARow : public Board<T> {
    private :
    int rows = 6;
    int columns = 7;
    bool check_line(int startRow, int startCol, int deltaRow, int deltaCol, T symbol);

public:
    FourInARow();
    ~FourInARow();
    int get_rows() const {return rows;}
    int get_column() const {return columns;} 
    T get_cell(int x, int y) const {return this->board[x][y]; }
    bool is_cell_empty(int x, int y) const { return this->board[x][y] == '.';}
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
     
};
template <typename T>
FourInARow<T>::FourInARow(){
    rows = 6;
    columns = 7;
    this->board = new T*[rows];
    for (int i = 0; i < rows; ++i){
        this->board[i] = new T[columns];
        fill(this->board[i], this->board[i] + columns, '.');
    }
}
template < typename T>
FourInARow<T>::~FourInARow(){
    for (int i = 0; i < rows; ++i){
        delete[] this->board[i];
    }
    delete [] this->board;
}
//update board for valid move
template <typename T>
bool FourInARow<T>::update_board(int x, int y, T symbol){
    if (y < 0 || y >= this->columns) return false;
    for (int i = this->rows - 1; i >= 0; --i){
        if (this->board[i][y] == '.'){
            this->board[i][y] = symbol;
            this ->n_moves++;
            return true;
        }
    }
    return false;
}
template <typename T>
void FourInARow<T>::display_board(){
    for (int i = 0; i < rows; ++i){
        for(int j = 0; j < columns; ++j){
            cout << " " << this->board[i][j] << " ";
            if (j < columns - 1) cout << "|";
        }
        cout <<"\n";
        if (i < rows - 1){
            for (int j = 0; j < columns; ++j){
                cout << "---";
                if (j < columns -1) cout << "+";
            }
             cout << "\n";
        }
    }
}
//check for a win condition
template <typename T>
bool FourInARow<T>::is_win(){
    for (int i = 0; i < this->rows; ++i){
        for (int j = 0; j < this->columns; ++j){
            if (this->board[i][j] != '.' &&
                (check_line(i, j, 0, 1, this->board[i][j]) ||
                check_line(i, j, 1, 0, this->board[i][j]) ||
                check_line(i, j, 1, 1, this->board[i][j]) ||
                check_line(i, j, 1,-1, this->board[i][j]))){ // Diagonal
                return true;
            }
        }
    }
    return false;
}
//check if the game is draw
template <typename T>
bool FourInARow<T>::is_draw(){
    return this->n_moves == this->rows * this-> columns && !is_win();
}
//check if the game is over
template <typename T>
bool FourInARow<T>::game_is_over(){
    return is_win() || is_draw();
}
//help to check lines four consecutive symbols
template <typename T>
bool FourInARow<T>::check_line(int startRow, int startCol, int deltaRow, int deltaCol, T symbol){
    int count = 0;
    for (int i = 0; i < 4; ++i){
        int row = startRow + i * deltaRow;
        int col = startCol + i * deltaCol;
        if (row >= 0 && row < rows && col >= 0 && col < columns && this->board[row][col] == symbol){
            ++count;
        } else {
            break;
        }
    }
    return count == 4;
}
template <typename T>
class HumanPlayert : public Player<T> {
public:
    HumanPlayert(string name, T symbol): Player<T>(name, symbol){}

    void getmove(int& x, int& y)override{
        auto* fourBoard = dynamic_cast<FourInARow<T>*>(this->boardPtr);
        if (fourBoard){
            while (true)
           {
                cout << this->name <<" (" << this->symbol << "), Entercolumn(0-"
                     << fourBoard->get_column() - 1 << "): ";
                cin >> y;

                // check for valid column input
                if (y >= 0 && y < fourBoard->get_column()){
                    for (x = fourBoard->get_rows() - 1; x >= 0; --x){
                        if (fourBoard->is_cell_empty(x, y)){
                            return;
                        }
                    }
                    cout << "Column "<< y << " Is full, try again.\n";
                } else {
                cout << "Ivalid column, try again.\n";
                }
            }
      
        }

    }
  
};
template <typename T>
class RandomplayerIm : public Player<T>{
public :
    RandomplayerIm(T symbol) : Player<T>("Random player", symbol){}
    void getmove(int& x, int& y) override {
        srand(time(0));
        auto* fourBoard = dynamic_cast<FourInARow<T>*>(this->boardPtr);
        if (fourBoard){
            do {
                y = rand() % fourBoard->get_column();
                for (x = fourBoard->get_rows() - 1; x >= 0; --x){
                        if (fourBoard->is_cell_empty(x, y)){
                        return;

                    }
                }
            } while(true);
        }
    }
};


#endif // _FOUR_IN_A_ROW_H