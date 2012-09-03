#ifndef GAMETREE_H
#define GAMETREE_H
#include "Game.h"
#include <stdint.h>

#define REGISTER_GAME_TREE(x) extern "C"\
    GameTree* __gametree_create_tree(Game* game)\
    {\
        return new x(game);\
    }\
    extern "C" void __gametree_destroy_tree(GameTree* tree)\
    {\
        delete tree;\
    }

class GameTree {
  protected:
    Game* game_;
  public:
    GameTree(Game* game) :
            game_(game)
    {}
    virtual ~GameTree() {}
    virtual GameMove* getNextMove(const GameBoard* board,
            uint32_t max_depth) = 0;
};

#endif // GAMETREE_H

