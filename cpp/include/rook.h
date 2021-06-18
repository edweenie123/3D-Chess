/* Rook class, describing a rook and its movements */

#ifndef rook_h
#define rook_h

#include "globals.h"
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Rook: public Piece {
    public:
        char getId(); 
        using Piece::Piece; // use constructor of parent class
        static vector<Move> directions;
        vector<Move> getMoves(Board board, bool prune);
};

#endif
