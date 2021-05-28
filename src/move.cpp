#include "../include/move.h"


Move::Move(int row_, int col_, int lvl_) {
    row = row_;
    col = col_;
    lvl = lvl_;
}

string Move::toString() {
    return "Move by (" + to_string(row) + ", " + to_string(col) + ", " + to_string(lvl) + ") cells";
}
