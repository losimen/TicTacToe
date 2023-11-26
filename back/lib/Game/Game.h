class Game
{
public:

    int board[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int turn = 0;
    bool isEnded = false;
    bool isTie = false;

    void resetBoard();

    void makeTurn(int id);
};
