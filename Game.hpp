#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <iostream>
#include <string>
#include <utility>

class Game : public Board {
public:
    Game();

    void match();
    void gameSetUp();
    void matchOver(const char (&board)[3][3], const int& result);

    int PvP(char (&board)[3][3]);
    int PvAI(char (&board)[3][3]);
    int AIvP(char (&board)[3][3]);
    int AIvAI(char (&board)[3][3]);

    int humanMove(char (&board)[3][3], const std::pair<std::string, std::pair<bool, char>>& player);
    void AIMove(char (&board)[3][3], const std::pair<std::string, std::pair<bool, char>>& player);

    void stringToLower(std::string &s) const;

private:
    //Player - Name (Human or AI) , {(human or ai), ('o', or 'x')}
    std::pair<std::string, std::pair<bool, char>> player1, player2;
    int finished;
};

#endif
