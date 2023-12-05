#include <Arduino.h>

enum GameMode
{
    MM = 0,
    MA = 1,
    AA = 2
};

class Game
{
protected:
    void determineGameEnd(int mark);
    bool checkWin(int mark);
    int minimax(int depth, bool isMaximizingPlayer);

public:
    int board[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    
    int turn = 0;
    int aiMark = 0;
    int moveToMake = 0;

    bool isEnded = false;
    bool isTie = false;

    GameMode gameMode = GameMode::MM;

    String resetBoard();
    void restoreBoard(int board[9], bool isEnded, bool isTie);

    String makeHumanTurn(int id);
    String makeAITurn();
};
