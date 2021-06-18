/* Bishop class, describing a bishop and its movements */

#ifndef bishop_h
#define bishop_h

#include "globals.h"
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Bishop: public Piece {
    public:
        char getId(); // returns ID identifying the piece
        using Piece::Piece; // use constructor of parent class
        static vector<Move> directions; // possible directions the piece can move in
        vector<Move> getMoves(Board board, bool prune); // returns all possible moves of the piece. if pruning is enabled, return all possible legal moves
};

#endif