#include "../include/queen.h"

vector<Move> Queen::directions = {
    Move(1, 0, 0),
    Move(-1, 0, 0),
    Move(0, 1, 0),
    Move(0, -1, 0),
    Move(0, 0, 1),
    Move(0, 0, -1),
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
    Move(0, -1, -1),
    Move(1, 1, 1),
    Move(-1, 1, 1),
    Move(1, -1, 1),
    Move(1, 1, -1),
    Move(1, -1, -1),
    Move(-1, 1, -1),
    Move(-1, -1, 1),
    Move(-1, -1, -1)
};

vector<Move> Queen::getMoves(Board board) {
    // get all moves in line based of piece directions
    return getAllMovesInLine(directions, board);
}