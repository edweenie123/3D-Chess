#include "../include/move.h"

Move::Move() {
    row = col = lvl = 0;
}

Move::Move(int row_, int col_, int lvl_) {
    row = row_;
    col = col_;
    lvl = lvl_;
}

Move Move::operator+(const Move &delta){
    return Move(row + delta.row, col + delta.col, lvl + delta.lvl);
}

Move& Move::operator+=(const Move &delta){
    this->row += delta.row;
    this->col += delta.col;
    this->lvl += delta.lvl;
    return *this;
}

Move& Move::operator= (const Move &delta){
    row = delta.row;
    col = delta.col;
    lvl = delta.lvl;
    return *this;
}

string Move::toString() {
    return "Move by (" + to_string(row) + ", " + to_string(col) + ", " + to_string(lvl) + ") cells";
}
