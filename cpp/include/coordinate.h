/* Coordinate class, describing a 3D chess coordinate, including handy methods for 3D coordinate arithmetic */

#ifndef coordinate_h
#define coordinate_h

#include "globals.h"
#include "move.h"

class Coordinate {
    private:
    public:
        // Stores row, col, and lvl into one Coordinate object
        int row, col, lvl;

        // Constructors
        Coordinate();
        Coordinate(Coordinate cur, Move delta);
        Coordinate(int row, int col, int lvl);

        string toString();

        // Operator overloads for easy Coordinate arithmetic
        Coordinate operator+(const Move&);
        Coordinate& operator+=(const Move&);
        Coordinate& operator=(const Coordinate&);
};

#endif
