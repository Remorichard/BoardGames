#ifndef PYRAMID_TIC_TAC_TOE_H
#define PYRAMID_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

template<typename T>
class Pyramid_Board : public Board<T> {
private:
    int rows;
    int columns;
    T** board;
    bool check_win(int x, int y, T symbol);
public:
    Pyramid_Board();
    ~Pyramid_Board();

    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

template<typename T>
Pyramid_Board<T>::Pyramid_Board() {
    rows = 3; // pyramid has 3 rows
    columns = 5; // base has 5 columns
    board = new T*[rows];

    // allocating memory for each row based on pyramid structure
    for (int i = 0; i < rows; i++) {
        int current_columns = columns - (i * 2); // decreasing columns for each row
        board[i] = new T[current_columns];
        for (int j = 0; j < current_columns; j++) {
            board[i][j] = T(); // initializing with default value (empty cell)
        }
    }
}

template<typename T>
Pyramid_Board<T>::~Pyramid_Board() {
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
    }
    delete[] board;
}

template<typename T>
bool Pyramid_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= rows) return false; // outside row bounds
    int current_columns = columns - (x * 2); // columns in the current row
    if (y < 0 || y >= current_columns) return false; // outside column bounds
    if (board[x][y] != T()) return false; // cell is already occupied

    board[x][y] = symbol;
    return true;
}

template<typename T>
void Pyramid_Board<T>::display_board() {
    for (int i = 0; i < rows; i++) { // starting from the first row(smallest) and move downward
        int current_columns = columns - ((rows - 1 - i) * 2); // columns in the current row

        // Add spaces for pyramid alignment
        for (int sp = 0; sp < rows - i - 1; sp++) {
            cout << " ";
        }

        for (int j = 0; j < current_columns; j++) {
            if (board[i][j] == T()) {
                cout << "_"; // Empty cell
            } else {
                cout << board[i][j] << " "; // Print symbol
            }
        }
        cout << endl;
    }
}

template<typename T>
bool Pyramid_Board<T>::check_win(int x, int y, T symbol) {
    // calculating the current number of columns for row
    int current_columns = columns - (x * 2);

    // check horizontal win (current row)
    if (y + 2 < current_columns &&
        board[x][y] == symbol &&
        board[x][y + 1] == symbol &&
        board[x][y + 2] == symbol) {
        return true; // 3 symbols in the same row
    }

    // check vertical win (rows below)
    if (x + 2 < rows &&
        board[x][y] == symbol &&
        y < columns - ((x + 1) * 2) && board[x + 1][y] == symbol &&
        y < columns - ((x + 2) * 2) && board[x + 2][y] == symbol) {
        return true;
    }

    // check diagonal (from top-left to bottom-right)
    if (x + 2 < rows &&
        y + 2 < current_columns - ((x + 2) * 2) &&
        board[x][y] == symbol &&
        board[x + 1][y + 1] == symbol &&
        board[x + 2][y + 2] == symbol) {
        return true;
    }

    // check diagonal (from top-right to bottom-left)
    if (x + 2 < rows &&
        y - 2 >= 0 &&
        board[x][y] == symbol &&
        board[x + 1][y - 1] == symbol &&
        board[x + 2][y - 2] == symbol) {
        return true;
    }

    return false;
}

template<typename T>
bool Pyramid_Board<T>::is_win() {
    for (int i = 0; i < rows; i++) {
        int current_columns = columns - (i * 2);
        for (int j = 0; j < current_columns; j++) {
            if (board[i][j] != T() && check_win(i, j, board[i][j])) {
                return true;
            }
        }
    }
    return false;
}

template<typename T>
bool Pyramid_Board<T>::is_draw() {
    for (int i = 0; i < rows; i++) {
        int current_columns = columns - (i * 2);
        for (int j = 0; j < current_columns; j++) {
            if (board[i][j] == T()) return false; // empty space found
        }
    }
    return true; // no empty spaces left
}

template<typename T>
bool Pyramid_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

#endif // PYRAMID_TIC_TAC_TOE_H
