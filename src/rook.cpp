#include "../include/rook.h"

vector<Move> Rook::getMoves(Board board) {
    vector<Move> moves;
    
    Move delta[6] = {
        Move(1, 0, 0),
        Move(-1, 0, 0),
        Move(0, 1, 0),
        Move(0, -1, 0),
        Move(0, 0, 1),
        Move(0, 0, -1),
    };

    // go up, down, left, right, front and back to find all legal moves

    for (int di = 0; di < 6; di++) {
        Coordinate cur(location.row, location.col, location.lvl);
        Move curDelta = delta[di];

        while (true) {
            cur = Coordinate(cur, curDelta);

            if (!board.isOnBoard(cur)) break;
            if (!board.isVacant(cur)) {
                // only add the move if the piece at cur is of OPPOSITE color
                if (board.getPieceAt(cur).color != color)
                    moves.push_back(curDelta);
                
                // exit the while loop as there is a piece blocking the rook's way
                break;
            }

            // coordinate cur is empty 
            moves.push_back(curDelta);

            curDelta = curDelta + delta[di];
        }
    }
    
    return moves;
}