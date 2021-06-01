#ifndef pawn_h
#define pawn_h

#include<vector>
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Pawn: public Piece {
    public:
        using Piece::Piece; // use constructor of parent class
        static vector<Move> captureDirections; // capture a piece while moving
        static vector<Move> passiveDirections; // move into a vacant cell
        vector<Move> getMoves(Board board);
        void Promote();
};

#endif