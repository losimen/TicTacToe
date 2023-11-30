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


void Game::restoreBoard(int board[9], bool isEnded, bool isTie)
{
    for (int i = 0; i < 9; i++)
    {
        this->board[i] = board[i];
    }

    this->isEnded = isEnded;
    this->isTie = isTie;
}

String Game::makeAITurn()
{
  if (isEnded)
  {
    return "error: game is ended";
  }

  int mark = turn % 2;
  int bestMove = -1;

  while (true)
  {
    bestMove = random(0, 9);

    if (board[bestMove] == -1)
      break;
  }
  board[bestMove] = mark;

  checkWin(mark);

  return "success";
}


void Game::checkWin(int mark)
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

  checkWin(mark);

  return "success";
}