#include "../include/coordinate.h"
#include "../include/piece.h"
#include "../include/board.h"

Piece::Piece() {
    location = Coordinate{0, 0, 0};
    color = 0;
}

Piece::Piece(int row_, int col_, int lvl_, int color_) {
    location = Coordinate{row_, col_, lvl_};
    color = color_;
}

int Piece::getColor() {
    return color;
}

char Piece::getId() {
    return ' ';
}

Coordinate Piece::getLocation() {
    return location;
}

// bool Piece::isEnemySquare(Piece other) {
//     // make sure pieces have valid colors
//     assert((color == BLACK || color == WHITE) && (other.color == BLACK || other.color == WHITE))

//     return color != other.color;
// }

void Piece::setLocation(int row_, int col_, int lvl_) {
    location = Coordinate{row_, col_, lvl_};
}

vector<Move> Piece::getMoves(Board board) {
    // return an empty vector for v table to be happy
    vector<Move> tmp;
    return tmp;
}

vector<Move> Piece::getAllMovesInLine(vector<Move> directions, Board board) {
    vector<Move> moves;

    // find all legal moves in "line" with directions
    // used for queen, rook, bishop and unicorn getMoves() method

    for (auto dir : directions) {
        Coordinate cur = Coordinate(location.row, location.col, location.lvl);
        Move curDelta = Move(dir.row, dir.col, dir.lvl);

        while (true) {
            // move the coordinate by the direction vector
            cur = Coordinate(cur, dir);
            if (!board.isOnBoard(cur)) break;
            if (!board.isVacant(cur)) {
                // only add the move if the piece at cur is of OPPOSITE color
                if (board.getPieceAt(cur)->color != color)
                    moves.push_back(curDelta);

                // exit the while loop as there is a piece blocking the piece's way
                break;
            }
            // coordinate at cur is empty therefore, the piece can move there
            moves.push_back(curDelta);

            // increase the delta by the direction vector
            curDelta = curDelta + dir;
        }
    }

    return moves;
}


// string Piece::toString() {
//     // return "isAlive = " + isAlive + " location = ";
// }