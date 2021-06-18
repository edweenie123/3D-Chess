#ifndef empty_h
#define empty_h

#include "globals.h"
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Empty: public Piece {
    public:
        char getId(); 
        using Piece::Piece; // use constructor of parent class
        vector<Move> getMoves(Board board, bool prune);
};

#endif