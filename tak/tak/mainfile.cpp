#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <fstream>
using namespace std;


const int SIZE = 3;
const int ROWS = 6;
const int COLS = 7;

void initializefourinrowBoard(vector<vector<char>>& Board){
   Board.assign(ROWS, vector<char>(COLS, ' '));
}
//Function to Initialize the board
void displayfourinrowboard(const vector<vector<char>>& Board){
  cout << "   ";
  for (int col = 0; col < COLS; ++col){
    cout << col << "   ";
  }
  cout << endl;
  //Display the board with row indices
  for (int row = 0; row < ROWS; ++row){
    cout << row << " | ";
    for (char cell : Board[row]){
      cout <<(cell == ' ' ? ' ' : cell ) << " | ";
    } 
    cout << endl;
  }
}
//function to drop a piece into a column starting from the bottom
bool dropfourinrowPiece(vector<vector<char>>& Board, int col, char piece){
  for (int row = ROWS - 1; row >= 0; --row){
    if (Board[row][col] == ' '){
      Board[row][col] = piece;
      return true;
    }
  }
  return false;
}

//function to check if the a player has won (horizontal, vertical, diagonal)
bool checkfourinrowWinner(const vector<vector<char>>& Board, char piece){
  for (int row = 0; row < ROWS; ++row){
    for (int col = 0; col < COLS - 3; ++col){
      if (Board[row][col] == piece && Board[row][col + 1] == piece &&
         Board[row][col + 2] == piece && Board[row][col + 3] == piece){
         return true;
      }
    }
  }

  //check vertical
  for (int col = 0; col < COLS; ++col){
    for (int row = 0; row < ROWS - 3; ++row){
      if (Board[row][col] == piece && Board[row + 1][col] == piece &&
      Board[row + 2][col] == piece && Board[row + 3][col] == piece){
        return true;
      } 
    }
  }

  // Check diagonal(\)
  for (int row = 0; row < ROWS - 3; ++row){
    for (int col = 0; col < COLS - 3; ++col){
      if (Board[row][col] == piece && Board[row + 1][col +1] == piece && 
      Board[row + 2][col + 2] == piece && Board[row + 3][col + 3] == piece){
        return true;
      }
    }
  }
    // Check diagonal(/)
  for (int row = 3; row < ROWS; ++row){
    for (int col = 0; col < COLS - 3; ++col){
      if (Board[row][col] == piece && Board[row - 1][col +1] == piece && 
      Board[row - 2][col + 2] == piece && Board[row - 3][col + 3] == piece){
        return true;
      }
    }
  }
  return false;

}
//Function for the computer to choose a random column
int computerfourinrowMove(const vector<vector<char>>& Board){
  while (true){
    int col = rand() % COLS;
    if (Board[0][col] == ' '){
      return col;
    }
  }
}
// work toe-tac-toe
char board[SIZE][SIZE];
unordered_set<string> validwords;
int computerMoveCount = 0;

//Function to initialize the game board
void initializeBoard(){
  for (int i = 0; i < SIZE; ++i)
   for (int j = 0; j < SIZE; ++j)
    board[i][j] = ' ';
}
//Function to load valid words feom the a file 
bool loadValidWords(const string &filename){
  ifstream file(filename);
  if (!file){
    cout << "Error: Unable to open the file "<< filename <<"\n";
    return false;
  }
  string word;
  while (file >> word){
    validwords.insert(word);
  }
  return true;
}
// Function to display the Game board 
void displayBoard(){
   cout << " ";
   for (int col = 0; col < SIZE; ++col){
       cout << col << " ";
    }
   cout << endl;
  
   for (int row = 0; row < SIZE; ++row){
       cout << row << "|";
       for (int col = 0; col < SIZE; ++col){
           cout<< (board[row][col] == ' ' ? ' ' : board[row][col])<< "|";
        }
        cout << endl;
    }
    cout << endl;
}
 
//function to check if a word is valid 
bool isValidWord(const string &word){
     return validwords.find(word) != validwords.end();
}
//Function to check the winner and return the winning word.
string checkWinner(){
   //check the row and col
   for (int i = 0; i < SIZE; ++i){
       string row, col;
       for (int j = 0; j < SIZE; ++j){
          row += board[i][j];
          col += board[j][i];
       }
       if (isValidWord(row)){
         return row;
        }
       if (isValidWord(col)){
         return col;
     }
    }
     //check the diagonals
   string diag1, diag2;
   for (int i = 0; i < SIZE; ++i){
        diag1 += board[i][i];
       diag2 += board[i][SIZE- i - 1];
    }
    if (isValidWord(diag1)){
       return diag1;
    }
    if (isValidWord(diag2)){
       return diag2;
    }
    return "";
}
// function tfor the computer to Make a random move
void computerMove(){
   while(true){
       int row = rand() % SIZE;
       int col = rand() % SIZE;
       if (board[row][col] == ' '){
           char computerLetter = 'A' + (rand() % 26);
           board[row][col] = computerLetter;
           computerMoveCount++;
           cout << "Computer place: "<< computerLetter << " at (" << row << ", " << col << ")\n";
           break; 
     
       }
   }
}
//Misere tic-tac-toe
void initializeBoard(vector<vector<char>>& Board){
  Board.assign(SIZE, vector<char>(SIZE, ' '));
}
//function to display the game board
void displayBoard(const vector<vector<char>>& Board){
  for (const auto& row : Board){
    cout << "|";
    for (char cell : row){
      cout << (cell == ' ' ? ' ' : cell) << "|";
    }
    cout << endl;
  }
  cout << endl;
}
//fundtion to check if the current player lost
bool checkLosingCondition(const vector<vector<char>>& Board, char piece){
  for (int row = 0; row < SIZE; ++row){
    if (Board[row][0] == piece && Board[row][1] == piece && Board[row][2] == piece){
      return true;

    }
  }
  for (int col = 0; col < SIZE; ++col){
    if (Board[0][col] == piece && Board[1][col] == piece && Board[2][col] == piece){
      return true;
    }
  }
  if (Board[0][0] == piece && Board[1][1] == piece && Board[2][2] == piece){
    return true;
  }
  if (Board[0][2] == piece && Board[1][1] == piece && Board[2][0] == piece){
    return true;
  }
  return false;
}
void computerMove(vector<vector<char>>& Board, char piece){
  for (int row = 0; row < SIZE; ++row){
    for (int col = 0; col < SIZE; ++col){
      if (Board[row][col] == ' '){
        Board[row][col] = piece;
        if (checkLosingCondition(Board, piece)){
          Board[row][col] = ' ';
        } else {
          return;
        }
      }
    }
  }
  //if o sage move, make a random move
  srand(time(0));
  while (true)
  {
    int row = rand() % SIZE;
    int col = rand() % SIZE;
    if (Board[row][col] == ' '){
      Board[row][col] = piece;
      return;
    }
  }
  
}

//main Menu
void displayMenu(){
    cout <<"\n Select a game to play: \n";
    cout << "1. four in row tie-tac-toe\n";
    cout << "2. Words tie-tae-toe\n";
    cout << "3. Misere tie-tac-toe\n";
    cout << "0. EXIST\n";
}
int main() {
    srand(time(0));
    int choice;
    do {
        displayMenu();
        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;
        if (choice == 1){
          vector<vector<char>> Board;
          initializefourinrowBoard(Board);
            char players[2] = {'X', '0'};
            int turn = 0;
            while (true){
                cout <<"Welcome to four-in-row tic-toe-toe Game!" << endl;
                displayfourinrowboard(Board);
               int col;
               if (turn == 0){
                  cout << "Player 1(X), Choose a column (0-6): ";
                  cin >> col;
                  if (col < 0 || col >= COLS){
                     cout <<"Invalid column, player try again.\n";
                    continue;
                  }
              } else {
              col = computerfourinrowMove(Board);
              cout <<"Computer(0), choose column: "<< col << endl;
            }
            if (!dropfourinrowPiece(Board, col, players[turn])){
               if (turn == 0){
                  cout <<"Column is full, please try again.\n";
                }
              continue;
           }
           if (checkfourinrowWinner(Board, players[turn])){
              displayfourinrowboard(Board);
              if (turn == 0){
                 cout <<"Player 1, wins\n";
              } else {
                 cout << "Computer wins\n";
              }
              break;
            }
           bool isTie = true;
           for (int col = 0; col < COLS; ++col){
               if (Board[0][col] == ' '){
                 isTie = false;
                 break;
                }
            }
            if (isTie){
               displayfourinrowboard(Board);
               cout << "THE GAME IS A TIE-TOE -TOE!\n";
               break;
           }
             turn = 1 - turn;
            }

        } else if (choice == 2){
          srand(static_cast<unsigned int>(time(0)));
            if (!loadValidWords("dic.txt")){
                 return 1;
           }
          initializeBoard();
          int moves = 0;
           cout << "Welcome to Word Tic-tac-toe! " << endl;
          while (true){
               displayBoard();
    
               //Human 1's turn
               char letter;
               int row, col;
               cout << "Human, Enter your move: ";
               cin >> letter >> row >> col;
               if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ' || !isalpha(letter)){
                  cout << "invalid move, try again.\n";
                  continue;
               }
              letter = toupper(letter);
              board[row][col] = letter;
              moves++;
              string winningword = checkWinner();
              if (!winningword.empty()){
                  displayBoard();
                  cout << "Human wins by forming the valid words: " << winningword << "!" << endl;
                  break;
               }
               if (moves == SIZE * SIZE){
                  displayBoard();
                  cout <<" It is draw, no vaild words former. " << endl;
                 break;
               }
    
               //compueter is turn
              computerMove();
              winningword = checkWinner();
             if (!winningword.empty()){
                 displayBoard();
                 cout << "Computer wins by forming valid words: " << winningword << "!" << endl;
                 break;
               }
              if (moves == SIZE * SIZE){
                   displayBoard();
                   cout << "it is draw, ni valid formed. " << endl;
                   break;
              }

           }
           
        } else if (choice == 3){
                vector<vector<char>> Board;
                initializeBoard(Board);
                char players[2] = {'X', 'O'};
                int turn = 0;
                int Moves = 0;
                cout <<"Welcome to the Misere TIC-TAC-TOE game for avoiding getting three marks!"<< endl;
                while (true){
                   displayBoard(Board);
                   if (turn == 0){
                      int row, col;
                      cout <<"Human player1 (X), Enter you move: ";
                      cin >> row >> col;
                     if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || Board[row][col] != ' '){
                         cout << "Invalid move, try again.\n";
                           continue;
                       }
                      Board[row][col] = players[turn];
                   } else {
                          cout << "Player 2 (o), Computer is marking its move.."<< endl;
                          computerMove(Board, players[turn]);
                    }
                    ++Moves;

                 if (checkLosingCondition(Board, players[turn])){
                      displayBoard(Board);
                      cout << "player "<<(turn + 1) << "(" << players[turn] << ") loses by forming three!" << endl;
                      break;
                   }
                  if (Moves == SIZE * SIZE){
                      displayBoard(Board);
                      cout << "Its a draw, both players avoided forming three!"<< endl;
                      break;
                   }
                 turn = 1 - turn;
                }
        

        

        }

    } while ( choice != 0);
    cout << "THANKS FOR PLAYING\n";
    return 0;
}
