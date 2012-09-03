#include "User.h"

namespace laserchess {
    GameMove* User::getUserMove(const GameBoard* board)
    {

        const Board* brd = dynamic_cast<const Board*>(board);   
        Move* mv1 = getMove(brd);
        Move* mv2 = getMove(brd);

        DoubleMove* db = new DoubleMove(mv1, mv2);
        return (dynamic_cast<GameMove*>(db));
    }

    Move* User::getMove(const Board* brd) 
    {
        int32_t pos_r, pos_c; 
        std::string str;
        fprintf(stderr, "\n Enter the move :\t");
        std::cin  >> str;
        Move *m;

        if(str[0] == 'r') {
            pos_r = str[3] - '1';
            pos_c = str[2] - 'a';
            
            if(str[1] == 'a')             
                m = new Move(pos_r, pos_c, brd, ROTATE_AC, brd->getTurn());
            else 
                m = new Move(pos_r, pos_c, brd, ROTATE_C, brd->getTurn());
        }

        else if(str[0] == 'f') {
            // get the fire position
             m = new Move(0, 0, brd, FIRE, brd->getTurn());
        }

        else {
            pos_c = str[0] - 'a';
            pos_r = str[1] - '1';

            int32_t newpos_c = str[2] - 'a';
            int32_t newpos_r = str[3] - '0';
            if(((newpos_r - pos_r) == 0) && ((newpos_c - pos_c) == 1))
                m = new Move(pos_r, pos_c, brd, MOVE_LEFT, brd->getTurn());

            else if(((newpos_r - pos_r) == 0) && ((newpos_c - pos_c) == -1))
                m = new Move(pos_r, pos_c, brd, MOVE_RIGHT, brd->getTurn());

            else if(((newpos_r - pos_r) == -1) && ((newpos_c - pos_c) == 0))
                m = new Move(pos_r, pos_c, brd, MOVE_DOWN, brd->getTurn());
            else
                m = new Move(pos_r, pos_c, brd, MOVE_UP, brd->getTurn());
        }
        return m;
    }
}
