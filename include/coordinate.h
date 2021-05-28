#ifndef coordinate_h
#define coordinate_h

using namespace std;
#include<string>

struct Coordinate {
    private:
    public:
        int row, col, lvl;
        Coordinate();
        Coordinate(int row, int col, int lvl);
        string toString();
        // might add toChessNotation method
};

#endif