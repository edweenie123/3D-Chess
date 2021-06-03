#include "../include/unicorn.h"

char Unicorn::getId() {
    return 'u';
}

vector<Move> Unicorn::directions = {
    Move(1, 1, 1),
    Move(-1, 1, 1),
    Move(1, -1, 1),
    Move(1, 1, -1),
    Move(1, -1, -1),
    Move(-1, 1, -1),
    Move(-1, -1, 1),
    Move(-1, -1, -1)
};

vector<Move> Unicorn::getMoves(Board board) {
    // get all moves in line based of piece directions
    return getAllMovesInLine(directions, board);
}