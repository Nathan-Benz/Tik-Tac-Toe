#include "Game.hpp"

Game::Game() : Board(), player1{"", {false, ' '}}, player2{"", {false, ' '}}, finished{0}, ai_1_lvl{-1}, ai_2_lvl{-1} {}

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
    else {player1.first = "AI_1";player1.second.first = false; setAILevel(player1);}
    
    do {
        std::cout << "\033[2J\033[H";
        std::cout<<"Will Player 2 be Human or AI? | [HUMAN] / [AI]: ";
        std::cin>>decision;
        stringToLower(decision);

    } while (decision != "human" && decision != "ai");

    if (decision == "human") {player2.first = "HUMAN_2";player2.second.first = true;}
    else {player2.first = "AI_2";player2.second.first = false; setAILevel(player2);}

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
        else std::cout<<"IT'S A DRAW! NO ONE WINS.";

        std::cout<<"\n";

        drawBoard(board);

        std::cout<<"Do you want to play again? | [Y] / [N]: ";
        std::cin>>decision;

    }   while (tolower(decision) != 'y' && tolower(decision) != 'n');

    if (tolower(decision) == 'y') match();
}

int Game::PvP(char (&board)[3][3]) {
    int turns = 0, finished = 0;
    
    do {
        std::cout<<player1.first<<"'s Turn. ("<<player1.second.second<<")\n";
        drawBoard(board);
        finished = humanMove(board, player1.second.second);
        turns++;

        if (finished != 0 || turns >= 9) break;

        std::cout<<player2.first<<"'s Turn. ("<<player2.second.second<<")\n";
        drawBoard(board);
        finished = humanMove(board, player2.second.second);
        turns++;

    }   while(finished == 0 && turns < 9);

    drawBoard(board);

    return finished;
}

int Game::PvAI(char (&board)[3][3]) {
    int turns = 0, finished = 0;
    
    std::cout << "\033[2J\033[H";

    do {
        std::cout<<player1.first<<"'s Turn. ("<<player1.second.second<<")\n";
        drawBoard(board);
        finished = humanMove(board, player1.second.second);
        turns++;

        if (finished != 0 || turns >= 9) break;

        finished = AIMove(board, player2.second.second, ai_2_lvl);
        turns++;

    }   while(finished == 0 && turns < 9);

    drawBoard(board);

    return finished;
}

int Game::AIvP(char (&board)[3][3]) {
    int turns = 0, finished = 0;
    
    std::cout << "\033[2J\033[H";

    do {
        finished = AIMove(board, player1.second.second, ai_1_lvl);
        turns++;

        if (finished != 0 || turns >= 9) break;

        std::cout<<player2.first<<"'s Turn. ("<<player2.second.second<<")\n";
        drawBoard(board);
        finished = humanMove(board, player2.second.second);
        turns++;

    }   while(finished == 0 && turns < 9);

    drawBoard(board);

    return finished;
}

int Game::AIvAI(char (&board)[3][3]) {
    int turns = 0, finished = 0;
    
    std::cout << "\033[2J\033[H";

    do {
        pause();

        std::cout<<player1.first<<"'s Turn. ("<<player1.second.second<<")\n";
        finished = AIMove(board, player1.second.second, ai_1_lvl);
        drawBoard(board);
        turns++;

        if (finished != 0 || turns >= 9) break;

        pause();

        std::cout<<player2.first<<"'s Turn. ("<<player2.second.second<<")\n";
        finished = AIMove(board, player2.second.second, ai_2_lvl);
        drawBoard(board);
        turns++;

        

    }   while(finished == 0 && turns < 9);

    drawBoard(board);

    return finished;
}

int Game::humanMove(char (&board)[3][3], const char& symbol) {
    int row, col;

    do {
        std::cout<<"Enter a row then a column: ";
        std::cin>>row>>col; 

    }   while (!updateCell(symbol, board, row, col));

    return gameStatus(symbol,board,row,col);
}

int Game::AIMove(char (&board)[3][3], const char& symbol, const int& level) {
    if (level == 0) return AIEasy(board, symbol);
    else if (level == 1) return AIMedium(board, symbol);
    else if (level == 2) return AIHard(board, symbol);
    else if (level == 3) return AIImpossible(board, symbol);
    return 0;
}

int Game::AIEasy(char (&board)[3][3], const char& symbol) {
    int row;
    int col;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);

    do {
        row = dist(gen);
        col = dist(gen);
        
    }   while (!updateCell(symbol, board,row,col));

    return gameStatus(symbol, board, row, col);
}

int Game::minimax(char (&board)[3][3], int depth, bool maxing, int alpha, int beta) {
    if (winner(board) != 0 || depth == 0 || isFilled(board)) {
        if (maxing) return winner(board);
        else return winner(board);
    }

    int best_score = (maxing)? INT_MIN : INT_MAX;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (isCellEmpty(board,i,j)) {
                if (maxing) {
                    updateCell('o',board,i,j);
                    int score = minimax(board,depth - 1,false, alpha, beta);
                    board[i][j] = ' ';

                    best_score = std::max(best_score,score);
                    alpha = std::max(alpha, score);

                    if (beta <= alpha) return best_score;
                }
                else {
                    updateCell('x',board,i,j);
                    int score = minimax(board,depth - 1,true, alpha, beta);
                    board[i][j] = ' ';

                    best_score = std::min(best_score,score);
                    beta = std::min(beta, score);

                    if (beta <= alpha) return best_score;
                }
            }
        }
    }

    return best_score;
}

int Game::AIMinimaxCaller(char (&board)[3][3], const char& symbol, const int& depth) {
    int best_score = (symbol == 'o')? INT_MIN : INT_MAX;
    std::vector<std::pair<int,int>> best_move;
    bool maximizing = (symbol == 'o');

    char clone[3][3];
    cloneBoard(clone,board);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (isCellEmpty(clone,i,j)) {
                updateCell(symbol,clone,i,j);
                int score = (maximizing)? minimax(clone,depth,false, INT_MIN, INT_MAX) : minimax(clone,depth,true, INT_MIN, INT_MAX); 
                clone[i][j] = ' ';

                if ((maximizing && score > best_score) || (!maximizing && score < best_score)) {
                    best_score = score;
                    best_move.clear();
                    best_move.push_back({i,j});
                }
                else if ((maximizing && score == best_score) || (!maximizing && score == best_score)) {best_move.push_back({i,j});}
            }
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,best_move.size() - 1);

    int num = dist(gen);

    updateCell(symbol,board,best_move[num].first,best_move[num].second);
    return gameStatus(symbol,board,best_move[num].first,best_move[num].second);
}

int Game::AIMedium(char (&board)[3][3], const char& symbol) {return AIMinimaxCaller(board,symbol,2);}

int Game::AIHard(char (&board)[3][3], const char& symbol) {return AIMinimaxCaller(board,symbol,4);}
    
int Game::AIImpossible(char (&board)[3][3], const char& symbol) {return AIMinimaxCaller(board,symbol,INT_MAX);}

void Game::setAILevel(const std::pair<std::string, std::pair<bool, char>>& player) {
    int level;
    do {
        std::cout << "\033[2J\033[H";
        std::cout<<"Select AI dificculty level [0 - 3]: ";
        std::cin>>level;

    } while (level < 0 || level > 3);

    if (player.first == "AI_1") ai_1_lvl = level;
    else ai_2_lvl = level;
}

void Game::stringToLower(std::string &s) const {for (int i = 0; i < s.size(); ++i) s[i] = std::tolower(s[i]);}

void Game::pause() const {std::cout << "Press enter to see next move.\n";std::cin.ignore();}

char Game::invertSymbol(const char& symbol) const {return (symbol == 'x')? 'o' : 'x';}