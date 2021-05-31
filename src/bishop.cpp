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

vector<Move> Bishop::getMoves(Board board) {
    // get all moves in line based of piece directions
    return getAllMovesInLine(directions, board);
}