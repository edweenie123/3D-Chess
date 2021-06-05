#include "../include/knight.h"
#include<iostream>

char Knight::getId() {
    return 'n';
}

vector<Move> Knight::getMoves(Board board) {

    vector<Move> moves;

    // initialize the ortho knight moves
    vector<vector<int>> orthoMoves = {
        {0, 1, 2},
        {-1, 0, 2},
        {-2, 0, 1},
        {-2, -1, 0},
    };

    // for each ortho move, we iterate through all permutations of it to account for the "3D-ness" of the board

    for (int i = 0; i < orthoMoves.size(); i++) {

        do {

            Move posMove = Move(orthoMoves[i][0], orthoMoves[i][1], orthoMoves[i][2]);
            Coordinate posCord = Coordinate(location, posMove);
            
            // add the move only if the cell is vacant or is occupied by an enemy piece
            if (board.isVacant(posCord))
                moves.push_back(posMove);
            else if (board.isEnemySquare(posCord, color))
                moves.push_back(posMove);

        } while (next_permutation(orthoMoves[i].begin(), orthoMoves[i].end()));

    }

    return moves;
}