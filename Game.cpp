#include "Game.hpp"

Game::Game() : Board(), player1{"", {false, ' '}}, player2{"", {false, ' '}}, finished{0} {}

void Game::match() {
    gameSetUp();

    int result = 0;
    char board[3][3];
    initializeBoard(board);

    if (player1.second.first && player2.second.first) result = PvP(board);
    else if (player1.second.first && !player2.second.first) result = PvAI(board);
    else if (!player1.second.first && player2.second.first) result = AIvP(board);
    else result = AIvAI(board);

    matchOver(board, result);
}

void Game::gameSetUp() {
    std::string decision;
    do {
        std::cout << "\033[2J\033[H";
        std::cout<<"Will Player 1 be Human or AI? | [HUMAN] / [AI]: ";
        std::cin>>decision;
        stringToLower(decision);

    } while (decision != "human" && decision != "ai");

    if (decision == "human") {player1.first = "HUMAN_1";player1.second.first = true;}
    else {player1.first = "AI_1";player1.second.first = false;}
    
    do {
        std::cout << "\033[2J\033[H";
        std::cout<<"Will Player 2 be Human or AI? | [HUMAN] / [AI]: ";
        std::cin>>decision;
        stringToLower(decision);

    } while (decision != "human" && decision != "ai");

    if (decision == "human") {player2.first = "HUMAN_2";player2.second.first = true;}
    else {player2.first = "AI_2";player2.second.first = false;}

    do {
        std::cout << "\033[2J\033[H";
        std::cout<<"Player 1 will be 'X' or 'O' | [X] / [O]: ";
        std::cin>>decision;
        stringToLower(decision);

    } while (decision != "x" && decision != "o");

    if (decision == "x") {player1.second.second = 'x';player2.second.second = 'o';}
    else {player1.second.second = 'o';player2.second.second = 'x';}

    do {
        std::cout << "\033[2J\033[H";
        std::cout<<player1.first<<" is: ( "<<player1.second.second<<" )\n";
        std::cout<<player2.first<<" is: ( "<<player2.second.second<<" )\n";

        std::cout<<"\nConintue? [Y] / [N]: ";
        std::cin>>decision;
        stringToLower(decision);

    } while (decision != "y" && decision != "n");

    if (decision == "n") gameSetUp();
}

void Game::matchOver(const char (&board)[3][3], const int& result) {
    char decision;
    do {
        if (result == 1) {
            if (player1.second.second == 'o') std::cout<<player1.first<<" ("<<player1.second.second<<") WINS!";
            else std::cout<<player2.first<<" ("<<player2.second.second<<") WINS!";
        }
        else if (result == -1) {
            if (player1.second.second == 'x') std::cout<<player1.first<<" ("<<player1.second.second<<") WINS!";
            else std::cout<<player2.first<<" ("<<player2.second.second<<") WINS!";
        }
        else std::cout<<"DRAWED GAME! NO ONE WINS.";

        std::cout<<"\n";

        drawBoard(board);

        std::cout<<"Do you want to play again? | [Y] / [N]: ";
        std::cin>>decision;

    }   while (tolower(decision) != 'y' && tolower(decision) != 'n');

    if (tolower(decision) == 'y') match();
}

int Game::PvP(char (&board)[3][3]) {
    int turns = 0, finished = 0;
    
    std::cout << "\033[2J\033[H";

    do {
        finished = humanMove(board, player1);
        turns++;

        if (finished != 0 || turns >= 9) break;

        finished = humanMove(board, player2);
        turns++;

    }   while(finished == 0 && turns < 9);

    drawBoard(board);

    return finished;
}

int Game::PvAI(char (&board)[3][3]) {
    int turns = 0, finished = 0;
    
    std::cout << "\033[2J\033[H";

    do {
        finished = humanMove(board, player1);
        turns++;

        if (finished != 0 || turns >= 9) break;

        finished = AIMove(board, player2, 0);
        turns++;

    }   while(finished == 0 && turns < 9);

    drawBoard(board);

    return finished;
}

int Game::AIvP(char (&board)[3][3]) {
    int turns = 0, finished = 0;
    
    std::cout << "\033[2J\033[H";

    do {
        finished = AIMove(board, player1, 0);
        turns++;

        if (finished != 0 || turns >= 9) break;

        finished = humanMove(board, player2);
        turns++;

    }   while(finished == 0 && turns < 9);

    drawBoard(board);

    return finished;
}

int Game::AIvAI(char (&board)[3][3]) {
    int turns = 0, finished = 0;
    
    std::cout << "\033[2J\033[H";

    do {
        finished = AIMove(board, player1, 0);
        turns++;

        if (finished != 0 || turns >= 9) break;

        finished = AIMove(board, player2, 0);
        turns++;

    }   while(finished == 0 && turns < 9);

    drawBoard(board);

    return finished;
}

int Game::humanMove(char (&board)[3][3], const std::pair<std::string, std::pair<bool, char>>& player) {
    int row, col;

    do {
        //std::system("cls");
        std::cout<<player.first<<"'s Turn. ("<<player.second.second<<")\n";
        drawBoard(board);
        std::cout<<"Enter a row then a column: ";
        std::cin>>row>>col; 

    }   while (!updateCell(player.second.second, board, row, col));

    return gameStatus(player.second.second, board, row, col);
}

int Game::AIMove(char (&board)[3][3], const std::pair<std::string, std::pair<bool, char>>& player, const int& level) {
    if (level == 0) return AIEasy(board, player);
    else if (level == 1) return AIMedium(board, player);
    else if (level == 2) return AIHard(board, player);
    else if (level == 3) return AIImpossible(board, player);
    return 0;
}

int Game::AIEasy(char (&board)[3][3], const std::pair<std::string, std::pair<bool, char>>& player) {
    int row;
    int col;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);

    do {
        row = dist(gen);
        col = dist(gen);
        
    }   while (!updateCell(player.second.second, board,row,col));

    std::cout<<player.first<<"'s Turn. ("<<player.second.second<<")\n";
    drawBoard(board);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string temp;
    std::cout<<"Press enter to continue.";
    std::getline(std::cin, temp);

    return gameStatus(player.second.second, board, row, col);
}

int Game::minimax() {}

int Game::AIMedium(char (&board)[3][3], const std::pair<std::string, std::pair<bool, char>>& player) {return 0;}

int Game::AIHard(char (&board)[3][3], const std::pair<std::string, std::pair<bool, char>>& player) {return 0;}
    
int Game::AIImpossible(char (&board)[3][3], const std::pair<std::string, std::pair<bool, char>>& player) {return 0;}

void Game::stringToLower(std::string &s) const {for (int i = 0; i < s.size(); ++i) s[i] = std::tolower(s[i]);}