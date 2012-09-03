#include "AlphaBetaParallel.h"
#include <limits>
#include <omp.h>
#include <stdio.h>
#include <vector>

namespace alphabetaparallel {
    AlphaBetaParallel::AlphaBetaParallel(Game* game) :
        GameTree(game)
    {
    }

    AlphaBetaParallel::~AlphaBetaParallel()
    {
    }

    GameMove* AlphaBetaParallel::getNextMove(const GameBoard* board, uint32_t max_depth)
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

    /* alpha (lower bound): Keeps track of the highest score obtained at a
     * maximizing node higher up in the tree and is used to perform cut-oﬀs at
     * minimizing nodes.
     * beta (upper bound): Keeps track of the lowest score obtained at a
     * minimizing node higher up in the tree and is used to perform cut-oﬀs at
     * maximizing nodes.
     */
    bool AlphaBetaParallel::AlphaBeta(const GameBoard* board, uint32_t depth,
            uint32_t max_depth,
            float alpha, float beta, float& chosen_score,
            GameMove*& chosen_move)
    {
        // if we've reached the leaves, evaluate board
        if (depth == max_depth) {
            chosen_score = game_->evaluateBoard(board);
            return true;
        }
        // initialize scores
        float score;
        if (board->getTurn() == WHITE)
            score = alpha;
        else
            score = beta;

        // initialize chosen move
        chosen_move = NULL;

        // generate all possible moves
        std::list<GameMove*> moves_list;
        game_->generateMoves(board, moves_list);
        if (moves_list.empty()) {
            chosen_score = game_->evaluateBoard(board);
            return true;
        }

        // calculate the PVS
        std::list<GameMove*>::iterator it = moves_list.begin();
        {
            GameBoard* new_board;
            GameMove* new_move;
            float game_tree_value;
            game_->applyMove(board, new_board, *it);

            // find score of new position
            if (board->getTurn() == WHITE) {
                AlphaBeta(new_board, depth + 1, max_depth, score, beta,
                        game_tree_value, new_move);
                if (game_tree_value >= beta) {
                    chosen_move = *it; // CORRECT?
                    chosen_score = beta;
                } else if (game_tree_value > score) {
                    score = game_tree_value;
                    chosen_move = *it;
                }
            } else {
                AlphaBeta(new_board, depth + 1, max_depth, alpha, score,
                        game_tree_value, new_move);
                if (game_tree_value <= alpha) {
                    chosen_score = alpha;
                    chosen_move = new_move;
                } else if (game_tree_value < score) {
                    score = game_tree_value;
                    chosen_move = *it;
                }
            }
            delete new_board;
        }
        it++;

        std::list<GameMove*>::iterator mov_it;
        std::vector<GameMove*> mvec;
        for ( ; it != moves_list.end(); ++it)
            mvec.push_back(*it);
        bool pruned = false;
        #pragma omp parallel \
                private(score) \
                shared(board, depth, max_depth, alpha, beta, pruned)
        {
            #pragma omp for
            for (uint32_t i=0; i<mvec.size(); i++) {
                #pragma omp flush (pruned)
                if (!pruned) {
                    // generate new board position
                    GameBoard* new_board;
                    GameMove* new_move;
                    float game_tree_value;
                    game_->applyMove(board, new_board, mvec[i]);

                    // find score of new position
                    if (board->getTurn() == WHITE) {
                        AlphaBeta(new_board, depth + 1, max_depth, score, beta,
                                game_tree_value, new_move);
                        #pragma omp flush (beta)
                        if (game_tree_value >= beta) {
                            #pragma omp critical
                            chosen_move = mvec[i]; // CORRECT?
                            chosen_score = beta;
                            pruned = true;
                        }
                        if (game_tree_value > score) {
                            #pragma omp critical
                            score = game_tree_value;
                            chosen_move = mvec[i];
                        }
                    } else {
                        AlphaBeta(new_board, depth + 1, max_depth, alpha, score,
                                game_tree_value, new_move);
                        #pragma omp flush (alpha)
                        if (game_tree_value <= alpha) {
                            #pragma omp critical
                            chosen_score = alpha;
                            chosen_move = new_move;
                            pruned = true;
                        }
                        if (game_tree_value < score) {
                            #pragma omp critical
                            score = game_tree_value;
                            chosen_move = mvec[i];
                        }
                    }
                    delete new_board;
                }
            }
        }
        if (!pruned)
            chosen_score = score;
        it = moves_list.begin();
        for ( ; it != moves_list.end(); ++it)
            if (*it != chosen_move)
                delete *it;
        return true;
    }
    REGISTER_GAME_TREE(AlphaBetaParallel);
}
