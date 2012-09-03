#ifndef BOARD_H
#define BOARD_H

#include <assert.h>
#include <list>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "GameBoard.h"
#include "Piece.h"
#include "Move.h"

namespace laserchess {
    class Move;
    class DoubleMove;
    
    /*  This is the board class that is dervied class of the generic
        GameBoard class. The class keeps track of the board status 
        at any instance of the game. */ 
    class Board : public GameBoard
    {
        friend class LaserChess;
      private:
        const uint32_t numRow;          // number of rows on the board
        const uint32_t numCol;          // number of columns on the board
        Piece*** piece_array;           // position -> Piece* map
        std::vector<Piece*> white_p;    // white pieces
        std::vector<Piece*> black_p;    // black pieces
        Piece* hyperhole;               // The hyper-hole on the board
        //int totalMoves;                 
        Team turn;                      // the team which is required to make move

      public:
        Board();
        Board(const Board& brd);
        // initialize the board
        void init();
        // get the team whose is suppose to make a move
        Team getTurn() const;
        // set the turn of the team 
        void setTurn(Team t);
        float evaluate() const;

        uint32_t cols() const { return numCol; }
        uint32_t rows() const { return numRow; }
        
        // Apply the move passed to the board
        void applyMove(Move* m);
        // Apply the two moves to the board
        void applyMove(const DoubleMove* d);
        // Get a 
        void getValidNextMoves(std::list<Move*>& moves) const;
        // display the board
        void display();
      private:
        // helpers
        // returns the reference to the array of piece belong to current team
        std::vector<Piece*>& my_pieces() const;
        // returns the reference to array of pieces belonging to opossite team
        std::vector<Piece*>& opp_pieces() const;
        // Delete the piece from the array
        void deletePiece(Piece*& p);


        // Check if the move/double-move are valid
        bool valid(const Move& mv) const;
        bool valid(const DoubleMove& dmv) const;
        // check if move places the object within the board limits
        bool checkPositionValid(uint32_t dst_r, uint32_t dst_c) const;

        void handleFireMove(uint32_t orig_r, uint32_t orig_c,
                Piece::Orientation ori, uint32_t depth=0);
        Piece* findFirstPieceHit(uint32_t orig_r, uint32_t orig_c,
                Piece::Orientation ori) const;
    };
}

#endif
