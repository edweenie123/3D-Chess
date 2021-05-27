#include<../include/piece.h>


Piece::Piece(int row_, int col_, int lvl_, int color_) {
    location = Coordinate{row_, col_, lvl_};
    color = color_;
}

int Piece::getColor() {
    return color;
}

Coordinate Piece::getLocation() {
    return location;
}

void Piece::setLocation(int row_, int col_, int lvl_) {
    location = Coordinate{row_, col_, lvl_};
}

// string Piece::toString() {
//     // return "isAlive = " + isAlive + " location = ";
// }
