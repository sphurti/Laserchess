#ifndef GAMEUSER_H
#define GAMEUSER_H

#include "GameMove.h"
#include "GameBoard.h"

class GameUser {
  public:
    GameUser() {}
    virtual ~GameUser() {};
    virtual GameMove* getUserMove(const GameBoard* board) = 0;
};

#endif // GAMEUSER_H
