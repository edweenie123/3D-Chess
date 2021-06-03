#include "../include/pawn.h"

char Pawn::getId() {
    return 'p';
}

vector<Move> Pawn::getMoves(Board board) {

    vector<Move> moves;

    vector<Move> captureDirections; // capture a piece while moving
    vector<Move> passiveDirections; // move into a vacant cell

    // move (up/down) or straight 
    passiveDirections = {
        Move((color==0 ? 1 : -1), 0, 0), 
        Move(0, 0, (color==0 ? 1 : -1))
    };

    // capture diagonally or diagonally (up/down)
    captureDirections = {
        Move((color==0 ? 1 : -1), 1, 0),
        Move((color==0 ? 1 : -1), -1, 0),
        Move((color==0 ? 1 : -1), 1, (color==0 ? 1 : -1)),
        Move((color==0 ? 1 : -1), -1, (color==0 ? 1 : -1))
    };

    for (auto m : passiveDirections) {
        // get the coordinate if the piece were to make a passive move
        Coordinate potCord = Coordinate(location, m);
        
        // this move can only be made if cell is empty
        if (board.isVacant(potCord)) moves.push_back(m);
    }

    for (auto m : captureDirections) {
        // get the coordinate if the piece were to make a passive move
        Coordinate potCord = Coordinate(location, m);
        
        // this move can only be made if cell contains an ENEMY piece
        if (board.getPieceAt(potCord).color != color) moves.push_back(m);
    }

    return moves;
}

void Pawn::Promote() {
    /*
    
    replace this piece with any piece the user picks
    perhaps this method should be in the board class ??

    */
}