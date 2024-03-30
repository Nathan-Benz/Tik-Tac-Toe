#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <stdlib.h>

class Board {
public:
    Board();

    //Defaults all the cells in the board
    void initializeBoard(char (&board)[3][3]);

    //Sets all the values in board to ' ' (calls initialize)
    void resetBoard(char (&board)[3][3]);

    //Checks if cell is empty, i.e. ' '
    bool isCellEmpty(const char (&board)[3][3], const int& row, const int& col);

    //Ensures the values are in range before continueing
    bool inRange(const int& row, const int& col);

    //Updates the value in a cell based on the player's symbol and if it is empty
    bool updateCell(const char& symbol, char (&board)[3][3], const int& row, const int& col);

    //Returns a character based on the value of the cell
    char getCell(const char (&board)[3][3], const int& row, const int& col);

    //Checks if row is completed and by which symbol | ('o' : 1 | 'x' : -1 | ' ' : 0)
    int completedRow(const char& symbol, const char (&board)[3][3], const int& row, const int& col);

    //Checks if row is completed and by which symbol | ('o' : 1 | 'x' : -1 | ' ' : 0)
    int completedColumn(const char& symbol, const char (&board)[3][3], const int& row, const int& col);

    //Checks if diagnoal is completed and by which symbol | ('o' : 1 | 'x' : -1 | ' ' : 0)
    int completedDiagnoal(const char& symbol, const char (&board)[3][3], const int& row, const int& col);

    //Checks if game is finished. 1 then 'o' connected 3. -1 if 'x' connected 3. Zero otherwise
    int gameStatus(const char& symbol, const char (&board)[3][3], const int& row, const int& col);

    //Makes a new instance of a board
    void cloneBoard(char (&lhs)[3][3], const char (&rhs)[3][3]);

    //Draws the board
    void drawBoard(const char (&board)[3][3]);
};

#endif 