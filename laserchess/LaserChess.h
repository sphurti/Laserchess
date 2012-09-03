#ifndef LASERCHESS_H
#define LASERCHESS_H
#include "Game.h"
#include "Move.h"
#include "Board.h"
#include "User.h"
#include <list>

namespace laserchess {
    /*  
        Laserchess is the derived class of the generic class Game.
        This is the main class for the laser chess game
    */
    class LaserChess : public Game {
      public:
        LaserChess();
        ~LaserChess();
        // Create and initialize the board for the game 
        void init(GameBoard*& board);
        // create a new user for the game
        void initUser(GameUser*& usr);
        // generate all possible moves for the given the board position
        void generateMoves(const GameBoard* board,
                std::list<GameMove*>& moves);
        // Evaluate the vale of the curent board
        float evaluateBoard(const GameBoard* board);
        // Given the board and move, make a move on the board
        bool applyMove(const GameBoard* board, GameBoard*& new_board,
                const GameMove* move);
    };
}

#endif // LASERCHESS_H
