#include "pyra2.h"
#include "BoardGame_Classes.h"
#include <iostream>
#include <string>

using namespace std;

class PyramidPlayer : public Player<char> {
public:
    PyramidPlayer(const string& name, char symbol) : Player(name, symbol) {}

    // Implement the pure virtual method from Player class
    void getmove(int& x, int& y) override {
        cout << getname() << " (" << getsymbol() << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};



int main() {
    Pyramid_Board<char> board;
    PyramidPlayer player1("Player 1", 'X');
    PyramidPlayer player2("Player 2", 'O');
    Player<char>* players[] = { &player1, &player2 };

    int turn = 0;
    while (!board.game_is_over()) {
        board.display_board();
        Player<char>* current_player = players[turn];
        cout << current_player->getname() << "'s turn." << endl;

        bool valid_move = false;
        while (!valid_move) {
            int row, col;
            current_player->getmove(row, col); // Get the move using the correct method
            valid_move = board.update_board(row, col, current_player->getsymbol());
            if (!valid_move) {
                cout << "Invalid move. Try again." << endl;
            }
        }

        if (board.is_win()) {
            board.display_board();
            cout << current_player->getname() << " wins!" << endl;
            return 0;
        }

        turn = (turn + 1) % 2; // Alternate turns
    }

    board.display_board();
    cout << "It's a draw!" << endl;
    return 0;
}
