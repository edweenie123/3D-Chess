#include "../include/queen.h"

char Queen::getId() {
    return 'q';
}

vector<Move> Queen::getMoves(Board board, bool prune) {

    vector<Move> moveDirections;

    // generate all the directions the queen can go in
    for (auto a : {-1, 0, 1}) {
        for (auto b : {-1, 0, 1}) {
            for (auto c : {-1, 0, 1}) {
                if (a == 0 && b == 0 && c == 0) continue;
                moveDirections.push_back(Move(a, b, c));
            }
        }
    }

    // get all moves in line based of piece directions
    return getAllMovesInLine(moveDirections, board, prune);
}