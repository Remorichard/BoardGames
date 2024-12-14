#include "5by5.h"

int main() {
    fiveTictac_Board<char> board;

    // One player is human, the other is random.
    HumanPlayer<char> player1('X');
    Random_Player<char> player2('O');

    Player<char>* players[2] = { &player1, &player2 };
    player1.setBoard(&board);
    player2.setBoard(&board);

    GameManager<char> gameManager(&board, players);

    int currentPlayerIndex = 0;
    int x, y;

    cout << "Welcome to 5x5 Tic-Tac-Toe with middle blocked!\n";
    board.display_board();

    while (!board.game_is_over()) {
        cout << players[currentPlayerIndex]->getname() << " (" << players[currentPlayerIndex]->getsymbol() << ")'s turn.\n";

        // Get a valid move
        players[currentPlayerIndex]->getmove(x, y);

        // Display the move made
        cout << players[currentPlayerIndex]->getname() << " placed at (" << x << ", " << y << ")\n";

        // Switch turns
        currentPlayerIndex = 1 - currentPlayerIndex;
        board.display_board();
    }

    cout << "Final Scores:\n";
    cout << "Player 1 (X): " << board.count_three_in_row('X') << endl;
    cout << "Player 2 (O): " << board.count_three_in_row('O') << endl;

    if (board.count_three_in_row('X') > board.count_three_in_row('O')) {
        cout << "Player 1 (X) wins!\n";
    } else if (board.count_three_in_row('X') < board.count_three_in_row('O')) {
        cout << "Player 2 (O) wins!\n";
    } else {
        cout << "It's a draw!\n";
    }

    return 0;
}
