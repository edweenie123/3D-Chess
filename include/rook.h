#ifndef rook_h
#define rook_h

#include<vector>
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Rook: public Piece {
    public:
        using Piece::Piece;
        vector<Move> getMoves(Board board);
};


#endif