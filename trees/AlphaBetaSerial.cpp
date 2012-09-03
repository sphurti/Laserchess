#include "AlphaBetaSerial.h"
#include <limits>
#include <stdio.h>

namespace alphabetaserial {
    AlphaBetaSerial::AlphaBetaSerial(Game* game) :
        GameTree(game)
    {
    }

    AlphaBetaSerial::~AlphaBetaSerial()
    {
    }

    GameMove* AlphaBetaSerial::getNextMove(const GameBoard* board, uint32_t max_depth)
    {
        float score;
        GameMove* move;
        AlphaBeta(board, 0, max_depth,
                -1 * std::numeric_limits<float>::infinity(),
                std::numeric_limits<float>::infinity(), score, move);
        fprintf(stderr, "Turn: %s\n", board->getTurn()==WHITE? "WHITE" : "BLACK");
        move->printMove();
        fprintf(stderr, "Score: %f\n", score);
        return move;
    }

    bool AlphaBetaSerial::AlphaBeta(const GameBoard* board, uint32_t depth, uint32_t max_depth,
            float alpha, float beta, float& chosen_score,
            GameMove*& chosen_move)
    {
        // if we've reached the leaves, evaluate board
        if (depth == max_depth) {
            chosen_score = game_->evaluateBoard(board);
            return true;
        }
        // initialize scores
        float score, game_tree_value;
        if (board->getTurn() == WHITE)
            score = alpha;
        else
            score = beta;

        // generate all possible moves
        std::list<GameMove*> moves_list;
        game_->generateMoves(board, moves_list);
        if (moves_list.empty()) {
            chosen_score = game_->evaluateBoard(board);
            return true;
        }

        std::list<GameMove*>::iterator it = moves_list.begin();
        for ( ; it != moves_list.end(); ++it) {
            // generate new board position
            GameBoard* new_board;
            GameMove* new_move;
            game_->applyMove(board, new_board, *it);

            // find score of new position
            if (board->getTurn() == WHITE) {
                AlphaBeta(new_board, depth + 1, max_depth, score, beta,
                        game_tree_value, new_move);
                if (game_tree_value >= beta) {
                    chosen_move = *it; // CORRECT?
                    chosen_score = beta;
                    return true;
                }
                if (game_tree_value > score) {
                    score = game_tree_value;
                    chosen_move = *it;
                }
            } else {
                AlphaBeta(new_board, depth + 1, max_depth, alpha, score,
                        game_tree_value, new_move);
                if (game_tree_value <= alpha) {
                    chosen_score = alpha;
                    chosen_move = new_move;
                    return true;
                }
                if (game_tree_value < score) {
                    score = game_tree_value;
                    chosen_move = *it;
                }
            }
        }
        chosen_score = score;
        return true;
    }
    REGISTER_GAME_TREE(AlphaBetaSerial);
}
