#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <stdlib.h>

class Board {
public:
    Board();

    //Ensures the values are in range before continueing
    bool inRange(const int& row, const int& col) const;

    //Updates the value in a cell based on the player's symbol and if it is empty
    bool updateCell(const char& symbol, const int& row, const int& col);

    //Checks if cell is empty, i.e. ' '
    bool isCellEmpty(const int& row, const int& col);

    //Returns a character based on the value of the cell
    char getCell(const int& row, const int& col) const;

    //Draws the board
    void drawBoard();

    //Sets all the values in board to 0
    void resetBoard();

    bool updateCell(int (&clone_board)[3][3], const char& symbol, const int& row, const int& col);
    bool isCellEmpty(int (&clone_board)[3][3], const int& row, const int& col);
    char getCell(int (&clone_board)[3][3], const int& row, const int& col) const;


private:
    int board_[3][3] = {0,0,0,0,0,0,0,0,0};
};

#endif 