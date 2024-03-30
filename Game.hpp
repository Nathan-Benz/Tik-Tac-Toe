#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <iostream>

class Game : public Board {
public:
    Game();

    void gameManager(const bool& play_ai);
    void playerSelect();
    void resetGame();

    int playerTurn();
    int opponentTurn();

    int Turn(const char& player, const bool& main_player);
    int aiTurn();
    int minimax(int (&curr_board)[3][3], int depth, bool maximixing, int row, int col);

    bool checkRow(const int& row) const;
    bool checkCol(const int& col) const;
    bool checkDiagnoal() const;
    bool checkBoard(const int& row, const int& col) const;
    bool isComplete() const;

    //The folowing functions handle a clone game state and not the original
    bool checkRow(int (&curr_board)[3][3], const int& row) const;
    bool checkCol(int (&curr_board)[3][3], const int& col) const;
    bool checkDiagnoal(int (&curr_board)[3][3]) const;
    bool checkBoard(int (&curr_board)[3][3], const int& row, const int& col) const;

private:
    int total_turns;
    char player1, player2;
    bool complete_;
};

#endif
