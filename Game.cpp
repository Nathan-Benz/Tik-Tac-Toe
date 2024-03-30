#include "Game.hpp"

Game::Game() : Board(), complete_{false}, total_turns{0} {}

void Game::gameManager(const bool& play_ai) {
    int winner = 0;
    playerSelect();

    resetGame();
    while (!isComplete() && winner == 0) {
        winner = playerTurn();

        if (winner != 0 || isComplete()) break;

        if (!play_ai) winner = opponentTurn();
        else winner = aiTurn();
    }

    std::system("cls");

    drawBoard();

    if (winner == 1) std::cout<<"Player 1 wins!";
    else if (winner == -1) {
        if (play_ai) std::cout<<"AI wins!";
        else std::cout<<"Player 2 wins!";
    }
    else std::cout<<"Draw!";

    char decision;
    do {
        std::cout<<"\nWant to play again? [Y] | [N]:";
        std::cin>>decision;     
    }
    while (tolower(decision) != 'y' && tolower(decision) != 'n');

    if (tolower(decision) == 'n') return;

    do {
        std::cout<<"\nWant to play the AI? [Y] | [N]:";
        std::cin>>decision;     
    }
    while (tolower(decision) != 'y' && tolower(decision) != 'n');

    if (tolower(decision) == 'y') gameManager(1);
    else gameManager(0);
}

void Game::playerSelect() {
    char symbol = ' ';

    do {
        std::system("cls");
        std::cout<<"Select your symbol | 'X' or 'O' :";
        std::cin>>symbol;
    }
    while (tolower(symbol) != 'x' && tolower(symbol) != 'o');

    if (symbol == 'x') {player1 = 'x'; player2 = 'o';}
    else {player1 = 'o'; player2 = 'x';}

    std::system("cls");
    std::cout<<"Player 1: "<<player1<<"\nPlayer 2: "<<player2<<"\n";
}

int Game::playerTurn() {
    std::system("cls");
    std::cout<<"Player 1's turn. ("<<player1<<")\n";
    return Turn(player1, 1);
}

int Game::opponentTurn() {
    std::system("cls");
    std::cout<<"Player 2's turn.("<<player2<<")\n";
    return Turn(player2, 0);
}

int Game::Turn(const char& player, const bool& main_player) {
    int row, col;

    drawBoard();

    do {
        std::system("cls");
        if (main_player) std::cout<<"Player 1's turn ("<<player1<<")\n";
        else std::cout<<"Player 2's turn ("<<player2<<")\n";
        drawBoard();

        std::cout<<"Enter a ROW then COLUMN in the terminal [0 - 2]\n";
        std::cin>>row>>col;
    }
    while (!inRange(row,col));


    while (!updateCell(player,row,col)) {
        std::system("cls");
        if (main_player) std::cout<<"Player 1's turn ("<<player1<<")\n";
        else std::cout<<"Player 2's turn ("<<player2<<")\n";
        drawBoard();

        std::cout<<"Invalid location! Enter new numbers.\n";
        std::cin>>row>>col;
    }

    total_turns++;

    if (main_player) {
        if (checkBoard(row,col)) return 1;
        else return 0;
    }
    else {
        if (checkBoard(row,col)) return -1;
        else return 0;
    }
}

int Game::aiTurn() {
    int best_score = INT_MIN;
    int best_row = -1, best_col = -1;

    int curr_board[3][3];
    for (int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j) curr_board[i][j] = getCell(i,j);
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (isCellEmpty(curr_board,i,j)) {
                updateCell(curr_board, player2, i, j);
                int score = minimax(curr_board, INT_MAX, false, i, j);

                if (score > best_score) {
                    best_score = score;
                    best_row = i;
                    best_col = j;
                }

                updateCell(curr_board, ' ', i, j);
            }
        }
    }

    updateCell(player2,best_row,best_col);
    if (checkBoard(best_row,best_col)) return -1;
    else return 0;
}

int Game::minimax(int (&curr_board)[3][3], int depth, bool maximixing, int row, int col) {
    if (checkBoard(curr_board, row,col) || depth == 0) {
        //if ()
        if (getCell(curr_board,row,col) == player1) return -1;
        else if (getCell(curr_board,row,col) == player2) return 1;
        else return 0;
    }


}

bool Game::checkRow(const int& row) const {return (getCell(row,0) == getCell(row,1)) && (getCell(row,0) == getCell(row,2));}

bool Game::checkCol(const int& col) const {return (getCell(0,col) == getCell(1,col)) && (getCell(0,col) == getCell(2,col));}

bool Game::checkDiagnoal() const {return (getCell(1,1) != ' ') && ((getCell(1,1) == getCell(0,0) && (getCell(1,1) == getCell(2,2))) || (getCell(1,1) == getCell(2,0) && (getCell(1,1) == getCell(0,2))));}

bool Game::checkBoard(const int& row, const int& col) const {return checkRow(row) || checkCol(col) || checkDiagnoal();}

bool Game::isComplete() const {return complete_ || (total_turns >= 9);}

void Game::resetGame() {
    complete_ = false;
    total_turns = 0;
    resetBoard();
}

//The folowing functions check the state of a clone board and not the original
bool Game::checkRow(int (&curr_board)[3][3], const int& row) const {return (getCell(curr_board,row,0) == getCell(curr_board,row,1)) && (getCell(curr_board,row,0) == getCell(curr_board,row,2));}

bool Game::checkCol(int (&curr_board)[3][3], const int& col) const {return (getCell(curr_board,0,col) == getCell(curr_board,1,col)) && (getCell(curr_board,0,col) == getCell(curr_board,2,col));}

bool Game::checkDiagnoal(int (&curr_board)[3][3]) const {return (getCell(curr_board,1,1) != ' ') && ((getCell(curr_board,1,1) == getCell(curr_board,0,0) && (getCell(curr_board,1,1) == getCell(curr_board,2,2))) || (getCell(curr_board,1,1) == getCell(curr_board,2,0) && (getCell(curr_board,1,1) == getCell(curr_board,0,2))));}

bool Game::checkBoard(int (&curr_board)[3][3], const int& row, const int& col) const {return checkRow(curr_board,row) || checkCol(curr_board,col) || checkDiagnoal(curr_board);}