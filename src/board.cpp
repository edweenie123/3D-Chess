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
                Piece emptyCell;
                emptyCell.isAlive = false;
                board[i][j][k] = emptyCell;
            }
        }
    }
    // set the board (bottom left back corner is 0, 0, 0)

    // set pieces for Level A
    board[0][0][0] = Rook(0, 0, 0, 1);
    board[0][4][0] = Rook(0, 4, 0, 1);
    board[0][1][0] = Knight(0, 1, 0, 1);
    board[0][3][0] = Knight(0, 3, 0, 1);
    board[0][2][0] = King(0, 2, 0, 1);
    for (int i = 0; i < 5; ++i) {
        board[1][i][0] = Pawn(1, i, 0, 1);
    }

    // set pieces for Level B
    board[0][0][1] = Bishop(0, 0, 1, 1);
    board[0][3][1] = Bishop(0, 3, 1, 1);
    board[0][1][1] = Unicorn(0, 1, 1, 1);
    board[0][4][1] = Unicorn(0, 4, 1, 1);
    board[0][2][1] = Queen(0, 2, 1, 1);
    for (int i = 0; i < 5; ++i) {
        board[1][i][1] = Pawn(1, i, 1, 1);
    }

    // set pieces for Level D
    board[4][0][3] = Bishop(4, 0, 3, -1); // colour -1 means black
    board[4][3][3] = Bishop(4, 3, 3, -1);
    board[4][1][3] = Unicorn(4, 1, 3, -1);
    board[4][4][3] = Unicorn(4, 4, 3, -1);
    board[4][2][3] = Queen(4, 2, 3, -1);
    for (int i = 0; i < 5; ++i) {
        board[3][i][3] = Pawn(3, i, 3, -1);
    }

    // set pieces for Level E
    board[4][0][4] = Rook(4, 0, 4, -1);
    board[4][4][4] = Rook(4, 4, 4, -1);
    board[4][1][4] = Knight(4, 1, 4, -1);
    board[4][3][4] = Knight(4, 3, 4, -1);
    board[4][2][4] = King(4, 2, 4, -1);
    for (int i = 0; i < 5; ++i) {
        board[3][i][4] = Pawn(3, i, 4, -1);
    }
}

Piece Board::getPieceAt(Coordinate square) {
    return board[square.row][square.col][square.lvl];
}

Piece Board::getPieceAt(int row, int col, int lvl) {
    return board[row][col][lvl];
}

bool Board::isOnBoard(Coordinate c) {
    if (c.row >= 0 && c.row < 5 && c.col >= 0 && c.col < 5 && c.lvl >= 0 && c.lvl < 5) {
        return true; // this coordinate lies within te 5x5x5 board
    }
    return false;
}

bool Board::isVacant(Coordinate c) {
    if (board[c.row][c.col][c.lvl].isAlive) {
        return false; // this square is occupied
    }
    return true;
}

void Board::updateLocation(Coordinate square, Move movement) {
    Piece curPiece = getPieceAt(square);

    // FIRST check if the move is legal
    int newRow = curPiece.location.row + movement.row;
    int newCol = curPiece.location.col + movement.col;
    int newLvl = curPiece.location.lvl + movement.lvl;
    Coordinate newCord;
    newCord.row = newRow;
    newCord.col = newCol;
    newCord.lvl = newLvl;

    bool legal = true;

    if (isOnBoard(newCord) == false) {
        legal = false;
    } else if (isVacant(newCord) == false && board[newRow][newCol][newLvl].color == curPiece.color) {
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
    Piece emptyCell;
    emptyCell.isAlive = false;
    board[curPiece.location.row][curPiece.location.col][curPiece.location.lvl] = emptyCell;

    // update board with the piece's new location

    // if there is a black piece currently occupying the new location, we destroy it
    if (!isVacant(newCord)) {
        board[newRow][newCol][newLvl].isAlive = false;
    }
    board[newRow][newCol][newLvl] = curPiece;
}

string Board::getGameState() {
    // Check for checkmate on both sides
    // i believe I need pieces class to be finished (legal moves for each piece to complete this part)
    // Check for check on both sides

    // Check for stalemate on both sides

    return "placehold";
}
