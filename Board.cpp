#include "Board.hpp"

Board::Board() {}

void Board::initializeBoard(char (&board)[3][3]) {for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) board[i][j] = ' ';}\

void Board::resetBoard(char (&board)[3][3]) {initializeBoard(board);}

bool Board::inRange(const int& row, const int& col) {
    if (row < 0 || row > 2 || col < 0 || col > 2) return false;
    return true; 
}

bool Board::isCellEmpty(const char (&board)[3][3], const int& row, const int& col) {
    if (!inRange(row,col)) return false;

    return board[row][col] == ' ';
}

bool Board::updateCell(const char& symbol, char (&board)[3][3], const int& row, const int& col) {
    if (!inRange(row,col)) return false;
    if (!isCellEmpty(board,row,col)) return false;

    board[row][col] = symbol;
    return true;
}

char Board::getCell(const char (&board)[3][3], const int& row, const int& col) {
    if (!inRange(row,col)) return ' ';

    return board[row][col];
}

int Board::completedRow(const char& symbol, const char (&board)[3][3], const int& row, const int& col) {
    if ((getCell(board,row,0) == getCell(board,row,1) && getCell(board,row,0) == getCell(board,row,2))) {
        if (symbol == 'o') return 1;
        else if (symbol == 'x') return -1;
    }
    return 0;
}

int Board::completedColumn(const char& symbol, const char (&board)[3][3], const int& row, const int& col) {
    if ((getCell(board,0,col) == getCell(board,1,col) && getCell(board,0,col) == getCell(board,2,col))) {        
        if (symbol == 'o') return 1;
        else if (symbol == 'x') return -1;

    }
    return 0;
}

int Board::completedDiagnoal(const char& symbol, const char (&board)[3][3], const int& row, const int& col) {
    if ((row == 0 && (col == 0 || col == 2)) || (row == 2 && (col == 0 || col == 2)) || (row == 1 && col == 1)) {
        if ((getCell(board,1,1) == getCell(board,0,0) && getCell(board,1,1) == getCell(board,2,2)) || (getCell(board,1,1) == getCell(board,0,2) && getCell(board,1,1) == getCell(board,2,0))) {
            if (getCell(board,1,1) == ' ') return 0;
            
            if (symbol == 'o') return 1;
            else if (symbol == 'x') return -1;
        }
    }
    return 0;
}

int Board::gameStatus(const char& symbol, const char (&board)[3][3], const int& row, const int& col) {
    if (completedRow(symbol,board,row,col) != 0) return completedRow(symbol,board,row,col);
    else if (completedColumn(symbol,board,row,col) != 0) return completedColumn(symbol,board,row,col);
    else if (completedDiagnoal(symbol,board,row,col) != 0) return completedDiagnoal(symbol,board,row,col);
    return 0;
}

bool Board::isFilled(const char (&board)[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') return false; 
        }
    }
    return true;
}

int Board::winner(const char (&board)[3][3]) {
    //Checks rows for 3 in a row
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            if (board[i][0] == 'o') return 1;
            if (board[i][0] == 'x') return -1;
        }
    }
    //Checks columns for 3 in a row
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            if (board[0][i] == 'o') return 1;
            if (board[0][i] == 'x') return -1;
        }
    }
    //Checks diagnoals
    if (board[1][1] == board[0][0] && board[1][1] == board[2][2]) {
        if (board[1][1] == 'o') return 1;
        if (board[1][1] == 'x') return -1;
    }
    if (board[1][1] == board[0][2] && board[1][1] == board[2][0]) {
        if (board[1][1] == 'o') return 1;
        if (board[1][1] == 'x') return -1;
    }

    return 0;
}

void Board::cloneBoard(char (&lhs)[3][3], const char (&rhs)[3][3]) {for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) lhs[i][j] = rhs[i][j];}

void Board::drawBoard(const char (&board)[3][3]) {
    std::cout<<"       |       |       \n";
    std::cout<<"   "<<getCell(board,0,0)<<"   |   "<<getCell(board,0,1)<<"   |   "<<getCell(board,0,2)<<"   \n";
    std::cout<<"_______|_______|_______\n";
    std::cout<<"       |       |       \n";
    std::cout<<"   "<<getCell(board,1,0)<<"   |   "<<getCell(board,1,1)<<"   |   "<<getCell(board,1,2)<<"   \n";
    std::cout<<"_______|_______|_______\n";
    std::cout<<"       |       |       \n";
    std::cout<<"   "<<getCell(board,2,0)<<"   |   "<<getCell(board,2,1)<<"   |   "<<getCell(board,2,2)<<"   \n";
    std::cout<<"       |       |       \n";
}