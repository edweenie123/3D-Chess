#ifndef coordinate_h
#define coordinate_h

#include<string>
#include "move.h"
using namespace std;

struct Coordinate {
    private:
    public:
        int row, col, lvl;
        Coordinate();
        Coordinate(Coordinate cur, Move delta);
        Coordinate(int row, int col, int lvl);
        string toString();
        Coordinate operator+(const Move&);
        Coordinate& operator+=(const Move&);
        // might add toChessNotation method
};

#endif
