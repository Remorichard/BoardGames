#include "BoardGame_Classes.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

// word Tic-Tac-Toe Board
class WordTicTacBoard : public Board<char> {
private: 
    unordered_set<string> dictionary;
public:
    WordTicTacBoard(const string& dict_file) {
        rows = columns = 3;
        board = new char*[rows];
        for(int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            fill(board[i], board[i] + columns, ' ');
        }
        load_dictionary(dict_file);
    }

    ~WordTicTacBoard() {
        for(int i = 0; i < rows; ++i)
            delete[] board[i];
        delete[] board;
    }

    void load_dictionary(const std::string& dict_file) {
        std::ifstream file(dict_file);
        if(!file) {
            std::cerr << "Failed to load dictionary file." << std::endl;
            exit(1);
        }
        std::string word;
        while(file >> word) {
            if(word.length() == 3)
                dictionary.insert(word);
        }
    }

    bool is_valid_word(const std::string& word) {
        return dictionary.find(word) != dictionary.end();
    }

    bool update_board(int x, int y, char symbol) override {
        if(x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
        board[x][y] = symbol;
        n_moves++;
        return true;
        }
        return false;
    }

    void display_board() override {
        cout << " 1 2 3" << std::endl;
        for(int i = 0; i < rows; ++i) {
        cout << i + 1 << " ";
        for(int j = 0; j < columns; ++j) {
            cout << board[i][j] << (j < columns  - 1 ? "|" : "");
        }
        cout << std::endl;
        if(i < rows - 1) cout << " -----" << endl;
        }
    }

    bool is_win() override {
        for(int i = 0; i < rows; ++i) {
            if(is_valid_word(string{board[i][0], board[i][1], board[i][2]})) return true;
        }
        for(int j = 0; j < columns; ++j) {
            if(is_valid_word(string{board[0][j], board[1][j], board[2][j]})) return true;
        }
        if(is_valid_word(string{board[0][0], board[1][1], board[2][2]})) return true;
        if(is_valid_word(string{board[0][2], board[1][1], board[2][0]})) return true;
        return false;
    }
    bool is_draw()override{
        return n_moves == rows * columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

// Human player
class HumanPlayerImpl : public Player<char> {
public:
    HumanPlayerImpl(const std::string& name, char symbol) : Player(name, symbol) {}

    void getmove(int& x, int& y) override {
        std::cout << name << ", enter your move (row, column, letter): ";
        char letter;
        while(!(std::cin >> x >> y >> letter) || x < 1 || x > 3 || y < 1 || y > 3 || !std::isalpha(letter)) {
            cout << "Invalid input. Enter row (1 - 3), column (1-3), column (1-3), and a letter: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        x--;
        y--;
        this->symbol = letter;
    }
};

// Random Player
class RandomPlayerImpl : public RandomPlayer<char> {
public: 
    RandomPlayerImpl(char symbol) : RandomPlayer(symbol) {}

    void getmove(int& x, int& y) override
    {
        x = rand() % 3;
        y = rand() % 3;
        this->symbol = 'A' + rand() % 26;
        cout << "Random Player plays (" << x + 1 << ", " << y + 1 << ", " << this->symbol << ")" <<endl;
    } 
};

