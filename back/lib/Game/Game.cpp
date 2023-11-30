#include "Game.h"
#include <limits.h>

String Game::resetBoard()
{
    for (int i = 0; i < 9; i++)
    {
        board[i] = -1;
    }

    turn = 0;
    isEnded = false;
    isTie = false;

    return "success";
}


void Game::restoreBoard(int board[9], bool isEnded, bool isTie)
{
    for (int i = 0; i < 9; i++)
    {
        this->board[i] = board[i];
    }

    this->isEnded = isEnded;
    this->isTie = isTie;
}


int Game::minimax(bool isMaximizing)
{
    int score;

    if (checkWin(1))
    {
        score = 1;
    }
    else if (checkWin(0))
    {
        score = -1;
    }
    else if (turn >= 8)
    {
        score = 0;
    }
    else
    {
        int bestScore = isMaximizing ? INT_MIN : INT_MAX;

        for (int i = 0; i < 9; i++)
        {
            if (boardCopy[i] == -1)
            {
                boardCopy[i] = isMaximizing ? 1 : 0;
                turn++;

                int currentScore = minimax(!isMaximizing);

                boardCopy[i] = -1;
                turn--;

                if ((isMaximizing && currentScore > bestScore) || (!isMaximizing && currentScore < bestScore))
                {
                    bestScore = currentScore;
                }
            }
        }

        score = bestScore;
    }

    return score;
}

int Game::findBestMove()
{
    int bestMove = -1;
    int bestScore = INT_MIN;

    for (int i = 0; i < 9; i++)
    {
        if (boardCopy[i] == -1)
        {
            boardCopy[i] = 1;
            turn++;

            int currentScore = minimax(false);

            boardCopy[i] = -1;
            turn--;

            if (currentScore > bestScore)
            {
                bestScore = currentScore;
                bestMove = i;
            }
        }
    }

    return bestMove;
}


String Game::makeAITurn()
{
    if (isEnded)
    {
        return "error: game is ended";
    }

    for (int i = 0; i < 9; i++)
    {
        boardCopy[i] = board[i];
    }

    // Find the best move using Minimax
    int bestMove = findBestMove();

    // Make the AI move
    int mark = turn % 2;
    board[bestMove] = mark;

    // Check if the game has ended
    determineGameEnd(mark);

    return "success";
}



bool Game::checkWin(int mark)
{
  for (int i = 0; i < 3; i++)
  {
    if (
      (board[i * 3] == mark &&
       board[1 + i * 3] == mark &&
       board[2 + i * 3] == mark) || 
      (board[i] == mark && 
      board[3 + i] == mark &&
      board[6 + i] == mark)
    )
    {
      return true;
    }
  }

  if ((board[0] == mark && board[4] == mark && board[8] == mark) || 
      (board[2] == mark && board[4] == mark && board[6] == mark))
  {
    return true;
  }

  return false;
}


void Game::determineGameEnd(int mark)
{
  if (checkWin(mark))
  {
    isEnded = true;
  }

  else if (turn >= 8)
  {
    isEnded = true;
    isTie = true;
  }

  else if (!isEnded)
  {
    turn += 1;
  }
}


String Game::makeHumanTurn(int id)
{
  if (isEnded)
  {
    return "error: game is ended";
  }

  if (board[id] != -1)
  {
    return "error: invalid move";
  }

  int mark = turn % 2;
  board[id] = mark;

  determineGameEnd(mark);

  return "success";
}