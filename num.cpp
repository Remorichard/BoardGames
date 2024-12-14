#include "num.h"
#include <iostream>

using namespace std;

int main() {
    NumericalTicTacToeBoard board;
    int playerTurn = 1;  // Player 1 starts
    int row, col, number;

    while (!board.game_is_over()) {
        board.display_board();

        // Determine which player is making the move
        cout << "Player " << playerTurn << "'s turn." << endl;
        cout << "Enter a number to place (Player 1 uses odd, Player 2 uses even): ";
        cin >> number;

        // Ensure the number is valid for the current player
        if (!board.is_valid_number(number, playerTurn)) {
            cout << "Invalid number! Try again." << endl;
            continue;
        }

        // Ask for the row and column
        cout << "Enter row (0-2): ";
        cin >> row;
        cout << "Enter column (0-2): ";
        cin >> col;

        // Try to make the move
        if (board.update_board(row, col, number)) {
            // Switch to the other player for the next turn
            playerTurn = (playerTurn == 1) ? 2 : 1;
        } else {
            cout << "Invalid move! Try again." << endl;
        }
    }

    board.display_board();

    // Check the game result
    if (board.is_win()) {
        cout << "Player " << (playerTurn == 1 ? 2 : 1) << " wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }

    return 0;
}
