#include "../include/coordinate.h"

Coordinate::Coordinate() {
    row = col = lvl = 0;
}

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

Coordinate Coordinate::operator+(const Move &delta){
    return Coordinate(row + delta.row, col + delta.col, lvl + delta.lvl);
}

Coordinate& Coordinate::operator+=(const Move &delta){
    this->row += delta.row;
    this->col += delta.col;
    this->lvl += delta.lvl;
    return *this;
}

Coordinate& Coordinate::operator= (const Coordinate &coord){
    row = coord.row;
    col = coord.col;
    lvl = coord.lvl;
    return *this;
}

string Coordinate::toString() {
    return "(" + to_string(row) + ", " + to_string(col) + ", " + to_string(lvl) + ")";
}

