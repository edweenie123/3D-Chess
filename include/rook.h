#ifndef rook_h
#define rook_h

#include<vector>
#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "board.h"

class Rook: public Piece {
    public:
        Rook(int col_, int row_, int lvl_, int color_);
        vector<Move> getMoves();
};


#endif