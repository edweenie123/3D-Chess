#ifndef pawn_h
#define pawn_h

#include<vector>
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"
#include "globals.h"

class Pawn: public Piece {
    public:
        char getId(); 
        using Piece::Piece; // use constructor of parent class
        vector<Move> getMoves(Board board, bool prune);
        void promote(Board& board, Piece* promotedPiece);
};

#endif