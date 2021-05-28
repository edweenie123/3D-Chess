#ifndef rook_h
#define rook_h

#include "piece.h"
#include<vector>
#include "coordinate.h"

class Rook: public Piece {
    public:
        Rook(int col_, int row_, int lvl_, int color_);
        vector<Coordinate> getMoves();
};


#endif