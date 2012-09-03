#ifndef MOVE_H
#define MOVE_H

#include <stdio.h>
#include <string>
#include "Board.h"
#include "GameMove.h"
#include "Piece.h"

namespace laserchess {
    class Board;
    // enum to keep track of different types of moves
    enum MoveType
    {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        FIRE,
        ROTATE_C,
        ROTATE_AC,
    };

    //This class is used to keep track of game moves
    class Move
    {
      public:
        // stores info about teleported pieces
        class TeleportInfo {
          public:
            TeleportInfo(uint32_t r, uint32_t c,
                    Piece::Orientation o)
            {
                row = r; col = c; ori = o;
            }
            ~TeleportInfo() {}
            uint32_t row;
            uint32_t col;
            Piece::Orientation ori;
        };
        // Board class can now access the private members of the Move class
        friend class Board;
        friend class LaserChess;
      private:
        // start position of the move
        const uint32_t piece_r, piece_c;
        /* Current Board psition to which this moves is applicable
        constant pointer to constant board. Neither the pointer nor the 
        the board value will change
        */
        const Board* const board;
        // The team to which this move refers
        const Team turn;
        // The type of the move
        const MoveType m_typ;
        TeleportInfo* tport_info;

      public:
        Move(uint32_t p_r, uint32_t p_c, const Board* brd, const MoveType type,
                const Team t);
        Move(const Move& m);
        ~Move();
        // check to determine if the Move is of type move
        bool isMove() const { return (m_typ >= MOVE_LEFT && m_typ <= MOVE_DOWN); }
        // check to find if the move is of type fire
        bool isFire() const { return (m_typ == FIRE); }
        // check to determine if the move is of type rotate
        bool isRotate() const { return (m_typ == ROTATE_C || m_typ == ROTATE_AC); }
        /* Depending on the move type, the values of the row and column
           of the piece is calculated */
        void getPieceDestination(int32_t& dst_r, int32_t& dst_c) const;
        void printMove() const;
    };  

    /*
        In laserchess, each turn allows the team to make two moves.
        The double move class is used to keep track of the two moves
        the player makes per turn. It inherits the generic GameMove class
    */ 
    class DoubleMove : public GameMove {
      private:
        Move* move_1;
        Move* move_2;
      public:
        DoubleMove(const Move* m1, const Move* m2);
        ~DoubleMove();
        GameMove* clone() const;
        // returns the first move of the turn
        Move* first() const { return move_1; }
        // returns the second move of the turn
        Move* second() const { return move_2; }
        void printMove() const;
    };
}

#endif  
