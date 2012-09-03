#ifndef GAME_H
#define GAME_H
#include "GameBoard.h"
#include "GameMove.h"
#include "GameUser.h"
#include <list>

#define REGISTER_GAME(x) extern "C"\
    Game* __gametree_create_game(void)\
    {\
        return new x();\
    }\
    extern "C" void __gametree_destroy_game(Game* game)\
    {\
        delete game;\
    }

class Game {
  public:
    Game() {}
    virtual ~Game() {}
    virtual void init(GameBoard*& board) = 0;
    virtual void initUser(GameUser*& usr) = 0;
    virtual void generateMoves(const GameBoard* board,
            std::list<GameMove*>& moves) = 0;
    virtual float evaluateBoard(const GameBoard* board) = 0;
    /* Apply the move to board and update new_board with the resulting
     * position */
    virtual bool applyMove(const GameBoard* board, GameBoard*& new_board,
            const GameMove* move) = 0;
};

#endif // GAME_H
