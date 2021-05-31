#include "../include/move.h"


Move::Move(int row_, int col_, int lvl_) {
    row = row_;
    col = col_;
    lvl = lvl_;
}

Move Move::operator+(const Move& move) {
    int nrow = move.row + row;
    int ncol = move.col + col;
    int nlvl = move.lvl + lvl;

    return Move(nrow, ncol, nlvl);
}

string Move::toString() {
    return "Move by (" + to_string(row) + ", " + to_string(col) + ", " + to_string(lvl) + ") cells";
}
