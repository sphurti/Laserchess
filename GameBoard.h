#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <assert.h>

#include "GameTeam.h"

// Generic board class for any board based games
class GameBoard {
  public:
    GameBoard() {}
    GameBoard(const GameBoard& board)
    {
        assert(false && "Cannot use base class copy constructor!");
    }
    /* The pure virtual prevents from instantiating the object
       of the class. */
    virtual ~GameBoard() = 0;
    virtual Team getTurn() const = 0;
    virtual void setTurn(Team) = 0;
    virtual void display() = 0;
};

// needs to be implemented since it'll be called by derived class destructor
inline GameBoard::~GameBoard() {}

#endif // GAMEBOARD_H
