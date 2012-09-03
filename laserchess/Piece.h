#ifndef PIECE_H
#define PIECE_H

#include <list>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <locale>
#include <iostream>

#include "GameTeam.h"

namespace laserchess {
    enum PieceState
    {
        ACTIVE,
        DEAD,
        NO_STATE,
    };

    struct Position
    {
        uint32_t row;
        uint32_t col;
    };

    class Piece
    {
        enum PieceType
        {
            KING,
            LASER,
            HYPERCUBE,
            BEAMSPLITTER,
            BLOCK,
            MIRROR_ST,
            MIRROR_DL,
            MIRROR_TR,
            HYPER_HOLE,
        };

        enum Orientation
        {
            V,
            H,
            F_SL,
            B_SL,
            N,
            S,
            E,
            W,
            NE,
            NW,
            SE,
            SW,
            NO_ORI,
        };

        friend class Board;
        friend class Move;
      private:
        const PieceType ptype;
        const Team pteam;
        Orientation ori;
        PieceState pState;
        Position pos;
        bool rotateable;
        bool capture_enabled;
        bool armed;

      public:
        Piece(PieceType pt, Team t, Orientation o, PieceState ps, uint32_t r,
                uint32_t c);
        ~Piece(){};

        // Piece capabilities
        bool can_capture() const { return capture_enabled; }
        bool can_rotate() const { return rotateable; }
        bool can_reflect(Orientation beam_ori) const;
        bool is_transparent() const;
        bool can_fire() const { return armed; }

        // Piece actions
        void rotate_c();
        void rotate_ac();
        void getReflectedOrientations(Orientation,
                std::list<Orientation>& ori_list);

        static Orientation opp_orient(Orientation o);
        static Orientation adj_orient_ac(Orientation o);
        static Orientation adj_orient_c(Orientation o);

        // display piece
        void display();
      private:
        void teleportRandom();
        float score() const;
    };
}

#endif
