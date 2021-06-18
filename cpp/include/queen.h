/* Queen class, describing a queen and its movements */

#ifndef queen_h
#define queen_h

#include "globals.h"
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Queen: public Piece {
    public:
        char getId(); 
        using Piece::Piece; // use constructor of parent class
        // static vector<Move> directions;
        vector<Move> getMoves(Board board, bool prune);
};

#endif