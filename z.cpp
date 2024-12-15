#include "Pyramid.h"
#include "5by5.h"
#include "Numerical.h"
#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime> 
#include <string>

using namespace std;
class Pyramid_player : public Player<char>{
public:
    Pyramid_player(const string& name, char symbol) : Player(name, symbol) {}
    void getmove(int& x, int& y){
        cout<<getname() <<"(" << getsymbol() << "), Enter your move (row and column): ";
        cin>>x >>y;
    }
};



void play_pyramidGame(){
    Pyramid_Board<char> board;
    Pyramid_player player_1("Player 1", 'X');
    Pyramid_player player_2("Player 2", 'O');
    Player<char>* players[] = {&player_1, &player_2};

    int turn = 0;
    cout << "starting Pyramid Game!\n";
    bool valid_move = false;
    while(!board.game_is_over()){
        board.display_board();
        Player<char>* current_player = players[turn];
        cout<< current_player->getname() <<"'s turn."<<endl;
        while(!valid_move){
            int row, col;
            current_player ->getmove(row, col);
            valid_move = board.update_board(row, col, current_player->getsymbol());
            if(!valid_move){
                cout<<"Invalid move. Try again."<< endl;
            }
        }
        if(board.is_win()){
            board.display_board();
            cout <<current_player->getname() <<"wins!"<<endl;
            return;
        }
        turn = (turn + 1) % 2;

    }
    board.display_board();
    cout<<" Its a draw! "<<endl;
}   

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
        cout<<"Enter row(0-2)";
        cin>>row;
        cout<<"Enter column (0-2)";
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


int main(){
    while(true){
        cout<<"\nChoose a game to play:\n";
        cout<<" 1.Pyramid Game\n";
        cout<<" 2.5x5 Tic Tac Toe\n";
        cout<<" 3.Numerical Tic Tac Toe\n";
        cout<<" 4.Exit\n";
        cout<<" Enter your choice: ";
        int choice;
        cin>>choice;

        if (choice == 1){
            play_pyramidGame();
        }else if(choice == 2){
            play_fiveTicTac();
        }else if(choice == 3){
            play_numericTictacToe();
        }else if(choice == 4){
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