#include "../include/coordinate.h"


Coordinate::Coordinate(int row_, int col_, int lvl_) {
    row = row_;
    col = col_;
    lvl = lvl_;
}

Coordinate::Coordinate(Coordinate cur, Move delta) {
    // creates the coordinate object after moving with delta

    row = cur.row + delta.row;
    col = cur.col + delta.col;
    lvl = cur.lvl + delta.lvl;
}

string Coordinate::toString() {
    return "(" + to_string(row) + ", " + to_string(col) + ", " + to_string(lvl) + ")";
}

