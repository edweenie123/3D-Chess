#include "../include/rook.h"

char Rook::getId() {
    return 'r';
}

vector<Move> Rook::directions = {
    Move(1, 0, 0),
    Move(-1, 0, 0),
    Move(0, 1, 0),
    Move(0, -1, 0),
    Move(0, 0, 1),
    Move(0, 0, -1)
};

vector<Move> Rook::getMoves(Board board, bool prune) {
    // get all moves in line based of piece directions
    return getAllMovesInLine(directions, board, prune);
}
