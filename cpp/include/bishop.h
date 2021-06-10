#ifndef bishop_h
#define bishop_h

#include<vector>
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Bishop: public Piece {
    public:
        char getId(); 
        using Piece::Piece; // use constructor of parent class
        static vector<Move> directions;
        vector<Move> getMoves(Board board, bool prune);
};

#endif