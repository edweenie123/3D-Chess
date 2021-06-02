#ifndef pawn_h
#define pawn_h

#include<vector>
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Pawn: public Piece {
    public:
        static const char id = 'p';
        using Piece::Piece; // use constructor of parent class
        vector<Move> getMoves(Board board);
        void Promote();
};

#endif