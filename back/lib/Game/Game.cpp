#include "Game.h"

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


String Game::makeTurn(int id)
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
      isEnded = true;
    }
  }

  if ((board[0] == mark && board[4] == mark && board[8] == mark) || 
      (board[2] == mark && board[4] == mark && board[6] == mark))
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

  return "success";
}