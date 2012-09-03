#include "LaserChess.h"
#include <stdlib.h>

namespace laserchess {
    LaserChess::LaserChess()
    {
    }

    LaserChess::~LaserChess()
    {
    }

    void LaserChess::init(GameBoard*& board)
    {
        Board* init_board = new Board();
        board = dynamic_cast<GameBoard*>(init_board);        
    }

    void LaserChess::initUser(GameUser*& usr)
    {
        User* init_usr = new User();
        usr = dynamic_cast<GameUser*>(init_usr);
    }

    void LaserChess::generateMoves(const GameBoard* brd,
            std::list<GameMove*>& moves)
    {
        const Board* board = dynamic_cast<const Board*>(brd);

        std::list<Move*> single_moves;
        // get all possible single moves for the given board position
        board->getValidNextMoves(single_moves);

        // for each single move, generate all possible next moves
        std::list<Move*>::iterator it;
        for (it=single_moves.begin(); it != single_moves.end(); ++it) {
            Board* new_board = new Board(*board);
            new_board->applyMove(const_cast<Move*>(*it));

            // generate valid second moves
            std::list<Move*> next_moves;
//            fprintf(stderr, "Next moves for ");
//            it->printMove();
            new_board->getValidNextMoves(next_moves);
            std::list<Move*>::iterator next_it;

            // generate valid double moves
            for (next_it=next_moves.begin(); next_it != next_moves.end();
                    next_it++) {
                DoubleMove* db = new DoubleMove(*it, *next_it);
                if (board->valid(*db))
                    moves.push_back(dynamic_cast<GameMove*>(db));
            }
        }
    }

    float LaserChess::evaluateBoard(const GameBoard* board)
    {
        const Board* lc_board = dynamic_cast<const Board*>(board);
        return lc_board->evaluate();
    }

    bool LaserChess::applyMove(const GameBoard* board, GameBoard*& new_board,
            const GameMove* move)
    {
        // create const pointer to Board 
        const Board* lc_board = dynamic_cast<const Board*>(board);
        // create a copy of board
        Board* new_lc_board = new Board(*lc_board);
        // apply the move
        const DoubleMove* d = dynamic_cast<const DoubleMove*>(move);
        new_lc_board->applyMove(d);
        new_lc_board->setTurn(OTHER_TEAM(lc_board->turn));
        // cast new_lc_board to what has to be returned
        new_board = dynamic_cast<const GameBoard*>(new_lc_board);
        return true;
    }

REGISTER_GAME(LaserChess);
}

