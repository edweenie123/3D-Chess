#include "../include/rook.h"

vector<Move> Rook::getMoves(Board board) {
    vector<Move> moves;

   // NEED TO ADD PIECE BLOCKING
    
    // go through all directions (up, down, left, right, front, back) to find legal moves
    
    Move delta[6] = {
        Move(1, 0, 0),
        Move(-1, 0, 0),
        Move(0, 1, 0),
        Move(0, -1, 0),
        Move(0, 0, 1),
        Move(0, 0, -1),
    };

    for (int di = 0; di < 6; di++) {
        Coordinate cur;

        
    }


    int delta = 1;
    for (int i=location.row;i<5;i++) {
        if (board.isVacant(Coordinate(i, location.col, location.lvl)))
            moves.push_back(Move(delta++, 0, 0));    
        else {
            if (board.getPieceAt(Coordinate(i, location.col, location.lvl)).color != color)
                moves.push_back(Move(delta++, 0, 0));    
            break;
        }
    }



    delta = -1;
    for (int i=location.row;i>=0;i--) {
        if (board.isVacant(Coordinate(i, location.col, location.lvl)))
            moves.push_back(Move(delta--, 0, 0));    
        else {
            moves.push_back(Move(delta--, 0, 0));    
            break;
        }
    }
    

    

    return moves;
}