#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string>
#include "GameUser.h"
#include "Board.h"
#include "Move.h"

namespace laserchess {
    class User : public GameUser {
        public:
            User(){};
            ~User(){};
            GameMove* getUserMove(const GameBoard* board);
            Move* getMove(const Board* brd);
    };
}

#endif
