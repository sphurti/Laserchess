#include "Board.h"

namespace laserchess {
    /* constructor to initialize the row and
       column values. The piece objects are created 
       and initialized to NULL
    */
    Board::Board() :
            numRow(9),
            numCol(9)
    {
        // allocate memory for piece array
        piece_array = new Piece**[numRow];
        for (uint32_t i=0; i<rows(); i++) {
            piece_array[i] = new Piece*[numCol];
            for (uint32_t j=0; j<cols(); j++)
                piece_array[i][j] = NULL;
        }
        // initialize board
        init();
    }

    /* This constructor helps to initialize the new Board object 
       with the existing Board values
    */
    Board::Board(const Board& brd) :
            numRow(brd.rows()),
            numCol(brd.cols())
    {
        // allocate memory and copy piece array
        piece_array = new Piece**[numRow];
        for (uint32_t i=0; i<rows(); i++) {
            piece_array[i] = new Piece*[numCol];
            for (uint32_t j=0; j<cols(); j++)
                piece_array[i][j] = NULL;
        }

        // copy pieces
        for (uint32_t i=0; i<brd.white_p.size(); i++) {
            Piece* newp = new Piece(*(brd.white_p[i]));
            white_p.push_back(newp);
            piece_array[newp->pos.row][newp->pos.col] = newp;
        }
        for (uint32_t i=0; i<brd.black_p.size(); i++) {
            Piece* newp = new Piece(*(brd.black_p[i]));
            black_p.push_back(newp);
            piece_array[newp->pos.row][newp->pos.col] = newp;
        }
        Piece* newp = new Piece(*(brd.hyperhole));
        hyperhole = newp;
        piece_array[4][4] = hyperhole;

        turn = brd.turn;
    }

    Team Board::getTurn() const
    {
        return turn;
    }

    // Set the turn of the team for the current Board
    void Board::setTurn(Team t)
    {
        turn = t;
    }

    /* Initialize the board. All the pieces are placed in their
       initial position on board and the teams array are populated 
       with the pieces belonging to the team
    */
    void Board::init()
    {
        Piece* ps;
        ps = new Piece(Piece::MIRROR_TR, WHITE, Piece::NE, ACTIVE, 0, 0);
        piece_array[0][0] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, WHITE, Piece::NE, ACTIVE, 0, 1);
        piece_array[0][1] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_DL, WHITE, Piece::F_SL, ACTIVE, 0, 2);
        piece_array[0][2] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::LASER, WHITE, Piece::N, ACTIVE, 0, 3);
        piece_array[0][3] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::KING, WHITE, Piece::NO_ORI, ACTIVE, 0, 4);
        piece_array[0][4] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::HYPERCUBE, WHITE, Piece::NO_ORI, ACTIVE, 0, 5);
        piece_array[0][5] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_DL, WHITE, Piece::B_SL, ACTIVE, 0, 6);
        piece_array[0][6] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, WHITE, Piece::NW, ACTIVE, 0, 7);
        piece_array[0][7] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, WHITE, Piece::NW, ACTIVE, 0, 8);
        piece_array[0][8] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, WHITE, Piece::NW, ACTIVE, 1, 0);
        piece_array[1][0] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::BLOCK, WHITE, Piece::N, ACTIVE, 1, 1);
        piece_array[1][1] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::BLOCK, WHITE, Piece::N, ACTIVE, 1, 2);
        piece_array[1][2] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::BEAMSPLITTER, WHITE, Piece::S, ACTIVE, 1, 3);
        piece_array[1][3] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_ST, WHITE, Piece::H, ACTIVE, 1, 4);
        piece_array[1][4] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_ST, WHITE, Piece::V, ACTIVE, 1, 5);
        piece_array[1][5] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::BLOCK, WHITE, Piece::N, ACTIVE, 1, 6);
        piece_array[1][6] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::BLOCK, WHITE, Piece::N, ACTIVE, 1, 7);
        piece_array[1][7] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, WHITE, Piece::NE, ACTIVE, 1, 8);
        piece_array[1][8] = ps;
        white_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, BLACK, Piece::SE, ACTIVE, 8, 0);
        piece_array[8][0] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, BLACK, Piece::SE, ACTIVE, 8, 1);
        piece_array[8][1] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_DL, BLACK, Piece::B_SL, ACTIVE, 8, 2);
        piece_array[8][2] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::HYPERCUBE, BLACK, Piece::NO_ORI, ACTIVE, 8, 3);
        piece_array[8][3] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::KING, BLACK, Piece::NO_ORI, ACTIVE, 8, 4);
        piece_array[8][4] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::LASER, BLACK, Piece::S, ACTIVE, 8, 5);
        piece_array[8][5] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_DL, BLACK, Piece::F_SL, ACTIVE, 8, 6);
        piece_array[8][6] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, BLACK, Piece::SW, ACTIVE, 8, 7);
        piece_array[8][7] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, BLACK, Piece::SW, ACTIVE, 8, 8);
        piece_array[8][8] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, BLACK, Piece::SW, ACTIVE, 7, 0);
        piece_array[7][0] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::BLOCK, BLACK, Piece::S, ACTIVE, 7, 1);
        piece_array[7][1] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::BLOCK, BLACK, Piece::N, ACTIVE, 7, 2);
        piece_array[7][2] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_ST, BLACK, Piece::V, ACTIVE, 7, 3);
        piece_array[7][3] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_ST, BLACK, Piece::H, ACTIVE, 7, 4);
        piece_array[7][4] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::BEAMSPLITTER, BLACK, Piece::N, ACTIVE, 7, 5);
        piece_array[7][5] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::BLOCK, BLACK, Piece::S, ACTIVE, 7, 6);
        piece_array[7][6] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::BLOCK, BLACK, Piece::S, ACTIVE, 7, 7);
        piece_array[7][7] = ps;
        black_p.push_back(ps);

        ps = new Piece(Piece::MIRROR_TR, BLACK, Piece::SE, ACTIVE, 7, 8);
        piece_array[7][8] = ps;
        black_p.push_back(ps);

        //hyperhole does not belong to any team
        ps = new Piece(Piece::HYPER_HOLE, NO_TEAM, Piece::NO_ORI, ACTIVE, 4, 4);
        piece_array[4][4] = ps;
        hyperhole = ps;
    }

    float Board::evaluate() const
    {
        float score;
        // assign scores to pieces
        for (uint32_t i=0; i<white_p.size(); i++) {
            score += white_p[i]->score();
        }
        for (uint32_t i=0; i<black_p.size(); i++) {
            score -= black_p[i]->score();
        }

        // King must not be exposed
        // Laser should have room to fire

        return score;
    }

    void Board::applyMove(Move* m)
    {
        if (m->isMove()) { /* Move moves */
            int32_t dst_r, dst_c;
	    // get the destination row and column value for given move 
            m->getPieceDestination(dst_r, dst_c);
            // get the current piece at the move source point 
            Piece* p = piece_array[m->piece_r][m->piece_c];

            // dst is occupied by another piece of either colour
            if (piece_array[dst_r][dst_c] != NULL) {
                Piece* dst_p = piece_array[dst_r][dst_c];
                // dst is hyperhole
                if (dst_p->ptype == Piece::HYPER_HOLE) {
                    if (!m->tport_info) {
                        do { // find a random unoccupied position
                            p->teleportRandom();
                        } while (piece_array[p->pos.row][p->pos.col] != NULL);
                        // store teleport info
                        m->tport_info = new Move::TeleportInfo(p->pos.row,
                                p->pos.col, p->ori);
                    } else {
                        Move::TeleportInfo* t = m->tport_info;
                        p->pos.row = t->row;
                        p->pos.col = t->col;
                        p->ori = t->ori;
                    }
                    // update p info
                    piece_array[p->pos.row][p->pos.col] = p;
                    piece_array[m->piece_r][m->piece_c] = NULL;
                    return; 
                } else if (p->ptype == Piece::HYPERCUBE) { // piece is hypercube
                    if (!m->tport_info) {
                        do { // find a random unoccupied position
                            dst_p->teleportRandom();
                        } while (piece_array[dst_p->pos.row][dst_p->pos.col]
                                != NULL);
                        m->tport_info = new Move::TeleportInfo(dst_p->pos.row,
                                dst_p->pos.col, dst_p->ori);
//                        fprintf(stderr, "Stored for %p\n", m);
//                        m->printMove();
                    } else {
//                        fprintf(stderr, "getting %p\n", m);
//                        m->printMove();
                        Move::TeleportInfo* t = m->tport_info;
                        dst_p->pos.row = t->row;
                        dst_p->pos.col = t->col;
                        dst_p->ori = t->ori;
                    }
                    // update dst_p info
                    piece_array[dst_p->pos.row][dst_p->pos.col] = dst_p;
                } else { // we capture piece
                    deletePiece(dst_p);
                }
            }
            // move piece into position and set original to NULL
            piece_array[dst_r][dst_c] = p;
            piece_array[m->piece_r][m->piece_c] = NULL;

            // update piece_position
            p->pos.row = dst_r;
            p->pos.col = dst_c;
        } else if (m->isFire()) { /* Fire moves */
            Piece* p = piece_array[m->piece_r][m->piece_c];
            handleFireMove(m->piece_r, m->piece_c, p->ori);
        } else if (m->isRotate()) { /* Rotate moves */
            Piece* p = piece_array[m->piece_r][m->piece_c];
            switch (m->m_typ) {
                case ROTATE_C:
                    p->rotate_c(); break;
                case ROTATE_AC:
                    p->rotate_ac(); break;
                default:
                    assert(false && "Shouldn't be here");
            }
        }
    }

    void Board::applyMove(const DoubleMove* d)
    {
//        fprintf(stderr, "F: "); d->first()->printMove();
        applyMove(d->first());
//        fprintf(stderr, "S: "); d->second()->printMove();
        applyMove(d->second());
    }
   
    void Board::getValidNextMoves(std::list<Move*>& moves) const
    {
        for (uint32_t i=0; i<my_pieces().size(); i++) {
            Piece* p = my_pieces()[i];
            // moving actions
            assert(p);
            for (MoveType i = MOVE_LEFT; i <= MOVE_DOWN;
                    i=static_cast<MoveType>(i+1)) {
                Move* m = new Move(p->pos.row, p->pos.col, this, i, turn);
                if (valid(*m))
                    moves.push_back(m);
                else
                    delete m;
            }

            // rotating actions
            if (p->can_rotate()) {
                Move* m = new Move(p->pos.row, p->pos.col, this, ROTATE_C,
                        turn);
                moves.push_back(m);
                m = new Move(p->pos.row, p->pos.col, this, ROTATE_AC, turn);
                moves.push_back(m);
            }

            // firing actions
            if (p->can_fire()) {
                Move* m = new Move(p->pos.row, p->pos.col, this, FIRE, turn);
                moves.push_back(m);
            }
        }
        std::list<Move>::iterator mit;
//        fprintf(stderr, "Valid moves\n");
//        for (mit=moves.begin(); mit != moves.end(); mit++)
//            mit->printMove();
    }

    bool Board::valid(const Move& mv) const
    {
        // get piece
        Piece* p = piece_array[mv.piece_r][mv.piece_c];
        if (!p) {
//            fprintf(stderr, "No piece at position\n");
            return false;
        }

        // no touching hyperhole
        if (p->ptype == Piece::HYPER_HOLE) {
//            fprintf(stderr, "Can't do anything with hyperhole\n");
            return false;
        }
//        mv.printMove();


        // Checking all illegal moves involving moving pieces
        if (mv.isMove()) {
            int32_t dst_r, dst_c;
            mv.getPieceDestination(dst_r, dst_c);

            // check if destination is out of bounds
            if (!checkPositionValid(dst_r, dst_c)) {
//                fprintf(stderr, "Out of bounds\n");
                return false;
            }
            // check if destination has another piece
            Piece* dst_piece = piece_array[dst_r][dst_c];
            if (dst_piece) {
                // check if it is our own piece
                /* ASSERT: moving a piece to another square occupied by our own
                 * piece is illegal except when we move a hypercube */
                if (dst_piece->pteam == p->pteam) {
                    if (p->ptype != Piece::HYPERCUBE) {
//                        fprintf(stderr, "Can't capture own piece\n");
                        return false;
                    }
                } else { // else check if piece has capture capabilities
                    if (!p->can_capture()) {
//                        fprintf(stderr, "Can't capture\n");
                        return false;
                    }
                }
            }
        }

        // Checking for illegal fire moves. TODO
        if (mv.isFire() && !p->can_fire()) {
//            fprintf(stderr, "Can't fire\n");
            return false;
        }

        // Checking for illegal rotate moves. TODO
        if (mv.isRotate() && !p->can_rotate()) {
//            fprintf(stderr, "Can't rotate\n");
            return false;
        }
        return true;
    }

    bool Board::valid(const DoubleMove& dmv) const
    {
        //TODO: hypercube can teleport once per turn
        //TODO: king can capture once per turn
        //TODO: block can capture once per turn
        return true;
    }

    bool Board::checkPositionValid(uint32_t dst_r, uint32_t dst_c) const
    {
        if (dst_r >= rows() || dst_r < 0)
            return false;
        if (dst_c >= cols() || dst_c < 0)
            return false;
        return true;
    }

    std::vector<Piece*>& Board::my_pieces() const
    {
        if (turn == WHITE)
            return const_cast<std::vector<Piece*>&>(white_p);
        else
            return const_cast<std::vector<Piece*>&>(black_p);
    }

    std::vector<Piece*>& Board::opp_pieces() const
    {
        if (turn == WHITE)
            return const_cast<std::vector<Piece*>&>(black_p);
        else
            return const_cast<std::vector<Piece*>&>(white_p);
    }

   /* Depending on the team to which the piece belongs,
   delete the piece from that array */
    void Board::deletePiece(Piece*& p)
    {
        std::vector<Piece*>* pieces_ptr;

        if (p->pteam == WHITE) {
            pieces_ptr = &white_p;
        } else if (p->pteam == BLACK) {
            pieces_ptr = &black_p;
        } else
            assert(false);
        for (uint32_t i=0; i<pieces_ptr->size(); i++) {
            if ((*pieces_ptr)[i] == p) {
                pieces_ptr->erase(pieces_ptr->begin() + i);
                piece_array[p->pos.row][p->pos.col] = NULL;
                delete p;
                p = NULL;
            }
        }
    }
   
    /*  
        This method handles the move of fire type.
        depending on the direction of the beam, either 
        a piece is captured or the beam is reflected untill
        it moves off the board
    */ 
    void Board::handleFireMove(uint32_t orig_r, uint32_t orig_c,
            Piece::Orientation beam_ori, uint32_t depth)
    {
        if (depth > 20)
            return;
        Piece* first_hit = findFirstPieceHit(orig_r, orig_c, beam_ori);
        // check if laser hits a piece
        if (first_hit) {
            if (first_hit->ptype == Piece::HYPER_HOLE)
                return;
            else if (!first_hit->can_reflect(beam_ori))
                deletePiece(first_hit);
            else {
                // generate reflected beam
                std::list<Piece::Orientation> ori_list;
                first_hit->getReflectedOrientations(beam_ori, ori_list);
                std::list<Piece::Orientation>::iterator or_it;
                for (or_it=ori_list.begin(); or_it != ori_list.end();
                        or_it++) {
                    handleFireMove(first_hit->pos.row, first_hit->pos.col,
                            *or_it, depth+1);
                }
            }
        }
    }

    /*  This method is used to determine the first piece that is hit by the
        the laser beam.
    */
    Piece* Board::findFirstPieceHit(uint32_t orig_r, uint32_t orig_c,
            Piece::Orientation beam_ori) const
    {
        // this does not include the HYPERCUBE
        int32_t r_incr, c_incr;
        // Laser can't point to diagonals
        switch (beam_ori) {
            case Piece::N:
                r_incr = 1;
                c_incr = 0;
                break;
            case Piece::E:
                r_incr = 0;
                c_incr = 1;
                break;
            case Piece::W:
                r_incr = 0;
                c_incr = -1;
                break;
            case Piece::S:
                r_incr = -1;
                c_incr = 0;
                break;
            default:
                assert(false && "Laser can't point to diagonal dirs.");
        }
        int32_t r = orig_r + r_incr, c = orig_c + c_incr;
        while (checkPositionValid(r, c)) {
            if (piece_array[r][c] != NULL) {
                if (piece_array[r][c]->ptype == Piece::HYPERCUBE)
                    goto next_sq;
                Piece* p = piece_array[r][c];
                if (p->ptype == Piece::MIRROR_ST &&
                        (p->ori == Piece::V && beam_ori == Piece::N) ||
                        (p->ori == Piece::V && beam_ori == Piece::S) ||
                        (p->ori == Piece::H && beam_ori == Piece::E) ||
                        (p->ori == Piece::H && beam_ori == Piece::W))
                    goto next_sq;
                return piece_array[r][c];
            }
next_sq:
            r += r_incr;
            c += c_incr;
        }
        return NULL;
    }
    
    // Display the board
    void Board::display()
    {
        for(int32_t i=(int32_t)numRow-1; i>=0; i--) {
            for(int32_t j=0; j<(int32_t)numCol; j++) {
                if (piece_array[i][j] == NULL)
                    std::wcout << "_" << "\t" ;
                else {
                    Piece* p = piece_array[i][j];
                    p->display();
                }
                
            }
            std::wcout << std::endl;
        }
    }
}           
