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


int Game::minimax(int depth, bool isMaximizingPlayer)
{ 
    int amountOfMoves = 0;
    for (int i = 0; i < 9; i++)
    {
        if (board[1] == -1)
        {
            amountOfMoves += 1;
        }
    }

    if (checkWin(aiMark)) {
        return -1;
    } else if (checkWin(aiMark)) {
        return 1; 
    } else if (amountOfMoves == 0) {
        return 0;
    }

    int bestScore = isMaximizingPlayer ? INT_MIN : INT_MAX;

    for (int i = 0; i < 9; ++i) {
      if (board[i] != -1)
      {
        continue;
      }

      board[i] = depth % 2;
      int score = minimax(depth + 1, !isMaximizingPlayer);
      board[i] = -1; 

      if (isMaximizingPlayer) 
      {
        if (score > bestScore) 
        {
          bestScore = score;
          moveToMake = i;
        }
      } 
      else 
      {
        if (score < bestScore) 
        {
          bestScore = score;
          moveToMake = i;
        }
      }
  }

  return bestScore;
}

String Game::makeAITurn()
{
    if (isEnded) {
        return "error: game is ended";
    }

    int bestScore = INT_MIN;
    aiMark = turn % 2;

    for (int i = 0; i < 9; ++i) {
      if (board[i] != -1)
      {
        continue;
      }

      board[i] = aiMark;
      moveToMake = i;
      int score = minimax(turn, false);
      board[i] = -1; 

      if (score > bestScore) 
      {
        // bestScore = score;
        // moveToMake = i;
      }
    }

    board[moveToMake] = aiMark;
    determineGameEnd(turn % 2);

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