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
    void checkWin(int mark);

public:
    int board[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int turn = 0;
    bool isEnded = false;
    bool isTie = false;

    GameMode gameMode = GameMode::MM;

    String resetBoard();
    void restoreBoard(int board[9], bool isEnded, bool isTie);

    String makeHumanTurn(int id);
    String makeAITurn();
};
