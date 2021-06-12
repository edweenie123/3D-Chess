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

vector<Move> Piece::pruneMoves(vector<Move> moves, Board board, Coordinate cord) {
    int row = cord.row;
    int col = cord.col;
    int lvl = cord.lvl;
    // Prune out all the moves that are illegal (places its king in check)
    for (int i = int(moves.size()) - 1; i >= 0; --i) {
		bool illegalMove = false;
        Move m = moves[i];

        // Try simulating this move
        Piece* oldPiece = board.getPieceAt({row + m.row, col + m.col, lvl + m.lvl});
        board.updateLocation({row, col, lvl}, m);
        if (board.isChecked(color)) {
            // prune this move
            illegalMove = true;
        }
        // Undo the simulated move
        board.updateLocation({row + m.row, col + m.col, lvl + m.lvl}, {-m.row, -m.col, -m.lvl});
        if (oldPiece->getId() != ' ') {
            board.board[row + m.row][col + m.col][lvl + m.lvl] = oldPiece;
            oldPiece->isAlive = true;
        }
        if (illegalMove) {
            moves.erase(moves.begin() + i);
        }
    }
    return moves;
}

vector<Move> Piece::getMoves(Board board, bool prune) {
    // return an empty vector for v table to be happy
    vector<Move> tmp;
    return tmp;
}

vector<Move> Piece::getAllMovesInLine(vector<Move> directions, Board board, bool prune) {
    vector<Move> moves;

    int row = location.row;
    int col = location.col;
    int lvl = location.lvl;

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
    if (prune) {
        // Prune out all the moves that are illegal (places its king in check)
        return pruneMoves(moves, board, location);
    }
    return moves;
}


// string Piece::toString() {
//     // return "isAlive = " + isAlive + " location = ";
// }
