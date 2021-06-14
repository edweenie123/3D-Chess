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
    // Prune out all the moves that are illegal (places its king in check)
    for (int i = int(moves.size()) - 1; i >= 0; --i) {
        Move m = moves[i];
        // Try simulating this move
        Piece* oldPiece = board.board[cord.row + m.row][cord.col + m.col][cord.lvl + m.lvl];
        board.updateLocation(cord, m);
        // prune move if checked
        bool illegalMove = board.isChecked(color);
        // Undo the simulated move
        board.updateLocation(cord + m, -m);
        if (oldPiece->getId() != ' ') {
            board.board[cord.row + m.row][cord.col + m.col][cord.lvl + m.lvl] = oldPiece;
            oldPiece->isAlive = true;
        }
        if (illegalMove) {
            swap(moves[i], moves.back());
            moves.pop_back();
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

    // find all legal moves in "line" with directions
    // used for queen, rook, bishop and unicorn getMoves() method

    for (auto dir : directions) {
        Coordinate cur = location;
        Move curDelta = dir;
        while (true) {
            // move the coordinate by the direction vector
            cur += dir;
            if(!board.isOnBoard(cur)) break;
            else if (!board.isVacant(cur)) {
                // only add the move if the piece at cur is of OPPOSITE color
                if (board.board[cur.row][cur.col][cur.lvl]->color != color)
                    moves.push_back(curDelta);

                // exit the while loop as there is a piece blocking the piece's way
                break;
            }
            // coordinate at cur is empty therefore, the piece can move there
            moves.push_back(curDelta);
            // increase the delta by the direction vector
            curDelta += dir;
        }

    }
    if (prune) {
        // Prune out all the moves that are illegal (places its king in check)
        return pruneMoves(moves, board, location);
    }
    return moves;
}

bool Piece::hasAnyMoves(Board board, Coordinate cord){
    // Prune out all the moves that are illegal (places its king in check)
    for (auto m : getMoves(board, false)) {
        // Try simulating this move
        Piece* oldPiece = board.board[cord.row + m.row][cord.col + m.col][cord.lvl + m.lvl];
        board.updateLocation(cord, m);
        // prune move if checked
        bool illegalMove = board.isChecked(color);
        // Undo the simulated move
        board.updateLocation(cord + m, -m);
        if (oldPiece->getId() != ' ') {
            board.board[cord.row + m.row][cord.col + m.col][cord.lvl + m.lvl] = oldPiece;
            oldPiece->isAlive = true;
        }
        if(!illegalMove) return true;
    }
    return false;
}
