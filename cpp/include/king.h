/* King class, describing a king and its movements */

#ifndef king_h
#define king_h

#include "globals.h"
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class King: public Piece {
    public:
        char getId(); // returns ID identifying the piece
        using Piece::Piece; // use constructor of parent class
        vector<Move> getMoves(Board board, bool prune); // returns all possible moves of the piece. if pruning is enabled, return all possible legal moves
};

#endif