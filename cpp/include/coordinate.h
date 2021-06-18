/* Coordinate class, describing a 3D chess coordinate, including handy methods for 3D coordinate arithmetic */

#ifndef coordinate_h
#define coordinate_h

#include "globals.h"
#include "move.h"

class Coordinate {
    private:
    public:
        int row, col, lvl;
        Coordinate();
        Coordinate(Coordinate cur, Move delta);
        Coordinate(int row, int col, int lvl);
        string toString();
        Coordinate operator+(const Move&);
        Coordinate& operator+=(const Move&);
        Coordinate& operator=(const Coordinate&);
};

#endif
