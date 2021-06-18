/* Unicorn class, describing a unicorn and its movements */

#ifndef unicorn_h
#define unicorn_h

#include "globals.h"
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Unicorn: public Piece {
    public:
        char getId(); 
        using Piece::Piece; // use constructor of parent class
        static vector<Move> directions;
        vector<Move> getMoves(Board board, bool prune);
};

#endif