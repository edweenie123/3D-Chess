#include "../include/coordinate.h"


Coordinate::Coordinate(int row_, int col_, int lvl_) {
    row = row_;
    col = col_;
    lvl = lvl_;
}

string Coordinate::toString() {
    return "(" + to_string(row) + ", " + to_string(col) + ", " + to_string(lvl) + ")";
}

