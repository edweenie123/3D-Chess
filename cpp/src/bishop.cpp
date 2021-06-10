#include "../include/bishop.h"

vector<Move> Bishop::directions = {
    Move(1, 1, 0),
    Move(-1, 1, 0),
    Move(1, -1, 0),
    Move(-1, -1, 0),
    Move(1, 0, 1),
    Move(-1, 0, 1),
    Move(1, 0, -1),
    Move(-1, 0, -1),
    Move(0, 1, 1),
    Move(0, -1, 1),
    Move(0, 1, -1),
    Move(0, -1, -1)
};

char Bishop::getId() {
    return 'b';
}

vector<Move> Bishop::getMoves(Board board, bool prune) {
    // get all moves in line based of piece directions
    return getAllMovesInLine(directions, board, prune);
}