#include "../include/board.h"
#include "../include/rook.h"
#include "../include/king.h"
#include "../include/bishop.h"
#include "../include/unicorn.h"
#include "../include/queen.h"
#include "../include/pawn.h"
#include "../include/knight.h"
#include "../include/piece.h"

Board::Board() {
    // initialize the board
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                /* To Denote an empty cell, we simply use a dead piece */
                board[i][j][k] = new Piece();
                board[i][j][k]->isAlive = false;
            }
        }
    }
    // set the board (bottom left back corner is 0, 0, 0)

    // set pieces for Level A
    board[0][0][0] = new Rook(0, 0, 0, 1);
    board[0][4][0] = new Rook(0, 4, 0, 1);
    board[0][1][0] = new Knight(0, 1, 0, 1);
    board[0][3][0] = new Knight(0, 3, 0, 1);
    board[0][2][0] = new King(0, 2, 0, 1);
    for (int i = 0; i < 5; ++i) {
        board[1][i][0] = new Pawn(1, i, 0, 1);
    }

    // set pieces for Level B
    board[0][0][1] = new Bishop(0, 0, 1, 1);
    board[0][3][1] = new Bishop(0, 3, 1, 1);
    board[0][1][1] = new Unicorn(0, 1, 1, 1);
    board[0][4][1] = new Unicorn(0, 4, 1, 1);
    board[0][2][1] = new Queen(0, 2, 1, 1);
    for(int i = 0; i < 5; ++i) {
        board[1][i][1] = new Pawn(1, i, 1, 1);
    }

    // set pieces for Level D
    board[4][0][3] = new Bishop(4, 0, 3, -1); // colour -1 means black
    board[4][3][3] = new Bishop(4, 3, 3, -1);
    board[4][1][3] = new Unicorn(4, 1, 3, -1);
    board[4][4][3] = new Unicorn(4, 4, 3, -1);
    board[4][2][3] = new Queen(4, 2, 3, -1);
    for(int i = 0; i < 5; ++i) {
        board[3][i][3] = new Pawn(3, i, 3, -1);
    }

    // set pieces for Level E
    board[4][0][4] = new Rook(4, 0, 4, -1);
    board[4][4][4] = new Rook(4, 4, 4, -1);
    board[4][1][4] = new Knight(4, 1, 4, -1);
    board[4][3][4] = new Knight(4, 3, 4, -1);
    board[4][2][4] = new King(4, 2, 4, -1);
    for(int i = 0; i < 5; ++i) {
        board[3][i][4] = new Pawn(3, i, 4, -1);
    }
}

Piece* Board::getPieceAt(Coordinate square) {
    return board[square.row][square.col][square.lvl];
}

Piece* Board::getPieceAt(int row, int col, int lvl) {
    return board[row][col][lvl];
}

bool Board::isOnBoard(Coordinate c) {
    if (c.row >= 0 && c.row < 5 && c.col >= 0 && c.col < 5 && c.lvl >= 0 && c.lvl < 5) {
        return true; // this coordinate lies within te 5x5x5 board
    }
    return false;
}

bool Board::isVacant(Coordinate c) {
    Piece curPiece = *board[c.row][c.col][c.lvl];
    if (curPiece.isAlive) {
        return false; // this square is occupied
    }
    return true;
}

void Board::updateLocation(Coordinate square, Move movement) {
    Piece curPiece = *getPieceAt(square);

    // FIRST check if the move is legal
    int newRow = curPiece.location.row + movement.row;
    int newCol = curPiece.location.col + movement.col;
    int newLvl = curPiece.location.lvl + movement.lvl;
    Piece nextSquare = *board[newRow][newCol][newLvl]; // the piece in the square the current piece is about to move to

    bool legal = true;

    if (isOnBoard({newRow, newCol, newLvl}) == false) {
        legal = false;
    } else if (isVacant({newRow, newCol, newLvl}) == false && nextSquare.color == curPiece.color) {
        legal = false;
    }
    // haven't added king checks, and check checks (king can't place itself in a check)
    if (!legal) return;

    // The move should be legal, so we update it on the board,and for the piece

    // update the piece
    curPiece.location.row = newRow;
    curPiece.location.col = newCol;
    curPiece.location.lvl = newLvl;

    // We need to update the board
    /* To Denote an empty cell, we simply use a dead piece */
    board[curPiece.location.row][curPiece.location.col][curPiece.location.lvl] = new Piece();
    board[curPiece.location.row][curPiece.location.col][curPiece.location.lvl]->isAlive = false;

    // update board with the piece's new location

    // if there is a black piece currently occupying the new location, we destroy it
    if (!isVacant({newRow, newCol, newLvl})) {
        nextSquare.isAlive = false;
    }
    nextSquare = curPiece;
}

string Board::getGameState() {
    // Check for checkmate on both sides
    // i believe I need pieces class to be finished (legal moves for each piece to complete this part)
    // Check for check on both sides

    // Check for stalemate on both sides

    return "placehold";
}
