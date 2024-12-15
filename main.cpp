#include "Pyramid.h"
#include "5by5.h"
#include "Numerical.h"
#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>
#include <string>

using namespace std;

// Pyramid Player Class
class Pyramid_player : public Player<char> {
public:
    Pyramid_player(const string& name, char symbol) : Player(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << getname() << " (" << getsymbol() << "), Enter your move (row and column): ";
        cin >> x >> y;
    }
};

// Pyramid Game Function
void play_pyramidGame() {
    Pyramid_Board<char> board;
    Pyramid_player player_1("Player 1", 'X');
    Pyramid_player player_2("Player 2", 'O');
    Player<char>* players[] = {&player_1, &player_2};

    int turn = 0;
    cout << "Starting Pyramid Game!\n";
    bool valid_move = false;

    while (!board.game_is_over()) {
        board.display_board();
        Player<char>* current_player = players[turn];
        cout << current_player->getname() << "'s turn." << endl;

        
        while (!valid_move) {
            int row, col;
            current_player->getmove(row, col);
            valid_move = board.update_board(row, col, current_player->getsymbol());
            if (!valid_move) {
                cout << "Invalid move. Try again." << endl;
            }
        }

        if (board.is_win()) {
            board.display_board();
            cout << current_player->getname() << " wins!" << endl;
            return;
        }

        turn = (turn + 1) % 2;
    }

    board.display_board();
    cout << "It's a draw!" << endl;
}

// 5x5 Tic-Tac-Toe Function
void play_fiveTicTac() {
    fiveTictac_Board<char> board;
    HumanPlayer<char> player1('X');
    Random_Player<char> player2('O');
    Player<char>* players[2] = {&player1, &player2};
    player1.setBoard(&board);
    player2.setBoard(&board);

    int currentPlayer_indx = 0;
    cout << "Welcome to 5x5 Tic-Tic-Toe with middle blocked!\n";

    while (!board.game_is_over()) {
        board.display_board();
        Player<char>* current_player = players[currentPlayer_indx];
        cout << current_player->getname() << " (" << current_player->getsymbol() << ")'s turn." << endl;

        int x, y;
        current_player->getmove(x, y);
        cout << current_player->getname() << " placed at (" << x << ", " << y << ")\n";

        currentPlayer_indx = 1 - currentPlayer_indx;
    }

    board.display_board();
    cout << "Final Scores:\n";
    cout << "Player 1 (X): " << board.count_three_in_row('X') << endl;
    cout << "Player 2 (O): " << board.count_three_in_row('O') << endl;

    if (board.count_three_in_row('X') > board.count_three_in_row('O')) {
        cout << "Player 1 (X) wins!" << endl;
    } else if (board.count_three_in_row('X') < board.count_three_in_row('O')) {
        cout << "Player 2 (O) wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }
}

// Numerical Tic-Tac-Toe Function
void play_numericTictacToe() {
    NumericalTicTacToeBoard board;
    int playerTurn = 1;
    int row, column, number;

    while (!board.game_is_over()) {
        board.display_board();

        // Determine current player
        cout << "Player " << playerTurn << "'s turn." << endl;
        cout << "Enter a number to place (Player 1 uses odd, Player 2 uses even): ";
        cin >> number;

        // Validate number
        if (!board.is_valid_number(number, playerTurn)) {
            cout << "Invalid number! Try again." << endl;
            continue;
        }

        // Get row and column
        cout << "Enter row (0-2): ";
        cin >> row;
        cout << "Enter column (0-2): ";
        cin >> column;

        // Make the move
        if (board.update_board(row, column, number)) {
            playerTurn = (playerTurn == 1) ? 2 : 1;
        } else {
            cout << "Invalid move! Try again." << endl;
        }
    }

    board.display_board();

    // Check game results
    if (board.is_win()) {
        cout << "Player " << ((playerTurn == 1) ? 2 : 1) << " wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }
}

// Main Function
int main() {
    while (true) {
        cout << "\nChoose a game to play:\n";
        cout << "1. Pyramid Game\n";
        cout << "2. 5x5 Tic Tac Toe\n";
        cout << "3. Numerical Tic Tac Toe\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                play_pyramidGame();
                break;
            case 2:
                play_fiveTicTac();
                break;
            case 3:
                play_numericTictacToe();
                break;
            case 4:
                cout << "Exiting. Thank you for playing!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << "Do you want to play again? (y/n): ";
        char playAgain;
        cin >> playAgain;
        if (tolower(playAgain) != 'y') {
            cout << "Exiting. Thank you for playing!\n";
            break;
        }
    }

    return 0;
}
