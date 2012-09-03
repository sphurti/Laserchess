#include "Piece.h"
#include <assert.h>
#include <stdlib.h>

namespace laserchess {
    Piece::Piece(PieceType pt, Team t, Orientation o, PieceState ps,
            uint32_t r, uint32_t c) :
            ptype(pt),
            pteam(t)
    {
        ori = o;
        pState = ps;
        pos.row = r;
        pos.col = c;

        // initialize capabilities
        capture_enabled = false;
        armed = false;
        rotateable = true;
        switch(ptype) {
            case KING:
                rotateable = false;
                capture_enabled = true;
                break;
            case LASER:
                armed = true;
                break;
            case HYPERCUBE:
                rotateable = false;
                break;
            case BEAMSPLITTER:
                break;
            case BLOCK:
                capture_enabled = true;
                break;
            case MIRROR_DL:
            case MIRROR_ST:
            case MIRROR_TR:
            case HYPER_HOLE:
                break;
        }
    }

    // Returns true if the piece can reflect the beam
    bool Piece::can_reflect(Orientation beam_ori) const
    {
        switch(ptype) {
            case KING:
                return false;
            case LASER:
                return false;
            case HYPERCUBE:
                assert(false && "Can't be called on HYPERCUBE");
                break;
            case BEAMSPLITTER:
                if (ori == beam_ori)
                    return false;
                return true;
            case BLOCK:
                if (ori == opp_orient(beam_ori))
                    return true;
                return false;
            case MIRROR_DL:
                return true;
            case MIRROR_ST:
                return true;
            case MIRROR_TR:
                switch(ori) {
                    case NE:
                        if (beam_ori == N || beam_ori == E) return false;
                        return true;
                    case SE:
                        if (beam_ori == S || beam_ori == E) return false;
                        return true;
                    case NW:
                        if (beam_ori == N || beam_ori == W) return false;
                        return true;
                    case SW:
                        if (beam_ori == S || beam_ori == W) return false;
                        return true;
                    default:
                        assert(false && "MIRROR_TR orientation messed up");
                        break;
                }
            case HYPER_HOLE:
                assert(false && "Shouldn't be here");
        }
        return false;
    }

    void Piece::rotate_c()
    {
        switch(ori) {
            case V: ori = H; break;
            case H: ori = V; break;
            case F_SL: ori = B_SL; break;
            case B_SL: ori = F_SL; break;
            case N: ori = E; break;
            case E: ori = S; break;
            case S: ori = W; break;
            case W: ori = N; break;
            case NE: ori = SE; break;
            case SE: ori = SW; break;
            case SW: ori = NW; break;
            case NW: ori = NE; break;
            case NO_ORI: break;
        };
    }

    void Piece::rotate_ac()
    {
        switch(ori) {
            case V: ori = H; break;
            case H: ori = V; break;
            case F_SL: ori = B_SL; break;
            case B_SL: ori = F_SL; break;
            case N: ori = W; break;
            case W: ori = S; break;
            case S: ori = E; break;
            case E: ori = N; break;
            case NE: ori = NW; break;
            case NW: ori = SW; break;
            case SW: ori = SE; break;
            case SE: ori = NE; break;
            case NO_ORI: break;
        }
    }

    /*
        Given the direction of the laser beam, this method determines
        the list of reflections the beam can undergo when it hits the mirrored
        surfaces
    */
    void Piece::getReflectedOrientations(Orientation beam_ori, 
            std::list<Orientation>& ori_list)
    {
        switch (ptype) {
            /*  if the piece is beam splitter, split the beam if direction 
                of beam is opposite to the beamsplitter. Else the beam is
                reflected in the direction of the beamsplitter orientation
            */
            case BEAMSPLITTER:
                if (ori == opp_orient(beam_ori)) {
                    ori_list.push_back(adj_orient_ac(beam_ori));
                    ori_list.push_back(adj_orient_c(beam_ori));
                } else {
                    ori_list.push_back(ori);
                }
                break;
            // Block reflects the beam in the direction of its orientation
            case BLOCK:
                ori_list.push_back(ori);
                break;
            // Direction of reflection for diagonal mirror depends on
            // beam direction
            case MIRROR_DL:
                switch (ori) {
                    Orientation refl;
                    case F_SL:
                        switch(beam_ori) {
                            case N: refl = E; break;
                            case E: refl = N; break;
                            case S: refl = W; break;
                            case W: refl = S; break;
                            default: break;
                        }
                        ori_list.push_back(refl); break;
                    case B_SL:
                        switch(beam_ori) {
                            case N: refl = W; break;
                            case E: refl = S; break;
                            case S: refl = E; break;
                            case W: refl = N; break;
                            default: break;
                        }
                        ori_list.push_back(refl); break;
                    default:
                        assert(false && "MIRROR_DL orientation messed up");
                        break;
                }
            // Straight mirror relect the beam in the direction opposite to 
            // to the incident beam direction.
            case MIRROR_ST:
                ori_list.push_back(opp_orient(beam_ori)); break;
            case MIRROR_TR:
                switch(ori) {
                    Orientation refl;
                    case NE:
                        if (beam_ori == S)
                            refl = E;
                        else if (beam_ori == W)
                            refl = N;
                        ori_list.push_back(refl); break;
                    case SE:
                        if (beam_ori == N)
                            refl = E;
                        else if (beam_ori == W)
                            refl = S;
                        ori_list.push_back(refl); break;
                    case NW:
                        if (beam_ori == S)
                            refl = W;
                        else if (beam_ori == E)
                            refl = N;
                        ori_list.push_back(refl); break;
                    case SW:
                        if (beam_ori == N)
                            refl = W;
                        else if (beam_ori == E)
                            refl = S;
                        ori_list.push_back(refl); break;
                    default:
                        assert(false && "MIRROR_TR orientation messed up");
                        break;
                }
                break;
            default:
                assert(false && "Shouldn't be here");
        }
    }

    // Returns the opposite orientation vale for the given orientation
    Piece::Orientation Piece::opp_orient(Piece::Orientation o)
    {
        switch(o) {
            case V: assert(false);
            case H: assert(false);
            case N: return S;
            case W: return E;
            case S: return N;
            case E: return W;
            case NE: return SW;
            case NW: return SE;
            case SW: return NE;
            case SE: return NW;
            case NO_ORI: assert(false);
            default: return NO_ORI;
        }
    }

    /*
        Returns the 90 degree anti-clockwise beam direction for the passed 
        piece orientation value
    */
    Piece::Orientation Piece::adj_orient_ac(Piece::Orientation o)
    {
        switch(o) {
            case V: assert(false);
            case H: assert(false);
            case N: return W;
            case W: return S;
            case S: return E;
            case E: return N;
            case NE: return NW;
            case NW: return SW;
            case SW: return SE;
            case SE: return NE;
            case NO_ORI: assert(false);
            default: return NO_ORI;
        }
    }
    
    /* 
       Returns the 90 degree clockwise beam direction for the passed 
       piece orientation value
    */
    Piece::Orientation Piece::adj_orient_c(Piece::Orientation o)
    {
        switch(o) {
            case V: assert(false);
            case H: assert(false);
            case N: return E;
            case E: return S;
            case S: return W;
            case W: return N;
            case NE: return SE;
            case SE: return SW;
            case SW: return NW;
            case NW: return NE;
            case NO_ORI: assert(false);
            default: return NO_ORI;
        }
    }

    /*  
        Teleport a piece to random location. If the piece is rotatable,
        rotate the piece in random direction
    */
    void Piece::teleportRandom()
    {
        pos.row = rand() % 9;
        pos.col = rand() % 9;
        int num_rot = rand() % 4;
        if (can_rotate())
            do { rotate_c(); } while (num_rot-- > 0); 
    }

    /*
        This function is used to display the piece on the board.
        The unicode geometric symbols have been used to represent 
        the pieces
    */        
    void Piece::display()
    {
        setlocale(LC_CTYPE,"");
        wchar_t pstr;
        switch(ptype) {
            case KING :
                if (pteam == WHITE) 
                    pstr = 9813;         
                else
                    pstr = 9819;
                break;
            case HYPERCUBE :
                if (pteam == WHITE)
                    pstr = 9750;
                else
                    pstr = 9751;
                break;
            case BLOCK :
                if (pteam == WHITE)
                    pstr = 9723;
                else
                    pstr = 9724;
                break;
            case HYPER_HOLE :
                pstr = 9635;
                break;
            case MIRROR_DL : 
                if (pteam == WHITE) {
                    if (ori == F_SL)
                        pstr = 118788;
                    else
                        pstr = 118790;
                } else {
                    if (ori == F_SL)
                        pstr = 118787;
                    else
                        pstr = 118789;
                }
                break;
            case MIRROR_ST: 
                if (pteam == WHITE) {
                    if (ori == V)
                        pstr = 9647;
                    else
                        pstr = 9645;
                } else {
                    if (ori == V)
                        pstr = 9646;
                    else
                        pstr = 9644;
                }
                break;
            case MIRROR_TR : 
                if (pteam == WHITE) {
                    if (ori == NE) 
                        pstr = 9722;
                    else if(ori == NW)
                        pstr = 9727;
                    else if(ori == SE)
                        pstr = 9720;
                    else
                        pstr = 9721;
                } else {
                    if (ori == NE) 
                        pstr = 9699;
                    else if(ori == NW)
                        pstr = 9698;
                    else if(ori == SE)
                        pstr = 9700;
                    else
                        pstr = 9701;
                }
                break;
            case BEAMSPLITTER : 
                if (pteam == WHITE) {
                    if (ori == N) 
                        pstr = 9651;
                    else if(ori == E)
                        pstr = 9659;
                    else if(ori == S)
                        pstr = 9661;
                    else
                        pstr = 9669;
                } else {
                    if (ori == N) 
                        pstr = 9650;
                    else if(ori == E)
                        pstr = 9658;
                    else if(ori == S)
                        pstr = 9660;
                    else
                        pstr = 9668;
                }
                break;
            case LASER : 
                if (pteam == WHITE) {
                    if (ori == N) 
                        pstr = 10595;
                    else if(ori == E)
                        pstr = 10594;
                    else if(ori == S)
                        pstr = 10597;
                    else
                        pstr = 10596;
                } else {
                    if (ori == N)
                        pstr = 10592;
                    else if(ori == E)
                        pstr = 10590;
                    else if(ori == S)
                        pstr = 10589;
                    else
                        pstr = 10587;
                }
                break;
            default : break;
        }
        std::wcout << pstr;
        std::wcout << "\t";
    }        

    float Piece::score() const
    {
        switch (ptype) {
            case KING:
                return 10000;
            case LASER:
                return 1000;
            case HYPERCUBE:
                return 500;
            case BEAMSPLITTER:
            case BLOCK:
            case MIRROR_DL:
            case MIRROR_ST:
            case MIRROR_TR:
                return 200;
            default:
                return 0;
        }
    }
}
