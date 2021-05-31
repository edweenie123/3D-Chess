#ifndef coordinate_h
#define coordinate_h

using namespace std;
#include "move.h"
#include<string>

struct Coordinate {
    private:
    public:
        int row, col, lvl;
        Coordinate();
        Coordinate(Coordinate cur, Move delta);
        Coordinate(int row, int col, int lvl);
        string toString();
        // might add toChessNotation method
};

#endif