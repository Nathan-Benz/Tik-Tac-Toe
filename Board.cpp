#include "Board.hpp"

Board::Board() {}

//Ensures the values are in range before continueing
bool Board::inRange(const int& row, const int& col) const {
    if (row < 0 || row > 2 || col < 0 || col > 2) return false;
    return true; 
}

//Updates the value in a cell based on the player's symbol and if it is empty
bool Board::updateCell(const char& symbol, const int& row, const int& col) {
    if (!inRange(row,col)) return false;
    if (!isCellEmpty(row,col)) return false;
    
    if (std::tolower(symbol) == 'x') board_[row][col] = -1; //p1 = 'x'
    else if (std::tolower(symbol) == 'o') board_[row][col] = 1; //p2 = 'x'
    else return false;

    return true;
}

//Checks if cell is empty, i.e. ' '
bool Board::isCellEmpty(const int& row, const int& col) {return board_[row][col] == 0;}

//Returns a character based on the value of the cell
char Board::getCell(const int& row, const int& col) const{
    if(!inRange(row,col)) return ' ';

    if (board_[row][col] == -1) return 'x';
    else if (board_[row][col] == 1) return 'o';
    else return ' ';
}

//Draws the board
void Board::drawBoard() {
    //std::system("cls");
    std::cout<<"       |       |       \n";
    std::cout<<"   "<<getCell(0,0)<<"   |   "<<getCell(0,1)<<"   |   "<<getCell(0,2)<<"   \n";
    std::cout<<"_______|_______|_______\n";
    std::cout<<"       |       |       \n";
    std::cout<<"   "<<getCell(1,0)<<"   |   "<<getCell(1,1)<<"   |   "<<getCell(1,2)<<"   \n";
    std::cout<<"_______|_______|_______\n";
    std::cout<<"       |       |       \n";
    std::cout<<"   "<<getCell(2,0)<<"   |   "<<getCell(2,1)<<"   |   "<<getCell(2,2)<<"   \n";
    std::cout<<"       |       |       \n";
    
}

//Sets all the values in board to 0
void Board::resetBoard() {for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) board_[i][j] = 0;}


//The following functions take a board as a reference instead of modifying or gathering data from the main board
bool Board::updateCell(int (&clone_board)[3][3], const char& symbol, const int& row, const int& col) {
    if (!inRange(row,col)) return false;
    if (!isCellEmpty(clone_board,row,col)) return false;
    
    if (std::tolower(symbol) == 'x') clone_board[row][col] = -1; //p1 = 'x'
    else if (std::tolower(symbol) == 'o') clone_board[row][col] = 1; //p2 = 'x'
    else return false;

    return true;
}

bool Board::isCellEmpty(int (&clone_board)[3][3], const int& row, const int& col) {return clone_board[row][col] == 0;}

char Board::getCell(int (&clone_board)[3][3], const int& row, const int& col) const {
    if(!inRange(row,col)) return ' ';

    if (clone_board[row][col] == -1) return 'x';
    else if (clone_board[row][col] == 1) return 'o';
    else return ' ';
}