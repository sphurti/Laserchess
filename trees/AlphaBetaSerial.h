#ifndef ALPHABETASERIAL_H
#define ALPHABETASERIAL_H
#include "GameTree.h"
#include "GameMove.h"

namespace alphabetaserial {
    class AlphaBetaSerial : public GameTree {
        public:
            AlphaBetaSerial(Game* game);
            ~AlphaBetaSerial();
            GameMove* getNextMove(const GameBoard* board, uint32_t max_depth);
        private:
            bool AlphaBeta(const GameBoard* board, uint32_t depth, uint32_t max_depth,
                    float alpha, float beta, float& chosen_score,
                    GameMove*& chosen_move);
    };
}

#endif // ALPHABETASERIAL_H
