#include "Move.h"
#include <assert.h>
#include <stdlib.h>

namespace laserchess {
    Move::Move(uint32_t p_r, uint32_t p_c, const Board* brd, const MoveType type,
        const Team t) :
            piece_r(p_r),
            piece_c(p_c),
            board(brd),
            turn(t),
            m_typ(type),
            tport_info(NULL)
    {
    }

    Move::Move(const Move& m) :
        piece_r(m.piece_r),
        piece_c(m.piece_c),
        board(m.board),
        turn(m.turn),
        m_typ(m.m_typ)
    {
        fprintf(stderr, "Copy con called\n");
        if (m.tport_info)
            tport_info = new TeleportInfo(m.tport_info->row,
                    m.tport_info->col, m.tport_info->ori);
    }

    Move::~Move()
    {
        // TODO
    }

    void Move::getPieceDestination(int32_t& dst_r, int32_t& dst_c) const
    {
        switch (m_typ) {
            case MOVE_LEFT:
                dst_r = piece_r;
                dst_c = piece_c - 1;
                break;
            case MOVE_RIGHT:
                dst_r = piece_r;
                dst_c = piece_c + 1;
                break;
            case MOVE_UP:
                dst_r = piece_r + 1;
                dst_c = piece_c;
                break;
            case MOVE_DOWN:
                dst_r = piece_r - 1;
                dst_c = piece_c;
                break;
            default:
                break;
        }
    }

    void Move::printMove() const
    {
        fprintf(stderr, "Move: ");
        switch(m_typ) {
            case MOVE_LEFT:
                fprintf(stderr, "MOVE_LEFT"); break;
            case MOVE_RIGHT:
                fprintf(stderr, "MOVE_RIGHT"); break;
            case MOVE_UP:
                fprintf(stderr, "MOVE_UP"); break;
            case MOVE_DOWN:
                fprintf(stderr, "MOVE_DOWN"); break;
            case ROTATE_C:
                fprintf(stderr, "ROTATE_C"); break;
            case ROTATE_AC:
                fprintf(stderr, "ROTATE_AC"); break;
            case FIRE:
                fprintf(stderr, "FIRE"); break;
        }
        fprintf(stderr, " at (%d, %d)\n", piece_r, piece_c);
    }

    // initialize the two moves of the double move.
    DoubleMove::DoubleMove(const Move* m1, const Move* m2)
    {
        move_1 = const_cast<Move*>(m1);
        move_2 = const_cast<Move*>(m2);
    }

    DoubleMove::~DoubleMove()
    {
    }

    GameMove* DoubleMove::clone() const
    {
        DoubleMove* m_clone = new DoubleMove(move_1, move_2);
        return dynamic_cast<GameMove*>(m_clone);
    }

    void DoubleMove::printMove() const
    {
        move_1->printMove();
        move_2->printMove();
    }
}
