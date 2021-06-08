#include "../include/king.h"

char King::getId() {
    return 'k';
}

vector<Move> King::getMoves(Board board) {

    vector<Move> moves;

    // generate all the directions the king can go in
    for (auto a : {-1, 0, 1}) {
        for (auto b : {-1, 0, 1}) {
            for (auto c : {-1, 0, 1}) {
                if (a == 0 && b == 0 && c == 0) continue;

                Move posMove = Move(a, b, c);
                Coordinate cur = Coordinate(location, posMove);
                if (board.isVacant(cur))
                    moves.push_back(Move(a, b, c));
                else if (board.isOnBoard(cur) && board.getPieceAt(cur)->color != color) {
                    moves.push_back(Move(a, b, c));
                }
            }
        }
    }



    return moves;
}