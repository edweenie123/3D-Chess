#ifndef queen_h
#define queen_h

#include<vector>
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Queen: public Piece {
    public:
        static const char id = 'q';
        using Piece::Piece; // use constructor of parent class
        // static vector<Move> directions;
        vector<Move> getMoves(Board board);
};

#endif