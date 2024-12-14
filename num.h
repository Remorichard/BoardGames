#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <algorithm>
using namespace std;

class NumericalTicTacToeBoard : public Board<int>{
private:
    int rows, columns;
    int** board;
    vector<int> player1Numbers = {1, 3,5, 7, 9};
    vector<int> player2Numbers = {2, 4, 6, 8};
    bool check_win();
    bool check_sum(int a, int b, int c);
public:
    NumericalTicTacToeBoard();
    ~NumericalTicTacToeBoard();
    bool update_board(int x, int y, int symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

    bool is_valid_number(int symbol, int player);
};

NumericalTicTacToeBoard :: NumericalTicTacToeBoard(){
    rows = 3;
    columns = 3;
    board = new int*[rows];
    for(int i = 0; i < rows; i++){
        board[i] = new int[columns];
        for(int j = 0; j < columns; j++){
            board[i][j] = 0; //initializing with 0 (empty cell)
        }
    }  
}
NumericalTicTacToeBoard :: ~NumericalTicTacToeBoard(){
    for(int i = 0; i < rows; i++){
        delete[] board[i];
    }
    delete[] board;
}
bool NumericalTicTacToeBoard :: update_board(int x, int y, int symbol){
    if(x < 0 || x>= rows || y < 0 || y >= columns || board[x][y] != 0){
        return false;
    }
    board[x][y] = symbol;
    return true;
}
void NumericalTicTacToeBoard :: display_board(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(board[i][j] == 0){
                cout << "__";
            }else{
                cout << " " <<board[i][j]<< " ";
            }
        }
        cout << endl;
    }
}

bool NumericalTicTacToeBoard :: check_sum(int a, int b, int c){
    return (a + b + c >= 15 && a != 0 && b != 0 && c != 0);
}

bool NumericalTicTacToeBoard :: check_win(){
    //check rows and columns
    for(int i = 0; i < rows; i++){
        if(check_sum(board[i][0], board[i][1], board[i][2])) return true;
        if(check_sum(board[0][i], board[1][i], board[2][i])) return true;
    }
    //check diagonals
    if(check_sum(board[0][0], board[1][1], board[2][2])) return true;
    if(check_sum(board[0][2], board[1][1], board[2][0])) return true;
}

bool NumericalTicTacToeBoard :: is_win(){
    return check_win();
}
bool NumericalTicTacToeBoard :: is_draw(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(board[i][j] == 0) return false; // empty cell exist
        }
    }
    return !is_win(); // no winner and no empty cells
}

bool NumericalTicTacToeBoard :: game_is_over(){
    return is_win() || is_draw();
}
bool NumericalTicTacToeBoard :: is_valid_number(int symbol, int player){
    vector<int>& numbers = (player ==  1) ? player1Numbers : player2Numbers;
    auto it = find(numbers.begin(), numbers.end(), symbol);
    if(it != numbers.end()){
        numbers.erase(it); //remove the number once used
        return true;
    }
    return false;
}

#endif //NUMERICAL_TIC_TAC_TOE_H

