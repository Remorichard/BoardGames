//DESCRIPTION: GAME APP FOR ALL GAMES
//AUTHOR1:RICHARD REMO EMMANUEL ID: 20220862
//AUTHOR2:SUNDAY PUL NYOK ID: 20220891
//DESIGN AUTHOR: BOTH INDIVIDUAL
//DATE:16/12/2024
//COURSE: CS213 OOP


#include "Pyramid.h"
#include "5by5.h"
#include "wordTic-tac.h"
#include "Numerical.h"
#include "fourinraw.h"
#include "misereTicTac.h"
#include "BoardGame_Classes.h"
#include <iostream>
#include <string>

using namespace std;
//DONE BY AUTHOR 1
class Pyramid_player : public Player<char>{
public:
    Pyramid_player(const string& name, char symbol) : Player(name, symbol) {}
    void getmove(int& x, int& y){
        cout<<getname() <<"(" << getsymbol() << "), Enter your move (row and column): ";
        cin>>x >>y;
    }
};

// FUNCTIION TO PLAY THE PYRAMID GAME
void play_pyramidGame() {
    PyramidBoard<char> board;

    Human_Player<char> player_1 ("Player 1", 'X');
    Random_PlayerIm<char> player_2('O');

    Player<char>* players[2] = { &player_1, &player_2};
    player_1.setBoard(&board);
    player_2.setBoard(&board);

    GameManager<char> game_manager(&board, players);
    game_manager.run();


}

//FUNCTION TO PLAY FIVE BY FIVE GAME
void play_fiveTicTac(){
    fiveTictac_Board<char> board;
    HumanPlayer<char> player1('X');
    Random_Player<char>player2('O');
    Player<char>* players[2] = {&player1, &player2};
    player1.setBoard(&board);
    player2.setBoard(&board);

    int currentPlayer_indx = 0;
    int x, y;
    cout << "Welcome to 5x5 Tic-Tic-Toe with middle blocked!\n";
    board.display_board();
    while(!board.game_is_over()){
        Player<char>* current_player = players[currentPlayer_indx];
        char symbol = current_player->getsymbol();
        if(currentPlayer_indx == 0){
            cout << "Human (" <<symbol << ")'s turn.\n";
        }else {
            cout << "Computer (" <<symbol << ")'s turn.\n";
        }
        //get moves
        current_player->getmove(x, y);
        cout<<current_player->getname()<< "placed at (" << x << ", " << y << ")\n";
        
        //switch players turn
        currentPlayer_indx = 1 - currentPlayer_indx;
        board.display_board();
        
    

        cout<<players[currentPlayer_indx]->getname()<< "("<<players[currentPlayer_indx]->getsymbol() << ") 's trun.\n";
        players[currentPlayer_indx]->getmove(x, y);
        cout<<players[currentPlayer_indx]->getname()<< "Placed at (" << x <<", " << y <<")\n";

        currentPlayer_indx = 1 - currentPlayer_indx;
        board.display_board();
    }
    cout<<"Final Scores:\n";
    cout<<"Human 1(X): "<<board.count_three_in_row('X') <<endl;
    cout<<"Computer 2(O): "<<board.count_three_in_row('O') <<endl;

    if(board.count_three_in_row('X') > board.count_three_in_row('O')){
        cout << "Human 1 (X) wins! \n";
    }else if (board.count_three_in_row('X') < board.count_three_in_row('O')){
        cout << "Computer 2 (O) wins! \n";
    }else{
        cout << "It's a draw! \n";
    }
}

//FUNCTION TO PLAY NUMERIC TIC TAC GAME
void play_numericTictacToe(){
    NumericalTicTacToeBoard board;
    int playerTurn = 1;
    int row, column, number;
    while(!board.game_is_over()){
        board.display_board();

        //determine which player is making the move
        cout << "Player "<<playerTurn <<"'s turn."<<endl;
        cout <<"Enter a number to placed (player 1 uses odd, player 2 uses even): ";
        cin>>number;

        //ensuring the number is valid for current player
        if(!board.is_valid_number(number, playerTurn)){
            cout<<"Invalid number! Try again. "<<endl;
            continue;
        }

        //ask the player to enter row and colum
        cout<<"Enter row(0-2): ";
        cin>>row;
        cout<<"Enter column (0-2): ";
        cin>>column;

        //making the move
        if(board.update_board(row, column, number)){
            //Switch turn to other player
            playerTurn = (playerTurn == 1 ) ? 2 : 1;
        }else {
            cout << "Invlaid move! try again." <<endl;
        }
    }

    board.display_board();
    //check gamae results
    if(board.is_win()){
        cout << "Player "<< (playerTurn == 1 ? 2 : 1) <<"WINS!"<<endl;
    }else {
        cout << "It's a draw!" <<endl;
    }
}

//FUNCTION TO PLAY WORD TIC TAC GAME
void play_wordTicToe(){
    srand(static_cast<unsigned> (time(0)));

    WordTicTacBoard board("dic.txt");

    HumanPlayerImpl human("player 1", ' ');
    RandomPlayerImpl random(' ');

    Player<char>* players[2] = {&human, &random};
    GameManager<char> game_manager(&board, players);

    game_manager.run();
}

//FUNCTION TO PLAY MISERE TIC TAC GAME
void play_misereTicTaC(){
    MisereTicTacToeBoard<char> Board;
    MisereTicTacToePlayer<char>player1("player1", 'X');
    MisereTicTacToeRandomPlayer<char>player2('O');

    char current_player = 'X';
    int x, y;
    while (!Board.game_is_over()){
        Board.display_board();
        cout << "currect player: "<< current_player << endl;
        if (current_player == 'X'){
            player1.getmove(x, y);
        }
        else {
            player2.getmove(x, y);
        }
        if (Board.update_board(x, y, current_player)){
            if (Board.is_win()){
                cout << "player "<< (current_player == 'X' ? 'O' : 'X') << "win"<< endl;
                break;
            }
            else if(Board.is_draw()){
                cout << "It's a draw!"<< endl;
                break;
            }
            current_player = (current_player == 'X') ? 'O' : 'X';
        }

    }
}

//FUNCTION TO PLAY FOUR IN RAW TIC TAC GAME
void play_fourinraw(){
    FourInARow<char> board;
    HumanPlayert<char>Player1("player1", 'X');
    RandomplayerIm<char> player2 ('O');

    Player<char>* players[2] = {&Player1, &player2};
    Player1.setBoard(&board);
    player2.setBoard(&board);

    int currentplayerIndex  = 0;
    int x, y;
    cout << " Welcome the four in a Row!\n";
    board.display_board();
    while (!board.game_is_over()){
        cout << players[currentplayerIndex]->getname()<< " (" << players[currentplayerIndex]->getsymbol() << ")'s turn.\n";
        do {
            players[currentplayerIndex]->getmove(x, y);
        } while (!board.update_board(x, y , players[currentplayerIndex]->getsymbol()));
        board.display_board();
        currentplayerIndex = 1 - currentplayerIndex;
    }
    if (board.is_win()){
        cout << players[1- currentplayerIndex] ->getname()<<"win!\n";

    } else {
        cout << "it's a draw\n";
    }
}


int main(){
    while(true){
        //DISPLAY MENU
        cout<<"\nChoose a game to play:\n";
        cout<<" 1.Pyramid Game\n";
        cout<<" 2.5x5 Tic Tac Toe\n";
        cout<<" 3.Numerical Tic Tac Toe\n";
        cout<<" 4.Word Tic Tac Toe\n";
        cout<<" 5.Four in a Row Tic Tac Toe\n";
        cout<<" 6.Misere Tic Tac Toe\n";
        cout<<" 7.Exit\n";
        cout<<" Enter your choice: ";
        int choice;
        cin>>choice;//Allow user to enter the game he/she wants to play

        if (choice == 1){
            play_pyramidGame();
        }else if(choice == 2){
            play_fiveTicTac();
        }else if(choice == 3){
            play_numericTictacToe();
        }else if(choice == 4){
            play_wordTicToe();
        }else if(choice == 5){
            play_fourinraw();
        }else if(choice == 6){
            play_misereTicTaC();
        }else if(choice == 7){
            cout <<"Exiting. Thank you for playing!!\n";
            break;
        }else {
            cout<<"Invalid choice. Please try again.\n";
        }

        cout<<"Do you want to play again? (y/n): ";
        char playagain;
        cin >>playagain;
        if(tolower(playagain) != 'y'){
            cout<<"Exiting. Thank you for playing!\n";
            break;
        }
    }

    return 0;
}