#include <Arduino.h>

enum GameMode
{
    MM = 0,
    MA = 1,
    AA = 2
};


/// @brief  This class is responsible for the game state, logic and AI
/// @note  Maybe it is better to split the AI logic into a separate class
/// @details This class called by the Pool class
class Game
{
protected:
    /// @brief Determines if the game has ended, if there is winner or if it's a tie it changes the isEnded and isTie variables
    /// @param mark The mark is user id
    void determineGameEnd(int mark);

    /// @brief Checks if someone has won the game or if it's a tie
    /// @param mark The mark is user id
    /// @return true if someone has won the game, false otherwise
    bool checkWin(int mark);

    /// @brief AI logic
    /// @param depth The depth of the minimax algorithm
    /// @param isMaximizingPlayer Determines if the AI is the maximizing player
    int minimax(int depth, bool isMaximizingPlayer);

public:
    /// @brief The board 
    ///        -1 is empty, 
    ///        0 is player 1, 
    ///        1 is player 2
    int board[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    
    /// @brief The turn if 1 is player 1, 2 is player 2
    int turn = 0;

    /// @brief The AI global state mark for the minimax algorithm
    int aiMark = 0;

    /// @brief The AI global state move to make for the minimax algorithm
    int moveToMake = 0;

    /// @brief State of the game
    bool isEnded = false;

    /// @brief Determines if the game is a tie
    bool isTie = false;

    /// @brief Determines if the game is against the AI or against another player 
    ///        0 is man vs man, 1 is man vs AI, 2 is AI vs AI
    GameMode gameMode = GameMode::MM;

    /// @brief Resets the board to the initial state
    /// @return Success message or error message
    String resetBoard();

    /// @brief Restores the board to a previous state
    /// @param board The board to restore
    /// @param isEnded Determines if the game has ended
    /// @param isTie Determines if the game is a tie
    void restoreBoard(int board[9], bool isEnded, bool isTie);

    /// @brief Makes a human turn
    /// @param id The id of the user
    /// @return Success message or error message
    String makeHumanTurn(int id);

    /// @brief Makes an AI turn
    /// @return Success message or error message
    String makeAITurn();
};
