/* Pawn class, describing a pawn and its movements, in addition to promotion */

#ifndef pawn_h
#define pawn_h

#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"
#include "globals.h"

class Pawn: public Piece {
    public:
        char getId(); // returns ID identifying the piece
        using Piece::Piece; // use constructor of parent class
        vector<Move> getMoves(Board board, bool prune); // returns all possible moves of the piece. if pruning is enabled, return all possible legal moves
        void promote(Board& board, Piece* promotedPiece, bool deletePiece); // handles pawn promotion
};

#endif
