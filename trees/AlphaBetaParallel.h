#ifndef ALPHABETAPARALLEL_H
#define ALPHABETAPARALLEL_H
#include "GameTree.h"
#include "GameMove.h"

namespace alphabetaparallel {
    class AlphaBetaParallel : public GameTree {
        public:
            AlphaBetaParallel(Game* game);
            ~AlphaBetaParallel();
            GameMove* getNextMove(const GameBoard* board, uint32_t max_depth);
        private:
            bool AlphaBeta(const GameBoard* board, uint32_t depth, uint32_t max_depth,
                    float alpha, float beta, float& chosen_score,
                    GameMove*& chosen_move);
    };
}

#endif // ALPHABETAPARALLEL_H
