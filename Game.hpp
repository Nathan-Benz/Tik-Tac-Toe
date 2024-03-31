#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <random>
#include <chrono>
#include <thread>

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
    void setAILevel(const std::pair<std::string, std::pair<bool, char>>& player);

    int humanMove(char (&board)[3][3], const char& symbol);
    int AIMove(char (&board)[3][3], const char& symbol, const int& level);
    int AIEasy(char (&board)[3][3], const char& symbol);
    int AIMedium(char (&board)[3][3], const char& symbol);
    int AIHard(char (&board)[3][3], const char& symbol);
    int AIImpossible(char (&board)[3][3], const char& symbol);
    int minimax(const char& symbol, char (&board)[3][3], int depth, bool maximing, int row, int col);

    void stringToLower(std::string &s) const;
    void pause() const;
    char invertSymbol(const char& symbol) const;

private:
    //Player - Name (Human or AI) , {(human or ai), ('o', or 'x')}
    std::pair<std::string, std::pair<bool, char>> player1, player2;
    int finished, ai_1_lvl, ai_2_lvl;
};

#endif
