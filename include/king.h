#ifndef king_h
#define king_h

#include<vector>
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class King: public Piece {
    public:
        using Piece::Piece; // use constructor of parent class
        // static vector<Move> directions;
        vector<Move> getMoves(Board board);
};

#endif