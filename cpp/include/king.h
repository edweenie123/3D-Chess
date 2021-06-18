/* King class, describing a king and its movements */

#ifndef king_h
#define king_h

#include "globals.h"
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class King: public Piece {
    public:
        char getId(); 
        using Piece::Piece; // use constructor of parent class
        // static vector<Move> directions;
        vector<Move> getMoves(Board board, bool prune);
};

#endif