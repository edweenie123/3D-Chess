#include "../include/board.h"

Board::Board() {
    // initialize the board
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                // set to empty piece
                board[i][j][k] = emptypiece; // NOTE need the individual pieces to be defined
            }
        }
    }
    // set the board (bottom left back corner is 0, 0, 0)

    // set pieces for Level A
    board[0][0][0] = board[0][4][0] = whiterook;
    board[0][1][0] = board[0][3][0] = whiteknight;
    board[0][2][0] = whiteking;
    board[1][0][0] = board[1][1][0] = board[1][2][0] = board[1][3][0] = board[1][4][0] = whitepawn;

    // set pieces for Level B
    board[0][0][1] = board[0][3][1] = whitebishop;
    board[0][1][1] = board[0][4][1] = whiteunicorn;
    board[0][2][1] = whitequeen;
    board[1][0][1] = board[1][1][1] = board[1][2][1] = board[1][3][1] = board[1][4][1] = whitepawn;

    // set pieces for Level D
    board[4][0][3] = board[4][3][3] = blackbishop;
    board[4][1][3] = board[4][4][3] = blackunicorn;
    board[4][2][3] = blackqueen;
    board[3][0][3] = board[3][1][3] = board[3][2][3] = board[3][3][3] = board[3][4][3] = blackpawn;

    // set pieces for Level E
    board[4][0][4] = board[4][4][4] = blackrook;
    board[4][1][4] = board[4][3][4] = blackknight;
    board[4][2][4] = blackking;
    board[3][0][4] = board[3][1][4] = board[3][2][4] = board[3][3][4] = board[3][4][4] = blackpawn;  
}

Piece Board::getPieceAt(Coordinate square) {
    return board[square.row][square.col][square.lvl];
}

void Board::updateLocation(Coordinate square, Move movement) {
    Piece curPiece = getPieceAt(square);
    curPiece.location.row = movement.row;
    curPiece.location.col = movement.col;
    curPiece.location.lvl = movement.lvl;
}

string Board::getGameState() {
    // Check for checkmate on both sides
    // i believe I need pieces class to be finished (legal moves for each piece to complete this part)
    // Check for check on both sides

    // Check for stalemate on both sides

    return "placehold";
}